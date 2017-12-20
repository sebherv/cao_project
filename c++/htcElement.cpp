//
// Created by Sebastien Hervieu on 19/12/2017.
//

#include "htcElement.h"

HctElement::HctElement(triangle elementTriangle) : mTriangle(elementTriangle) {}


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
    // D'abord calculer u

}

void HctElement::compute_e() {
    int i = 0;
    int j = 0;
    int k = 0;

    while (circularPermutation(i, j, k)) {
        e[k] = (d[k] + g[i] + g[j])/3;
    }
}



