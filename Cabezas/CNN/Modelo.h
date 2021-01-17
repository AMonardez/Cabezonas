#ifndef Modelo_H
#define Modelo_H

#include <vector>
#include "Matriz.h"


namespace ReconLib {
	class Modelo {

	private:

		int epochs;
		Matriz weights;
		Matriz avgGradients;
		int convolutions;
		int maxpoolings;
		float learningRate;
		std::string rutapesos;
		std::vector<Matriz> gradients;
		std::vector<Matriz> imagesTrain;
		std::vector<Matriz> imagesValid;
		std::vector<std::vector<float>> labelsTrain;
		std::vector<std::vector<float>> labelsValid;
		std::vector<std::vector<float>> inputLayerPerImage;
		std::vector<std::vector<float>> softmaxLayerPerImage;
		void calculateGradients(int imageIndex,int epoch);
		void calculateAvgGradient(std::vector<Matriz> gradients);
		void applyGradient();
		void exportWeights(std::string rutapesosout);
	public:
		Modelo(std::vector<Matriz> images, std::vector<std::vector<float>> labels, int epocas, int convolutions, int maxpoolings, float learningRate, std::string pesospath);
		void train();//Encontrar los pesos ideales
		float imageLoss(int index,int epoch);
		void backprop(int epoch);
	};
}

#endif

