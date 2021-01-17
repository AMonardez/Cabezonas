#ifndef Label_H
#define Label_H
#include<string>
#include <stdlib.h>
#include "ReconLib.h"
namespace ReconLib {

    struct label {
        int x = -1;
        int y = -1;
        std::string clasificacion = "";
        int n_clasificacion = -1;
        float precision = 0.0f;

        void mostrar() {
            std::cout << "Clasificacion:" << clasificacion << "\n";
            std::cout << "X: " << x << "\n";
            std::cout << "Y: " << y << "\n";
            std::cout << "Precision: " << precision << "\n";
        }

        float calculateAngle(struct label l2) {

            float angle = (atan2(this->y - l2.y, this->x - l2.x) * 180.0) / 3.14159265;
            return angle;
        }
    };
}
#endif