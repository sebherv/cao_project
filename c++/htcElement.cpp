//
// Created by Sebastien Hervieu on 19/12/2017.
//

#include <cmath>
#include "htcElement.h"

HctElement::HctElement(triangle elementTriangle)
        : mTriangle(elementTriangle), mCoefficientCalculated(false) {}


bool HctElement::circularPermutation(int &i, int &j, int &k) {
    if(i == 0 && j == 0 && k == 0) {
        i = 1; j = 2; k = 3;
        return true;
    }

    if(i == 1) {
        i = 2; j = 3; k = 1;
        return true;
    }

    if (i == 2) {
        i = 3; j = 1; k = 2;
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
}

void HctElement::compute_a() {
    for(int i = 0; i < 3; i++) {
        a[i] = mTriangle.getPoint(i).get_f();
    }
}

void HctElement::compute_p_and_q() {
    int i=0; int j=0; int k=0;

    while (circularPermutation(i,j,k)) {

        double aj_dx = mTriangle.getPoint(j).get_df_dx();
        double aj_dy = mTriangle.getPoint(j).get_df_dy();

        double ak_dx = mTriangle.getPoint(k).get_df_dx();
        double ak_dy = mTriangle.getPoint(k).get_df_dy();

        double aj_ak_x = mTriangle.getPoint(j).get_x() - mTriangle.getPoint(k).get_x();
        double aj_ak_y = mTriangle.getPoint(j).get_y() - mTriangle.getPoint(k).get_y();

        double ak_aj_x = -aj_ak_x;
        double ak_aj_y = -aj_ak_y;

        p[j] = aj_dx * aj_ak_x + aj_dy * aj_ak_y;
        q[k] = ak_dx * ak_aj_x + ak_dy * ak_aj_y;

    }
}

void HctElement::compute_b() {
    for(int i = 0; i < 3; i++) {
        b[i] = a[i] + p[i]/3;
    }
}

void HctElement::compute_c() {
    for(int i = 0; i < 3; i++) {
        c[i] = a[i] + q[i]/3;
    }
}

void HctElement::compute_d() {
    for(int i = 0; i < 3; i++) {
        d[i] = (a[i] + b[i] + c[i])/3;
    }
}

void HctElement::compute_g() {
    int i=0; int j=0; int k=0;
    while(circularPermutation(i,j,k)) {

        // D'abord calculer u
        double omega_x = mTriangle.getOmega_x();
        double omega_y = mTriangle.getOmega_y();
        double ak_x = mTriangle.getPoint(k).get_x();
        double ak_y = mTriangle.getPoint(k).get_y();
        double aj_x = mTriangle.getPoint(j).get_x();
        double aj_y = mTriangle.getPoint(j).get_y();

        double den_u = pow(aj_x - ak_x,2.0) + pow(aj_y - ak_y,2.0);
        double num_u = 2 * ((omega_x - ak_x) * (aj_x - ak_x) + (omega_y - ak_y) * (aj_y - ak_y));
        double u = num_u / den_u;

        g[i] = (2*(d[k]+d[j]) + (4-3*u)*c[k] + (u-2)*a[k] + (3*u-2)*b[j] - u*a[j]/4);
    }

}

void HctElement::compute_e() {
    int i = 0;
    int j = 0;
    int k = 0;

    while (circularPermutation(i, j, k)) {
        e[k] = (d[k] + g[i] + g[j])/3;
    }
}

void HctElement::compute_om() {
    om = (e[1] + e[2] + e[3])/3;
}

double HctElement::interpolate(double x, double y) {
    if(!mCoefficientCalculated) {
        computeCoefficients();
    }

    // Dans quel sous-triangle le point est-il?

    // Calculer l'interpolation.
    return 0;
}



