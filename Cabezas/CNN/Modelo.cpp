#define _CRT_SECURE_NO_WARNINGS
#include "Modelo.h"
#include "Image.h"
#include "Convolution.h"
#include "Layer.h"
#include "FullyConnected.h"
#include "Activations.h"
#include <fstream>
#include <chrono>
#include <ctime> 

namespace ReconLib {
	
	Modelo::Modelo(std::vector<Matriz> images,std::vector<std::vector<float>> labels, int epocas, int convolutions, int maxpoolings, float learningRate, std::string pesospath) {
		/*int trainNumber = ceil(images.size() * 0.8);
		int validNumber = images.size()-trainNumber;*/
		int trainNumber = images.size();
		int validNumber = images.size();

		for (int i = 0; i < trainNumber;i++) {
			this->imagesTrain.push_back(images.at(i));
			//images.at(i).mostrar();
			this->labelsTrain.push_back(labels.at(i));
		}
		//
		//
		// Verificar que los labels calzen con la posicion de la imagen
		//
		//
		for (int i = trainNumber; i < images.size();i++) {
			this->imagesValid.push_back(images.at(i));
			this->labelsValid.push_back(labels.at(i));
		}

		this->epochs = epocas;
		this->convolutions = convolutions;
		this->maxpoolings = maxpoolings;
		this->learningRate = learningRate;
		this->rutapesos = pesospath;
	}
	
	void Modelo::train() {
		float totalEntropy = 1.0;
		int e = 0;
		while (e<this->epochs && totalEntropy>0.001) {
			//recorrer imagenes
			totalEntropy = 0.0;
			for (int index = 0; index <this->imagesTrain.size();index++) {
				
				auto start = std::chrono::system_clock::now();

				totalEntropy = totalEntropy + imageLoss(index, e);

				auto end = std::chrono::system_clock::now();

				std::chrono::duration<double> elapsed_seconds = end - start;
				std::time_t end_time = std::chrono::system_clock::to_time_t(end);
				std::cout << "Epoch: " << e + 1 << " Imagen n: " << index << " FPS:"<< 1.0/elapsed_seconds.count()<<"\r";
				
			}
			totalEntropy = totalEntropy / this->imagesTrain.size();

			std::cout << "La entropia total es: "<< totalEntropy<<" Para la epoca: "<<e+1<<'\n';
			std::cout << "Backpropagating...";
			backprop(e);
			std::cout << "\r";
			e++;
		}

		//create txt
		//this->weights.mostrar();
		exportWeights(rutapesos);
	}

	void Modelo::exportWeights(std::string rutapesos) {
		std::ofstream weights(rutapesos);
		for (int i = 0; i < this->weights.alto;i++) {
			for (int j = 0; j < this->weights.ancho;j++) {
				weights << this->weights.get(i,j);
				weights << ' ';
			}
			weights << '\n';
		}
		weights.close();
	}

	float Modelo::imageLoss(int index, int epoch) {
		float lossEntropy = 0;
		std::vector<Matriz> imagenIn;
		
		imagenIn.push_back(this->imagesTrain.at(index));
		//Convolution con1(imagenIn,numFilters);
		////Falta max pooling
		//std::vector<Matriz> conv1Res = con1.getImageOut();
		//Convolution con2(conv1Res,numFilters);
		//std::vector<Matriz> conv2Res;
		std::vector<Matriz> convolution = imagenIn;
		std::vector<Matriz> convRes;
		for (int i = 0; i < this->convolutions;i++) {
			Convolution con(convolution);
			convolution = con.getImageOut();
			 if (i<=this->maxpoolings/* && i>0*/) {
				 std::vector<Matriz> maxpoolingConv;
				 for (Matriz m:convolution) {
					 maxpoolingConv.push_back(Layer().maxpooling(m));
				 }
				 convolution = maxpoolingConv;
			 }
			 if (i==this->convolutions-1) {
				 convRes = convolution;
			 }
		}
		/*for (Matriz matrizCon2: con2.getImageOut()) {
			conv2Res.push_back(Layer().maxpooling(matrizCon2));
		} */
		int numLabels = this->labelsTrain.at(0).size();

		if (epoch==0) {
			FullyConnected fc1(Layer().flatten(convRes), numLabels);
			this->inputLayerPerImage.push_back(fc1.getNeuronsIn());
			this->softmaxLayerPerImage.push_back(fc1.applySoftmax());
			this->weights = fc1.getInputWeights();
			//fc1.mostrarWeights();
			return Activations().crossentropy(this->softmaxLayerPerImage.at(index), this->labelsTrain.at(index));
		}
		FullyConnected fc1(Layer().flatten(convRes), numLabels,this->weights.toVector());
		this->inputLayerPerImage.at(index)=fc1.getNeuronsIn();
		this->softmaxLayerPerImage.at(index)=fc1.applySoftmax();
		this->weights = fc1.getInputWeights();
		//fc1.mostrarWeights();
		float numero=Activations().crossentropy(this->softmaxLayerPerImage.at(index), this->labelsTrain.at(index));
		return numero;
	}

	void Modelo::backprop(int epoch) {
		
		for (int image = 0; image < this->imagesTrain.size();image++) {
			calculateGradients(image,epoch);
		}
		calculateAvgGradient(this->gradients);
		
		applyGradient();	
		
		
	}

	void Modelo::calculateGradients(int imageIndex,int epoch) {
		//Calcular vector gradiente:
		//	calcular el valor gradiente por cada peso
		//	gradiente = x*(p-q)
		//	gradienteFinal = promedio de los gradientes por peso
		Matriz gradient(this->weights.ancho,this->weights.alto);
		for (int neuron = 0; neuron < this->inputLayerPerImage.at(imageIndex).size();neuron++) {
			//gradient.push_back();
			for (int label = 0; label < this->weights.ancho;label++) {
				//std::cout << " gradient value :"<<gradientValue<<'\n';
				gradient.set(neuron,label, inputLayerPerImage.at(imageIndex).at(neuron) * (softmaxLayerPerImage.at(imageIndex).at(label) - labelsTrain.at(imageIndex).at(label)));
			}
		}
		if (epoch == 0) {
			this->gradients.push_back(gradient);
		}
		else {
			this->gradients.at(imageIndex)= gradient;
		}
		//gradient.mostrar();
		
		//Ajustar los pesos
		//	w = w - gradiente
	}

	void Modelo::calculateAvgGradient(std::vector<Matriz> gradients) {
		Matriz avgM(gradients.at(0).ancho,gradients.at(0).alto);
		float num=0;
		for (int i = 0; i < avgM.alto;i++) {
			for (int j = 0; j < avgM.ancho;j++) {
				num = 0;
				for (Matriz gradient:gradients) {
					num = num + gradient.get(i,j);
				}
				num = num / gradients.size();
				avgM.set(i,j,num);
			}
		}

		this->avgGradients = avgM;
	}

	void Modelo::applyGradient() {
		//Falta multiplicar por el learning rate
		this->weights = Matriz().subtractMatrizTerm(this->weights,this->avgGradients.mulByScalar(this->learningRate));

	}

	
}