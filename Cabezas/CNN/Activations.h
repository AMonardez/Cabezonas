#ifndef Activations_H
#define Activations_H

#include<vector>
#include "Matriz.h"

namespace ReconLib {

	class Activations
	{
	public:
		//hacer las clases statics
		std::vector<float> softmax(std::vector<float> input);
		std::vector<float> hardmax(std::vector<float> input);
		int argmax(std::vector<float> input);
		float crossentropy(std::vector<float> prob, std::vector<float> labelcorrecto);
		void Mostrar(std::vector<float> input);
		void testeo();
		float ReLu(float relu);
		Matriz ReLuApply(Matriz m);
	};
}
#endif
