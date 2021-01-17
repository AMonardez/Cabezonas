#include "FullyConnected.h"
#include "Activations.h"
#include <iostream>

namespace ReconLib {
	FullyConnected::FullyConnected(std::vector<std::vector<float>> convFlattened, int numLabels) {
		this->numLabels = numLabels;

		std::vector<std::vector<float>> pesos;

		
		for (std::vector<float> vec:convFlattened) {
			for (float num:vec) {
				this->neuronsIn.push_back(num);
				std::vector<float> p;
				for (int i = 0; i < this->numLabels; i++) {
					p.push_back(1.0);
				}
				pesos.push_back(p);
			}
		}

		setBias(0);

		setWeights(pesos);

		setNeuronsOut();
	}

	FullyConnected::FullyConnected(std::vector<std::vector<float>> convFlattened, int numLabels, std::vector<std::vector<float>> weights) {
		this->numLabels = numLabels;

		for (std::vector<float> vec : convFlattened) {
			for (float num : vec) {
				this->neuronsIn.push_back(num);
			}
		}

		setBias(0);

		setWeights(weights);

		setNeuronsOut();
	}

	void FullyConnected::setWeights(std::vector<std::vector<float>> weigths) {
		this->neuronInputWeights = weigths;
	}

	void FullyConnected::setBias(float bias) {
		this->neuInBias=bias;
	}

	void FullyConnected::mostrarWeights() {

		std::cout << "El numero de pesos es : "<<this->neuronInputWeights.size()*this->neuronInputWeights.at(0).size()<<'\n';
		for (std::vector<float> vec:this->neuronInputWeights) {
			for (float num:vec) {
				std::cout << num << " ";
			}
		}
		std::cout << '\n';
		std::cout << "El tamano del vector de pesos es: " << this->neuronInputWeights.size()<<'\n';
	}

	void FullyConnected::mostrarInput() {
		std::cout << "Input Neurons: ";
		for (float n : this->neuronsIn) {
			std::cout << n << ' ';
		}
		std::cout << '\n';
	}

	void FullyConnected::mostrarOutput() {
		std::cout << "Output Neurons: ";
		for (int n:this->neuronsOut) {
			std::cout << n <<' ';
		}
		std::cout <<'\n';
	}

	void FullyConnected::setNeuronsOut() {
		for (int label = 0; label < this->numLabels;label++) {
			float output = 0;
			int contador = 0;
			for (float n:this->neuronsIn) {
				output = output+ n*this->neuronInputWeights.at(contador).at(label);
				//std::cout << this->neuInW.at(contador).at(label)<<'\n';
				contador++;
			}
			output = output + this->neuInBias;
			this->neuronsOut.push_back(output);
		}
	}

	std::vector<float> FullyConnected::applySoftmax() {
		return Activations().softmax(this->neuronsOut);
	}

	std::vector<float> FullyConnected::getNeuronsIn() {
		return this->neuronsIn;
	}

	std::vector<std::vector<float>> FullyConnected::getInputWeights() {
		return this->neuronInputWeights;
	}
}