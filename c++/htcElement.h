//
// Created by Sebastien Hervieu on 19/12/2017.
//

#ifndef C_HTCELEMENT_H
#define C_HTCELEMENT_H

#include <array>
#include "triangle.h"

class HctElement : public triangle{
private:

    bool mCoefficientCalculated;

    std::array<double,3> a;
    std::array<double,3> b;
    std::array<double,3> c;
    std::array<double,3> d;
    std::array<double,3> e;
    double om;
    std::array<double,3> g;
    std::array<double,3> p;
    std::array<double,3> q;
    std::array<triangle, 3> mSubTriangles;

    // Private methods
    bool circularPermutation(int& i, int &j, int& k);
    void compute_a();
    void compute_p_and_q();
    void compute_b();
    void compute_c();
    void compute_g();
    void compute_d();
    void compute_e();
    void compute_om();

    void generateSubTriangles();
    void computeCoefficients();

public:
    HctElement(int idTriangle, point pt1, point pt2, point pt3);
    double interpolate(double x, double y);

    double compute(int triangleIndex, double x, double y);
};


#endif //C_HTCELEMENT_H
