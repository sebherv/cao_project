//
// Created by anais on 15/01/2018.
//

#include "GInterpolator.h"

GInterpolator::GInterpolator(const std::vector<point> &pointList, double minX, double maxX, double minY, double maxY)
        : FunctionInterpolator(pointList, minX, maxX, minY, maxY) {}

double GInterpolator::getf(double x, double y) {
    return y*y*y-2*x*y*y-5*x*x*y+10*x*y+1;
}

double GInterpolator::getf_dx(double x, double y) {
    return -2*y*y-10*x*y+10*y;
}

double GInterpolator::getf_dy(double x, double y) {
    return 3*y*y-4*x*y-5*x*x+10*x;
}

