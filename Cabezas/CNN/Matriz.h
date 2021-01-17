//#pragma once
#ifndef Matriz_H
#define Matriz_H

#include <vector>
#include <iostream>

namespace ReconLib {

	class Matriz
	{
	public:
		std::vector<float> numeros;
		int alto;
		int ancho;
		Matriz(int ancho, int alto);
		Matriz(int dimension);
		Matriz();
		void mostrar();
		void rellenar(float relleno);
		float get(int i, int j);
		void set(int i, int j, float valor);
		int size();
		float mulMatriz(Matriz m, Matriz f);
		Matriz mulMatrizTerm(Matriz m1, Matriz m2);
		Matriz mulByScalar(float scalar);
		Matriz plusMatrizTerm(Matriz m2);
		Matriz subtractMatrizTerm(Matriz m1, Matriz m2);
		Matriz subMatriz(Matriz m, int i, int j, int kernel);
		Matriz subMatriz(int i,int j,int ancho,int alto);
		float grtNumMatriz(Matriz m);
		Matriz paddingAncho(Matriz m);
		Matriz paddingAlto(Matriz m);
		Matriz padding(Matriz m);
		std::vector<int> paddSize(Matriz m);
		Matriz(std::vector<std::vector<float>> vectorIn);

		std::vector<std::vector<float>> toVector();
		
		//~Matriz();
	};
}
#endif // !Matriz_H

