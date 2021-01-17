#define _CRT_SECURE_NO_WARNINGS
#include "CNN/ReconLib.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

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
    t.validate("../dataset/cabezas_val/", labeles);
    t.validate("../dataset/nocabeza_val/", labeles2);
    return 0;
}

void entrenarcabezas(std::string rutapesos) {
    int epochs = 150;
    float learningrate = 0.4;
    Detector t(rutapesos);
    t.train(epochs, learningrate);
}

int main()
{
    std::string rutapesos = "pesos.txt";
    entrenarcabezas(rutapesos);
    validarcabezas(rutapesos);
    //Mat m =imread("../dataset/cabezas_train/PartB_00000_23.jpg");
    //imshow("cabeza", m);
    //waitKey();
}