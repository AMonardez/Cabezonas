//#pragma once
#ifndef Layer_H
#define Layer_H

#include "Matriz.h"
#include <vector>
#include <iostream>
#include <cmath>

namespace ReconLib {
	class Layer {
	public:
		std::vector<Matriz> Imagenes;
		Layer();
		Layer(std::vector<Matriz> inputs);

		Matriz maxpooling(Matriz matrix);
		std::vector<std::vector<float>> flatten(std::vector<Matriz> vector_matrix);
	};
}

#endif