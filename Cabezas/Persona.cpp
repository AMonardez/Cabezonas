#include "CNN/ReconLib.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace ReconLib;

int ui();
int entrenar(std::string rutapesos);
int escanear(std::string rutapesos, std::string nombrearchivo);
int validar(std::string rutapesos);


VideoCapture streamvideo() {
	int opcion=0;
	int fuente = -1;
	cout << "Ingrese una opción para la fuente de video:" << endl;
	cout << "\t1.- Camara principal." << endl;
	cout << "\t2.- Camara auxiliar 1." << endl;
	cout << "\t3.- Camara auxiliar 2." << endl;
	cin >> opcion;
	//scanf("%d", &opcion);
	if (opcion == 0) fuente = 0;
	else if (opcion == 1) fuente = 1;
	else if (opcion == 2) fuente = 2;
	return VideoCapture(0);
}


int main4() {
	string rutapesos="../Personas/pesos.txt";
	//string rutapesos = "../pesos.txt";
	//ui();
	//red();
	//entrenar(rutapesos);
	validar(rutapesos);
	//escanear(rutapesos, "./pruebaa.bmp");
	//system("pause");
	return 0;
}

int ui() {
	VideoCapture cap(0);
	system("cls");
	cout << "Monitoreando"<<endl;
	if (!cap.isOpened()) {
		cout << "Error abriendo la camara." << endl;
		return -1;
	}
	while (1) {
		Mat frame;
		Mat capturado;
		cap >> frame;
		if (frame.empty()) break;

		imshow("Monitoreo", frame);

		char c = (char)waitKey(25); //Tecla ESCAPE
		//cout << (int)c << endl;
		if (c == 27)
		{
			break;
		}
		else if (c == 32) { //ESPACIO
			cv::destroyWindow("Monitoreo");
			capturado = frame;
			imshow("Deteccion.", capturado);
			waitKey(0);
			//break;
			destroyWindow("Deteccion.");
		}

	}
	return 0;
}

int entrenar(std::string rutapesos) {
	cout << "Entrenar." << endl;
	int epochs = 15;
	float learningRate = 0.4;
	Detector t(rutapesos);
	t.train(epochs,learningRate);
	return 0;
}

int validar(std::string rutapesos) {
	Detector t(rutapesos);
	//Testeo t("../Personas/pesos_personas.txt");
	std::vector<float> labeles(2,0.0);
	labeles.at(0) = 1.0;
	std::vector<float> labeles2(2, 0.0);
	labeles2.at(1) = 1.0;
	t.validate("../dataset/validacion_pos/",labeles);
	t.validate("../dataset/validacion_neg/", labeles2);
	return 0;
}

int escanear(std::string rutapesos, std::string nombrearchivo) {
	cout << "Escanear imagen." << endl;
	Detector t(rutapesos);
	//std::string rutaimagen = "../dataset/img_positivo/person_051.bmp";
	//std::string rutaimagen = "C:/Users/aleja/source/repos/Personas/dataset/img_positivo/person_051.bmp";
	std::string rutaimagen = nombrearchivo;
	std::vector<struct label> etiquetas= t.scanPredict(rutaimagen);
	etiquetas.at(0).mostrar();
	//for (struct label l : etiquetas) l.mostrar();
	return 0;
}
