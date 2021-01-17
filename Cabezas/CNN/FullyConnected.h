#ifndef FullyConnected_H
#define FullyConnected_H

#include <vector>

namespace ReconLib {
	class FullyConnected
	{
	private:
		std::vector<float> neuronsIn;
		std::vector<float> neuronsOut;
		std::vector<std::vector<float>> neuronInputWeights;
		int neuInBias;
		int numLabels;
		void setNeuronsOut();
	public:
		FullyConnected(std::vector<std::vector<float>> convFlattened,int numLabels,std::vector<std::vector<float>> weights);
		FullyConnected(std::vector<std::vector<float>> convFlattened, int numLabels);
		void setWeights(std::vector<std::vector<float>> weigths);
		void setBias(float bias);
		void mostrarWeights();
		void mostrarInput();
		void mostrarOutput();
		std::vector<float> getNeuronsIn();
		std::vector<float> applySoftmax();
		std::vector<std::vector<float>> getInputWeights();
	};
}


#endif
