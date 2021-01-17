#include "Convolution.h"

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



    void Convolution::convolutionFunction(int fill_num) {
        //Layer L = Layer();
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
