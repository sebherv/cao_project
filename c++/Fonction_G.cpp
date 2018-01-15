//
// Created by anais on 15/01/2018.
//

#include "Fonction_G.h"

double Fonction_G::getg(double x, double y) {
    return y*y*y-2*x*y*y-5*x*x*y+10*x*y+1;
}

double Fonction_G::getg_dx(double x, double y) {
    return 2*y*y-10*x*y+10*y;
}

double Fonction_G::getg_dy(double x, double y) {
    return 3*y*y-4*x*y-5*x*x+10*x;
}