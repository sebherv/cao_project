//
// Created by anais on 19/12/2017.
//


#include <cmath>
#include "FInterpolator.h"

FInterpolator::FInterpolator(std::vector<point> pointList, double minX, double maxX, double minY, double maxY)
        : FunctionInterpolator(pointList, minX, maxX, minY, maxY) {}

double FInterpolator::getf(double x, double y) {
    return exp(x+y);
}

double FInterpolator::getf_dx(double x, double y) {
    return exp(x+y);
}

double FInterpolator::getf_dy(double x, double y) {
    return exp(x+y);
}

