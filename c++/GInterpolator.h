//
// Created by anais on 15/01/2018.
//

#ifndef C_FONCTION_G_H
#define C_FONCTION_G_H


#include "FunctionInterpolator.h"

class GInterpolator : public FunctionInterpolator {
public:
    GInterpolator(const std::vector<point> &pointList, double minX, double maxX, double minY, double maxY);

    double getf(double x, double y) override ;
    double getf_dx(double x, double y) override ;
    double getf_dy(double x, double y) override ;
};

#endif //C_FONCTION_G_H
