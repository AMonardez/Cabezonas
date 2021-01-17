#include "Convolution.h"
//#include "Matriz.h"
#include "Layer.h"
#include "Activations.h"

namespace ReconLib {

    Convolution::Convolution(std::vector<Matriz> imagen) {
        for (Matriz m:imagen) {
            addImageIn(m);
        }
        setFilters();
    }

    void Convolution::setFilters() {
        Matriz fil1(3, 3); //bottom border
        Matriz fil2(3, 3); //right border
        Matriz fil3(3, 3); //top border
        Matriz fil4(3, 3); //lefth border

        //Matriz fil1w(3, 3); //bottom border weights
        //Matriz fil2w(3, 3); //right border weights
        //Matriz fil3w(3, 3); //top border weights
        //Matriz fil4w(3, 3); //lefth border weights

        //Matriz fil1B(3, 3);

        //std::cout << "Setting Filter1 \n";
        fil1.set(0, 0, -1);
        fil1.set(0, 1, -1);
        fil1.set(0, 2, -1);
        fil1.set(1, 0, 1);
        fil1.set(1, 1, 1);
        fil1.set(1, 2, 1);
        fil1.set(2, 0, 0);
        fil1.set(2, 1, 0);
        fil1.set(2, 2, 0);

        //std::cout << "Setting Filter2 \n";
        fil2.set(0, 0, -1);
        fil2.set(0, 1, 1);
        fil2.set(0, 2, 0);
        fil2.set(1, 0, -1);
        fil2.set(1, 1, 1);
        fil2.set(1, 2, 0);
        fil2.set(2, 0, -1);
        fil2.set(2, 1, 1);
        fil2.set(2, 2, 0);

        //std::cout << "Setting Filter3 \n";
        fil3.set(0, 0, 0);
        fil3.set(0, 1, 0);
        fil3.set(0, 2, 0);
        fil3.set(1, 0, 1);
        fil3.set(1, 1, 1);
        fil3.set(1, 2, 1);
        fil3.set(2, 0, -1);
        fil3.set(2, 1, -1);
        fil3.set(2, 2, -1);

        //std::cout << "Setting Filter4 \n";
        fil4.set(0, 0, 0);
        fil4.set(0, 1, 1);
        fil4.set(0, 2, -1);
        fil4.set(1, 0, 0);
        fil4.set(1, 1, 1);
        fil4.set(1, 2, -1);
        fil4.set(2, 0, 0);
        fil4.set(2, 1, 1);
        fil4.set(2, 2, -1);

        //Iniciar pesos de los filtros en 1
        //Iniciar Bias en 0
        /*for (int i = 0; i < fil1w.size(); i++) {
            fil1w.numeros[i] = 0;
            fil2w.numeros[i] = 0;
            fil3w.numeros[i] = 0;
            fil4w.numeros[i] = 0;
            fil1B.numeros[i] = 0;
        }*/

        /*Matriz pesos(3, 3);*/

        /*for (int i = 0; i < pesos.alto; i++) {
            for (int j = 0; j < pesos.ancho; j++) {
                pesos.set(i, j, 1);
            }
        }*/

        /*this->filtersW.push_back(fil1w);
        this->filtersW.push_back(fil2w);
        this->filtersW.push_back(fil3w);
        this->filtersW.push_back(fil4w);
        this->setFilterBias(fil1B);*/

        /*setFilterW(0, pesos);
        setFilterW(1, pesos);
        setFilterW(2, pesos);
        setFilterW(3, pesos);*/

        this->filters.push_back(fil1);
        this->filters.push_back(fil2);
        this->filters.push_back(fil3);
        this->filters.push_back(fil4);
        // this->filters.at(0).mostrar();
        // this->filters.at(1).mostrar();
        // this->filters.at(2).mostrar();
        // this->filters.at(3).mostrar();

        this->fillNum = filters.size();
    }

    void Convolution::addImageIn(Matriz imagen) {
        this->ImagenIn.push_back(imagen);
    }

    std::vector<Matriz> Convolution::getImageOut() {
        convolutionFunction(this->fillNum);
        return this->ImagenOut;
    }

	Matriz Convolution::getFilter(int filtro) {
		return this->filters.at(filtro);
	}

	Matriz Convolution::getFilterW(int filtro) {
		return this->filtersW.at(filtro);
	}

	std::vector<Matriz> Convolution::getFilters() {
		return this->filters;
	}

	std::vector<Matriz> Convolution::getFiltersW() {
		return this->filtersW;
	}
	void Convolution::setFilter(int filtro,Matriz m) {
		for (int i = 0; i < m.alto; i++) {
			for (int j = 0; j < m.ancho; j++) {
				this->filters.at(filtro).set(i, j, m.get(i, j));
			}
		}
	}

	void Convolution::setFilterW(int filtro,Matriz m) {
		for (int i = 0; i < m.alto; i++) {
			for (int j = 0; j < m.ancho; j++) {
				this->filtersW.at(filtro).set(i, j, m.get(i, j));
			}
		}
	}
    void Convolution::setFilterBias(Matriz bias) {
        this->filterB = Matriz(bias.ancho, bias.alto);
        for (int i = 0; i < bias.alto; i++) {
            for (int j = 0; j < bias.ancho; j++) {
                this->filterB.set(i,j,bias.get(i,j));
            }
        }
    }


    void Convolution::convolutionFunction(int fill_num) {
        Layer L = Layer();
        int contador = 0;
        for (Matriz m : this->ImagenIn) {
            contador = 0;
            for (Matriz fil : this->filters) {
                if (contador < fill_num) {
                    
                    Matriz mf(m.ancho - (fil.ancho - 1), m.alto - (fil.alto - 1));
                    
                    for (int i = 0; i < mf.alto; i++) {
                        for (int j = 0; j < mf.ancho; j++) {
                            //Matriz mi = m.subMatriz(m, i, j, fil.ancho);
                            /*mi = m.mulMatrizTerm(mi, this->filtersW.at(contador));
                            mi = mi.plusMatrizTerm(this->filterB);*/
                    
                            mf.set(i, j, m.mulMatriz(m.subMatriz(m, i, j, fil.ancho), fil));
                        }
                    }
                    //std::cout << "El resultado del filtro es: " << '\n';
                    //mf.mostrar();
                    /*std::cout << '\n';
                    mf.mostrar();
                    std::cout << '\n';*/
                    this->ImagenOut.push_back(Activations().ReLuApply(mf));
                }
                else {
                    break;
                }
                contador++;
            }
        }
        //std::cout << "El tamano del vector de salida es: " << this->ImagenOut.size() << '\n';
    }
}
