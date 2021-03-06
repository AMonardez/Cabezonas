#ifndef Convolution_H
#define Convolution_H

#include <vector>
#include "Matriz.h"
#include "Image.h"
#include "Layer.h"
#include "Activations.h"

namespace ReconLib {
	class Convolution
	{
	private:
		int fillNum;
		std::vector<Matriz> filters;
		std::vector<Matriz> ImagenIn;
		std::vector<Matriz> ImagenOut;
	public:
		Convolution(std::vector<Matriz> imagen);
		void addImageIn(Matriz imagen);
		void setFilters();
		void convolutionFunction();
		void convolutionFunction_nothread();
		static void convolve(Matriz m, Matriz fil, Matriz& out);
		std::vector<Matriz> getImageOut();
	};
}
#endif

