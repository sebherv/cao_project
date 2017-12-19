//
// Created by Sebastien Hervieu on 19/12/2017.
//

#include "htcElement.h"

HctElement::HctElement(triangle elementTriangle) : mTriangle(elementTriangle) {}


void HctElement::computeCoefficients() {
    performCircularPermutation(1,2,3);
    performCircularPermutation(2,3,1);
    performCircularPermutation(3,1,2);
}

void HctElement::performCircularPermutation(int i, int j, int k) {

    // Compute aj
    //a[j]=mTriangle.getPoint(j).get_f();

}
