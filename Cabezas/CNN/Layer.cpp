//#pragma once
#include "Layer.h"

namespace ReconLib{
    Layer::Layer() {};
    Layer::Layer(std::vector<Matriz> inputs)
    {
        this->Imagenes = inputs;
    }
    Matriz Layer::maxpooling(Matriz matrixEntrada)
    {
        int kernel = 2;
        Matriz m(0, 0);
        std::vector<int> size = m.paddSize(matrixEntrada);
        Matriz matrix(size.at(0),size.at(1));
        matrix = m.padding(matrixEntrada);
        Matriz poolingM(matrix.ancho / kernel, matrix.alto / kernel);
        Matriz subm(kernel, kernel);
        for (int i = 0; i < poolingM.alto; i++)
        {
            for (int j = 0; j < poolingM.ancho; j++)
            {
                subm = m.subMatriz(matrix, i * kernel, j * kernel, kernel);
                //subm.mostrar();
                poolingM.set(i, j, m.grtNumMatriz(subm));
            }
        }
        return poolingM;
    }

    std::vector<std::vector<float>> Layer::flatten(std::vector<Matriz> vector_matrix){
        std::vector<std::vector<float>> flattenVector;
        for(Matriz m:vector_matrix){
            std::vector<float> vn;
            int numeros = (m.alto*m.ancho);
            for(int i = 0;i<numeros;i++){
                vn.push_back(m.numeros[i]);
                //std::cout<< m.numeros[i] <<'\n';
            }
            flattenVector.push_back(vn);
        }
        return flattenVector;
    }
}