#define _CRT_SECURE_NO_WARNINGS
#include "CNN/ReconLib.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>
#include <ctime> 

using namespace ReconLib;
using namespace cv;

int validarcabezas(std::string rutapesos) {
    Detector t(rutapesos);
    //Detector ex testeo
    //Testeo t("../Personas/pesos_personas.txt");
    //std::vector<float> labeles(2, 0.0);labeles.at(0) = 1.0;
    //std::vector<float> labeles2(2, 0.0); labeles2.at(1) = 1.0;
    std::vector<float> labeles = {1.0, 0.0};
    std::vector<float> labeles2 = {0.0, 1.0};
    //auto start = std::chrono::system_clock::now();
    t.validate("../dataset/cabezas_val/", labeles);
    //auto end = std::chrono::system_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    //std::cout << "Termina de analizar. " << "Duracion: " << elapsed_seconds.count() << "seg (" << 1.0 / elapsed_seconds.count() << " FPS)\n";

    t.validate("../dataset/nocabeza_val/", labeles2);
    return 0;
}

void entrenarcabezas(std::string rutapesos) {
    int epochs = 5;
    float learningrate = 0.4;
    Detector t(rutapesos);
    t.train(epochs, learningrate);
}

void basuras() {
    //Mat m = imread("../dataset/cabezas_train/PartB_00000_23.jpg");
    std::vector<Matriz> f= Image::CargaCarpeta("../dataset/test/");
    Convolution cl(f);
    auto start = std::chrono::system_clock::now();
    cl.getImageOut();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Termina de analizar. " << "Duracion: " << elapsed_seconds.count() << "seg (" << 1.0 / elapsed_seconds.count() << " FPS)\n";

    //cl.convolutionFunction();


    /*std::cout<< "Tamaño convoluciones:" << cl.getImageOut().size()<<std::endl;
    for (Matriz m : cl.getImageOut()) {
        m.mostrardim();
    }*/
}

int main()
{
    std::string rutapesos = "pesos.txt";
    entrenarcabezas(rutapesos);
    validarcabezas(rutapesos);
    //basuras();

    //Mat m =imread("../dataset/cabezas_train/PartB_00000_23.jpg");
    //imshow("cabeza", m);
    //waitKey();
}