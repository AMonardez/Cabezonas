#include "Convolution.h"
#include <thread>
using namespace std;

namespace ReconLib {
    Convolution::Convolution(std::vector<Matriz> imagen) {
        for (Matriz m:imagen) {
            addImageIn(m);
        }
        setFilters();
    }

    void Convolution::setFilters() {
        //Filtro gaussiano diagonales
        Matriz fil1(3, 3);
        fil1.set(0, 0, -1);
        fil1.set(0, 1, -1);
        fil1.set(0, 2, -1);
        fil1.set(1, 0, -1);
        fil1.set(1, 1,  8);
        fil1.set(1, 2, -1);
        fil1.set(2, 0, -1);
        fil1.set(2, 1, -1);
        fil1.set(2, 2, -1);
        this->filters.push_back(fil1);

        //Sobel horizontal
        Matriz fil2(3, 3);
        fil2.set(0, 0, -1);
        fil2.set(0, 1, -2);
        fil2.set(0, 2, -1);
        fil2.set(1, 0, 0);
        fil2.set(1, 1, 0);
        fil2.set(1, 2, 0);
        fil2.set(2, 0, 1);
        fil2.set(2, 1, 2);
        fil2.set(2, 2, 1);
        this->filters.push_back(fil2);

        //Sobel vertical
        Matriz fil3(3, 3);
        fil3.set(0, 0, -1);
        fil3.set(0, 1, 0);
        fil3.set(0, 2, 1);
        fil3.set(1, 0, -2);
        fil3.set(1, 1, 0);
        fil3.set(1, 2, 2);
        fil3.set(2, 0, -1);
        fil3.set(2, 1, 0);
        fil3.set(2, 2, 1);
        this->filters.push_back(fil3);

        ////Gaussiano horizontalvertical
        //Matriz fil4(3, 3);
        //fil4.set(0, 0, 0);
        //fil4.set(0, 1, -1);
        //fil4.set(0, 2, 0);
        //fil4.set(1, 0, -1);
        //fil4.set(1, 1, 4);
        //fil4.set(1, 2, -1);
        //fil4.set(2, 0, 0);
        //fil4.set(2, 1, -1);
        //fil4.set(2, 2, 0);
        //this->filters.push_back(fil4);

        this->fillNum = filters.size();
    }

    void Convolution::addImageIn(Matriz imagen) {
        this->ImagenIn.push_back(imagen);
    }

    std::vector<Matriz> Convolution::getImageOut() {
        convolutionFunction();
        return this->ImagenOut;
    }
    
    void Convolution::convolve(Matriz m, Matriz fil, Matriz &out) {
        Matriz mf(m.ancho - (fil.ancho - 1), m.alto - (fil.alto - 1));
        for (int i = 0; i < mf.alto; i++) {
            for (int j = 0; j < mf.ancho; j++) {
                mf.set(i, j, m.mulMatriz(m.subMatriz(m, i, j, fil.ancho), fil));
            }
        }
        Matriz final=Activations().ReLuApply(mf);
        out = final;
    }

    void Convolution::convolutionFunction() {
        //Version monohilo lentaaaaaaaaaaaaaaaaa
        std::vector<Matriz>convolutas(this->ImagenIn.size()*this->filters.size(), Matriz());
        int i = 0;
        for (Matriz m : this->ImagenIn) {
            for (Matriz fil : this->filters) {
                convolve(m, fil, convolutas.at(i));
                i++;
            }
        }
        ImagenOut = convolutas;
    }

    void Convolution::convolutionFunction_nothread() {
        //Version multihilo pulentaaaaaaaaaaaaa
        std::vector<Matriz>convolutas(this->ImagenIn.size() * this->filters.size(), Matriz());
        int i = 0;
        vector<thread> hilos;
        for (Matriz m : this->ImagenIn) {
            for (Matriz fil : this->filters) {
                hilos.push_back(thread(convolve, m, fil, ref(convolutas.at(i))));
                i++;
            }
        }
        for (auto& th : hilos) th.join();
        ImagenOut = convolutas;
    }
}
