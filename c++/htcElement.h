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
    void compute_a();
    bool circularPermutation(int& i, int &j, int& k);
    void compute_p_and_q();
    void compute_b();
    void compute_c();
    void compute_g();
    void compute_d();
    void compute_e();

public:
    HctElement(triangle elementTriangle);
    void computeCoefficients();
};


#endif //C_HTCELEMENT_H
