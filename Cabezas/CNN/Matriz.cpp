//#pragma once
#include "Matriz.h"
#include <opencv2/core/mat.hpp>

namespace ReconLib {

	Matriz::Matriz(int dimension) {
		this->alto = dimension;
		this->ancho = dimension;
		//numeros = new float[ancho * alto];
		//this->numeros = (float*)malloc(sizeof(float) * ancho * alto);
		rellenar(-1);
	}

	Matriz::Matriz(int _ancho, int _alto) {
		this->alto = _alto;
		this->ancho = _ancho;
		//this->numeros = (float*)malloc(sizeof(float) * ancho * alto);
		//numeros = new float[ancho * alto];
		rellenar(-1);
	}

	Matriz::Matriz() {
		this->alto = 0;
		this->ancho = 0;
		//this->numeros = NULL;
	}

	Matriz::Matriz(std::vector<std::vector<float>> vectorIn) {
		this->alto = vectorIn.size();
		this->ancho = vectorIn.at(0).size();
		//this->numeros = (float*)malloc(sizeof(float) * ancho * alto);
		//numeros = new float[ancho * alto];
		rellenar(-1);
		//Matriz mat(vectorIn.size(), vectorIn.at(0).size());
		std::vector<float> fila;
		for (int i = 0; i < vectorIn.size(); i++) {
			fila = vectorIn.at(i);
			for (int j = 0; j < fila.size(); j++) {
				set(i, j, fila.at(j));
			}
		}

	}

	float Matriz::get(int i, int j) {
		return this->numeros[i * ancho + j];
	}

	void Matriz::set(int i, int j, float valor) {
		this->numeros[i * ancho + j] = valor;
	}

	int Matriz::size(){
		return(this->alto * this->ancho);
	}

	void Matriz::mostrar()
	{
		for (int i = 0; i < alto; i++) {
			for (int j = 0; j < ancho; j++) {
				printf("%.3f ", get(i, j));
				//std::cout << get(i, j) << " ";
			}
			std::cout << "\n";
		}
	}

	void Matriz::mostrardim()
	{
		std::cout << "Dimension: " <<this->ancho<<"x"<<this->alto <<std::endl;
	}

	void Matriz::rellenar(float relleno)
	{
		for (int i = 0; i < this->alto; i++) {
			for (int j = 0; j < this->ancho; j++) {
				//this->numeros[i * this->ancho + j] = relleno;
				numeros.push_back(relleno);
			}
		}
	}


	float Matriz::mulMatriz(Matriz m, Matriz f) {
		float res = 0;
		for (int i = 0; i < m.alto; i++) {
			for (int j = 0; j < m.ancho; j++) {
				res += m.get(i, j) * f.get(i, j);
				//std::cout<<"i: "<<i<<" j: "<<j<<" res: "<<res<<'\n';
			}
		}
		return res;
	}

	Matriz Matriz::mulMatrizTerm(Matriz m1, Matriz m2) {
		Matriz res(m1.ancho, m1.alto);
		for (int i = 0; i < m1.alto; i++) {
			for (int j = 0; j < m1.ancho; j++) {
				res.set(i, j, m1.get(i, j) * m2.get(i, j));
			}
		}
		return res;
	}

	Matriz Matriz::mulByScalar(float scalar) {
		Matriz res(ancho,alto);
		for (int i=0; i < alto;i++) {
			for (int j=0; j < ancho;j++) {
				res.set(i,j,this->get(i,j)*scalar);
			}
		}
		return res;
	}

	Matriz Matriz::plusMatrizTerm(Matriz m2) {
		Matriz res(ancho,alto);
		for (int i = 0; i < alto; i++) {
			for (int j = 0; j < ancho; j++) {
				res.set(i, j, get(i, j) + m2.get(i, j));
			}
		}
		return res;
	}

	Matriz Matriz::subtractMatrizTerm(Matriz m1, Matriz m2) {
		Matriz res(m1.ancho, m1.alto);
		for (int i = 0; i < m1.alto; i++) {
			for (int j = 0; j < m1.ancho; j++) {
				res.set(i, j, m1.get(i, j) - m2.get(i, j));
			}
		}
		return res;
	}



	Matriz Matriz::subMatriz(Matriz m, int i, int j, int kernel) {
		Matriz sub(kernel);
		for (int x = 0; x < kernel; x++) {
			for (int y = 0; y < kernel; y++) {
				sub.set(x, y, m.get(i + x, j + y));
			}
		}
		return sub;
	}

	Matriz Matriz::subMatriz(int i,int j, int ancho, int alto) {
		Matriz sub(ancho,alto);
		for (int x = 0; x < alto; x++) {
			for (int y = 0; y < ancho; y++) {
				sub.set(x, y, get(i + x, j + y));
			}
		}
		return sub;
	}

	float Matriz::grtNumMatriz(Matriz m) {
		float great = m.get(0, 0);
		for (int i = 0; i < m.alto; i++) {
			for (int j = 0; j < m.ancho; j++) {
				if (m.get(i, j) > great) {
					great = m.get(i, j);
					//std::cout<< great <<'\n';
				}
			}
		}
		//std::cout<< m.ancho <<" "<<m.alto<<" " <<great <<'\n';	
		return great;
	}

	Matriz Matriz::paddingAncho(Matriz m) {
		Matriz mAncho(m.ancho + 1, m.alto);
		for (int i = 0; i < m.alto; i++) {
			for (int j = 0; j < m.ancho; j++) {
				mAncho.set(i, j, m.get(i, j));
			}
		}
		for (int n = 0; n < m.alto; n++) {
			mAncho.set(n, m.ancho, 0);
		}
		return mAncho;
	}

	Matriz Matriz::paddingAlto(Matriz m) {
		Matriz mAlto(m.ancho, m.alto + 1);
		for (int i = 0; i < m.alto; i++) {
			for (int j = 0; j < m.ancho; j++) {
				mAlto.set(i, j, m.get(i, j));
			}
		}
		for (int n = 0; n < m.ancho; n++) {
			mAlto.set(m.alto, n, 0);
		}
		return mAlto;
	}

	Matriz Matriz::padding(Matriz m) {
		if (m.ancho % 2 != 0) {
			return paddingAncho(m);
		}
		else if (m.alto % 2 != 0)
		{
			return paddingAlto(m);
		}
		else if (m.alto % 2 != 0 && m.ancho % 2 != 0) {
			Matriz m2(m.ancho + 1, m.alto);
			m2 = paddingAncho(m);
			Matriz m3(m2.ancho, m2.alto + 1);
			m3 = paddingAlto(m2);
		}
		return m;

	}

	std::vector<int> Matriz::paddSize(Matriz m) {
		std::vector<int> size;
		if (m.ancho % 2 != 0) {
			size.push_back(m.ancho + 1);
			size.push_back(m.alto);
			return size;
		}
		else if (m.alto % 2 != 0)
		{
			size.push_back(m.ancho);
			size.push_back(m.alto + 1);
			return size;
		}
		else if (m.alto % 2 != 0 && m.ancho % 2 != 0) {
			size.push_back(m.ancho + 1);
			size.push_back(m.alto + 1);
			return size;
		}
		size.push_back(m.ancho);
		size.push_back(m.alto);
		return size;
	}

	std::vector<std::vector<float>> Matriz::toVector(){
		std::vector<std::vector<float >> v;
		std::vector<float> fila;
		for(int i=0; i<alto; i++){
			fila.clear();
			for(int j=0; j<ancho; j++){				
				fila.push_back((float)get(i, j));
			}
			v.push_back(fila);
		}
		return v;
	}

}