#define _CRT_SECURE_NO_WARNINGS
#include "Detector.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Convolution.h"
#include "FullyConnected.h"
#include "Activations.h"
#include "Layer.h"
#include "Modelo.h"

#include <chrono>
#include <ctime> 
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


namespace ReconLib {
	Detector::Detector(std::string ruta_archivo_pesos) {
		std::ifstream weights(ruta_archivo_pesos);
        std::string line;
        this->rutapesos = ruta_archivo_pesos;
		std::vector<std::vector<float>> v;

        if (weights.is_open()) std::cout << "Abrio correctamente el archivo de pesos.\n";
        else std::cout << "Fallo al abrir archivo de pesos.\n";

        int i = 0;
        while (std::getline(weights, line))
        {
            float value;
            std::stringstream ss(line);

            v.push_back(std::vector<float>());

            while (ss >> value)
            {
                v[i].push_back(value);
            }
            ++i;
        }

        Matriz weightsFromFile(v);
        this->weights = weightsFromFile;
        //this->weights.mostrar();

        //etiquetas.push_back("Cabeza");
        //etiquetas.push_back("No cabeza");

	}
    
    std::vector<float> Detector::predict(Matriz image) {
        int convolutions = n_convolutions;
        int maxpoolings = n_maxpoolings;
        std::vector<Matriz> imagenIn;
        imagenIn.push_back(image);
        std::vector<Matriz> convolution = imagenIn;
        std::vector<Matriz> convRes;
        for (int i = 0; i < convolutions; i++) {
            Convolution con(convolution);
            convolution = con.getImageOut();
            if (i <=maxpoolings /*&& i>0*/) {
                std::vector<Matriz> maxpoolingConv;
                for (Matriz m : convolution) {
                    maxpoolingConv.push_back(Layer().maxpooling(m));
                }
                convolution = maxpoolingConv;
            }
            if (i == convolutions - 1) {
                convRes = convolution;
            }
        }
        //int numLabels = this->weights.ancho;
        int numLabels = labels;
        FullyConnected fc1(Layer().flatten(convRes), numLabels, this->weights.toVector());
        //std::vector<float> sfmx= fc1.applySoftmax();
        //std::cout << "Sfmx:" << sfmx.size() << "\n";
        //return sfmx;
        return fc1.applySoftmax();
        
    }

    std::vector<struct label> Detector::scanPredict(std::string ruta) {      
        int stride = 60;

        int strideancho = anchoTrainingImage / 3;
        int stridealto = altoTrainingImage / 4;
        //Image im = Image(ruta);
        //Matriz image = im.toMatriz();
        cv::Mat mat = cv::imread(ruta);
        cv::imshow("Prueba persona", mat);
        cv::waitKey(0);

        int alto = mat.rows;
        int ancho = mat.cols;
        Matriz image(ancho, alto);
        for (int i = 0; i < mat.rows; i++){
            for (int j = 0; j < mat.cols; j++){
                cv::Vec3b bgrPixel = mat.at<cv::Vec3b>(i, j);
                //cout << bgrPixel[0] << "-" << bgrPixel[1] << "-" << bgrPixel[2] << endl;
                image.set(i, j, (bgrPixel[0] + bgrPixel[1] + bgrPixel[2]) * 1.0 / (3.0 * 255.0));
            }
        }
        std::vector<std::string> nombreslabels = etiquetas;
        //nombreslabels.push_back("Persona");
        //nombreslabels.push_back("No Persona");
        struct label mejorcero; mejorcero.precision = 0;
        std::vector<struct label> best(nombreslabels.size(),mejorcero);
        int b = 0;
        int iteracion = 0;
        int iteracionestotales = (((image.alto - altoTrainingImage) +2)/stridealto) * (((image.ancho - anchoTrainingImage)+2)/strideancho);
        std::cout << "Comenzando a analizar " << ruta << "\n";

        auto start = std::chrono::system_clock::now();

        for (int i = 0; i < image.alto - (altoTrainingImage - 1);i=i+stridealto) {
            for (int j = 0; j < image.ancho - (anchoTrainingImage - 1); j=j+strideancho) {
                b = 0;
                std::vector<float> namesProb = predict(image.subMatriz(i,j,anchoTrainingImage,altoTrainingImage));
                std::string label = nombreslabels.at(Activations().argmax(namesProb));
                b = Activations().argmax(namesProb);
                if(namesProb.at(b) > best.at(b).precision){
                    //CENTRAR LA COORDENADA DE LA VENTANA
                    best.at(b).x = j  +(anchoTrainingImage/2);
                    best.at(b).y = i +(altoTrainingImage/2);
                    best.at(b).precision = namesProb.at(b);
                    best.at(b).n_clasificacion = b;
                    best.at(b).clasificacion = label;
				}
                iteracion++;
                std::cout << "Analizando imagen: "  << " X:"<<i <<" Y:"<<j <<"\r";
                //<< (int)(iteracion * 100.0) / iteracionestotales
            }
        }
        std::cout << "\n";

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "Termina de analizar. " << "Duracion: " << elapsed_seconds.count() << "seg (" << 1.0/elapsed_seconds.count() << " FPS)\n";
        //<< std::ctime(&end_time) 
        if (best.at(0).precision > 0.60) {
            cv::rectangle(mat, cv::Rect(best.at(0).x - anchoTrainingImage / 2, best.at(0).y - altoTrainingImage / 2, anchoTrainingImage, altoTrainingImage), cv::Scalar(255.0, 0, 0), 2, 8);
            cv::destroyWindow("Prueba persona");
            cv::imshow("Labeled", mat);
            cv::waitKey(0);
        }
        
        
        
        return best;
    }

    void Detector::train(int epochs,float learningRate) {
        std::vector<Matriz> matrices;
        std::vector<std::vector<float>> labels;

        std::string rutaceros = "../dataset/cabezas_train/";
        std::vector<Matriz> matricesceros = Image::CargaCarpeta(rutaceros);
        for (Matriz m : matricesceros) matrices.push_back(m);
        std::vector<float> ceros(2, 0.0); ceros.at(0) = 1.0;
        for (int i = 0; i < matricesceros.size(); i++) labels.push_back(ceros);

        std::string rutaunos = "../dataset/nocabeza_train/";
        std::vector<Matriz> matricesunos = Image::CargaCarpeta(rutaunos);
        for (Matriz m : matricesunos) matrices.push_back(m);
        std::vector<float> unos(2, 0.0); unos.at(1) = 1.0;
        for (int i = 0; i < matricesunos.size(); i++) labels.push_back(unos);

        Modelo m(matrices, labels, epochs,n_convolutions,n_maxpoolings,learningRate, rutapesos);
        std::cout << "Comienza a entrenar con " << matrices.size() << " imagenes, durante " << epochs << " epoch.\n";

        auto start = std::chrono::system_clock::now();

        m.train();

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "Termina de entrenar: " << std::ctime(&end_time) << "Duracion: " << elapsed_seconds.count() << "seg\n";

    }
    
    void Detector::validate(std::string rutacarpeta, std::vector<float> labelscorrectos) {
        //Se asume que la carpeta tiene imagenes de la misma clase.
        std::cout << "\nTesteando carpeta "<<rutacarpeta<< "\n";
        std::vector<Matriz> imagenes0=Image::CargaCarpeta(rutacarpeta);

        int correctos = 0;
        int totales = imagenes0.size();

        int clasecorrecta = Activations().argmax(labelscorrectos);
        int procesados = 0;
        for (Matriz m:imagenes0) {
        	std::vector<float> labelsProb = predict(m);
        	
            //for (float n : labelsProb) 	std::cout << n << ' ';
        	//std::cout << etiquetas.at(Activations().argmax(labelsProb)) << "\n";
            procesados++;
            std::cout << "Procesados: " << procesados<<"\r";
            if (clasecorrecta == Activations().argmax(labelsProb)) correctos++;
        }
        std::cout << "\n==Resultados validacion: "<< etiquetas.at(clasecorrecta) <<"==\n";
        std::cout << "Totales: " << totales;
        std::cout << "\nCorrectos: " << correctos;
        std::cout << "\nPrecision Clase " <<etiquetas.at(clasecorrecta)<<": "<< (float)correctos*100.0/totales << "%\n";
    }

}