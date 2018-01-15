//
// Created by Sebastien Hervieu on 19/12/2017.
//

#include <cmath>
#include <string>
#include <sstream>
#include "HtcElement.h"

HctElement::HctElement(int idTriangle, point pt1, point pt2, point pt3)
        : triangle(idTriangle, pt1,  pt2,  pt3), mCoefficientCalculated(false) {}


bool HctElement::circularPermutation(int &i, int &j, int &k) {
    if(i == -1 && j == -1 && k == -1) {
        i = 0; j = 1; k = 2;
        return true;
    }

    if(i == 0) {
        i = 1; j = 2; k = 0;
        return true;
    }

    if (i == 1) {
        i = 2; j = 0; k = 1;
        return true;
    }

    return false;
}

void HctElement::computeCoefficients() {
    compute_a();
    compute_p_and_q();
    compute_b();
    compute_c();
    compute_d();
    compute_g();
    compute_e();
    compute_om();
}

void HctElement::compute_a() {
    for(int i = 0; i < 3; i++) {
        a[i] = getPoint(i).get_f();
    }
}

void HctElement::compute_p_and_q() {
    int i=-1; int j=-1; int k=-1;

    while (circularPermutation(i,j,k)) {

        double aj_dx = getPoint(j).get_df_dx();
        double aj_dy = getPoint(j).get_df_dy();

        double ak_dx = getPoint(k).get_df_dx();
        double ak_dy = getPoint(k).get_df_dy();

        double aj_ak_x = getPoint(k).get_x() - getPoint(j).get_x();
        double aj_ak_y = getPoint(k).get_y() - getPoint(j).get_y();

        double ak_aj_x = -aj_ak_x;
        double ak_aj_y = -aj_ak_y;

        p[j] = aj_dx * aj_ak_x + aj_dy * aj_ak_y;
        q[k] = ak_dx * ak_aj_x + ak_dy * ak_aj_y;

    }
}

void HctElement::compute_b() {
    for(int j = 0; j < 3; j++) {
        b[j] = a[j] + p[j]/3;
    }
}

void HctElement::compute_c() {
    for(int k = 0; k < 3; k++) {
        c[k] = a[k] + q[k]/3;
    }
}


void HctElement::compute_d() {
    for(int k = 0; k < 3; k++) {
        d[k] = (a[k] + b[k] + c[k])/3;
    }
}

void HctElement::compute_g() {
    int i=-1; int j=-1; int k=-1;
    while(circularPermutation(i,j,k)) {

        // D'abord calculer u
        double omega_x = getOmega_x();
        double omega_y = getOmega_y();
        double ak_x = getPoint(k).get_x();
        double ak_y = getPoint(k).get_y();
        double aj_x = getPoint(j).get_x();
        double aj_y = getPoint(j).get_y();

        double den_u = (ak_x - aj_x)*(ak_x - aj_x) +(ak_y - aj_y)*(ak_y - aj_y);
        double num_u = 2 * ((ak_x - omega_x) * (ak_x - aj_x) + (ak_y - omega_y) * (ak_y - aj_y));
        double u = num_u / den_u;

        g[i] = (2*(d[k]+d[j]) + (4-3*u)*c[k] + (u-2)*a[k] + (3*u-2)*b[j] - u*a[j])/4;
    }

}

void HctElement::compute_e() {
    int i=-1; int j=-1; int k=-1;
    while (circularPermutation(i, j, k)) {
        e[k] = (d[k] + g[i] + g[j])/3;
    }
}

void HctElement::compute_om() {
    om = (e[0] + e[1] + e[2])/3;
}

double HctElement::interpolate(double x, double y) {
    if(!mCoefficientCalculated) {
        computeCoefficients();
        generateSubTriangles();
        mCoefficientCalculated = true;
    }

    // Dans quel sous-triangle le point est-il?
    int subtriangleIndex = -1;
    for(int i = 0; i < 3; i++) {
        if(mSubTriangles[i].isInside(x,y)) {
            subtriangleIndex = i;
        }
    }

    if(subtriangleIndex == -1) {
        // We should not arrive here
        throw std::domain_error("Error in HctInterpolator::interpolate: subtriangle not found");
    }

    // Calculer l'interpolation.
    return compute(subtriangleIndex, x, y);
}

void HctElement::generateSubTriangles() {
    mSubTriangles[0] = triangle(id*100 + 1, point(0,getOmega_x(), getOmega_y()), getPoint(1), getPoint(2));
    mSubTriangles[1] = triangle(id*100 + 2, point(0,getOmega_x(), getOmega_y()), getPoint(2), getPoint(0));
    mSubTriangles[2] = triangle(id*100 + 3, point(0,getOmega_x(), getOmega_y()), getPoint(0), getPoint(1));
}

double HctElement::compute(int triangleIndex, double x, double y) {
    double l1, l2, l3;

    mSubTriangles[triangleIndex].getBarycentricFromCartesian(x,y,l1, l2, l3);

    int i, j, k;

    if(triangleIndex == 0) {
        i = 0; j = 1; k = 2;
    } else if(triangleIndex == 1) {
        i = 1; j = 2; k = 0;
    } else if (triangleIndex == 2) {
        i = 2; j = 0; k = 1;
    }

    double si = a[k] * l3*l3*l3
                + 3 * c[k] * l2 * l3*l3
                + 3 * b[j] * l2*l2 * l3
                + a[j] * l2*l2*l2
                + 3 * d[k] *l1 * l3*l3
                + 6 * g[i] * l1 * l2 * l3
                + 3 * d[j] * l1 * l2*l2
                + 3 * e[k] * l1*l1 * l3
                + 3 * e[j] * l1*l1 * l2
                + om * l1*l1*l1;

    return si;
}


std::string HctElement::getOutputLine() {

    std::ostringstream oss;

    oss << id << "\t";

    for(int i = 0; i < 3 ; i++) {
        oss << getPoint(i).get_id() << "\t";
    }
    oss << "\n";

    return oss.str();
}




