#ifndef Convolution_H
#define Convolution_H

#include <vector>
#include "Matriz.h"
#include "Image.h"

namespace ReconLib {
	class Convolution
	{
	private:
		int fillNum;
		std::vector<Matriz> filters;
		std::vector<Matriz> filtersW;
		Matriz filterB;
		std::vector<Matriz> ImagenIn; //Imagenes para ser convolucionadas
		std::vector<Matriz> ImagenOut;
	public:
		Convolution(std::vector<Matriz> imagen);
		void addImageIn(Matriz imagen);
		void setFilters();
		void setFilter(int filtro, Matriz nuevosFiltros);
		void setFilterW(int filtro,Matriz nuevosFiltrosW);
		void setFilterBias(Matriz nuevoBias);
		void convolutionFunction(int fill_num);
		std::vector<Matriz> getImageOut();
		Matriz getFilter(int filtro);
		Matriz getFilterW(int filtro);
		std::vector<Matriz> getFilters();
		std::vector<Matriz> getFiltersW();
	};
}
#endif

