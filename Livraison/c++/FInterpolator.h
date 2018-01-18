//
// Created by anais on 19/12/2017.
//

#ifndef C_FONCTION_F_H
#define C_FONCTION_F_H


#include "FunctionInterpolator.h"

class FInterpolator : public FunctionInterpolator {
public:
    FInterpolator(std::vector<point> pointList, double minX, double maxX, double minY, double maxY);

    double getf(double x, double y) override;
    double getf_dx(double x, double y) override;
    double getf_dy(double x, double y) override;
    std::string getFunctionLabel() override;
};

#endif //C_FONCTION_F_H
