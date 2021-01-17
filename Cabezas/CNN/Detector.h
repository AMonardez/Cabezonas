#ifndef Detector_H
#define Detector_H

#include "Matriz.h"
#include <string>

namespace ReconLib {
	class Detector {
	private:
		Matriz weights;
		int n_convolutions=2;
		int n_maxpoolings=2;
		int anchoTrainingImage = 32;
		int altoTrainingImage = 32;
		int labels = 2;
		std::string rutapesos;
		std::vector<std::string> etiquetas = { "Cabeza", "No cabeza" };
	public:
		Detector(std::string ruta_archivo_pesos);
		std::vector<float> predict(Matriz image);
		std::vector<struct label> scanPredict(std::string ruta);
		void train(int epochs, float learningRate);
		void validate(std::string rutacarpeta, std::vector<float> labelscorrectos);
	};	
}
#endif


