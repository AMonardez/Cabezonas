/* Estructura de los Layers que componen al programa, input layer, convolutional layer
y polling layer*/
//#pragma once
#ifndef Layer_H
#define Layer_H

#include "Matriz.h"
#include <vector>
#include <iostream>
#include <cmath>

namespace ReconLib {
	class Layer {
	private:
		//void modifyW(); //modifica los pesos
		//void modifyB(); //modifica los bias
		
	public:
		//void setFilters();
		std::vector<Matriz> filters;
		std::vector<Matriz> filtersW;
		std::vector<Matriz> filtersB;
		std::vector<Matriz> getFilters();
		void setFiltersW(int filtro,Matriz pesos);
		/*Matriz filtersB;*/
		std::vector<Matriz> convolution(int fill_num, Matriz m);
		Matriz maxpooling(Matriz matrix);
		std::vector<std::vector<float>> flatten(std::vector<Matriz> vector_matrix);
		float ReLu(float relu);
		Matriz optimize(float learningRate,std::vector<float> outputLayer,std::vector<std::vector<Matriz>> convoluciones); //sdg stocastic descendent gradient
		Matriz ReLuApply(Matriz m);
		//std::vector<float> softmax(std::vector<float> inputLayer);
		//float LossFunction(std::vector<float> softRes,std::vector<float> labels);//Cross entropy
	};
}

#endif