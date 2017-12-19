//
// Created by Sebastien Hervieu on 19/12/2017.
//

#ifndef C_HTCELEMENT_H
#define C_HTCELEMENT_H

#include <array>
#include "triangle.h"

class HctElement {
private:

    triangle mTriangle;

    std::array<double,3> a;
    std::array<double,3> b;
    std::array<double,3> c;
    std::array<double,3> d;
    std::array<double,3> e;
    double om;
    std::array<double,3> g;
    std::array<double,3> p;
    std::array<double,3> q;

    // Private methods
    void performCircularPermutation(int i, int j, int k);

public:
    HctElement(triangle elementTriangle);
    void computeCoefficients();
};


#endif //C_HTCELEMENT_H
