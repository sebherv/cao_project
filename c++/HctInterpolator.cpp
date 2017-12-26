//
// Created by Sebastien Hervieu on 26/12/2017.
//

#include <cstdlib>
#include "HctInterpolator.h"

HctInterpolator::HctInterpolator(std::vector<HctElement> elements) {
    m_hctElements = elements;
}

pointResult HctInterpolator::interpolate(double x, double y) {
    // Find element to which the point belongs
    HctElement element = findElement(x,y);

    // Compute interpolate on the found out element
    double z = element.interpolate(x,y);

    //  return
    return pointResult(x, y, z, 0);
}

HctElement HctInterpolator::findElement(double x, double y) {
    for (auto &element : m_hctElements) {
        double l1, l2, l3;
        element.getBarycentricFromCartesian(x,y,l1,l2,l3);
        if((l1 >= 0) && (l1 <= 1)
           && (l2 >= 0) && (l2 <= 1) && (l3 >= 0 && l3 <= 1)) {
            return  element;
        }
    }

    // We should not arrive here
    exit(-1);
}

