//
// Created by Sebastien Hervieu on 26/12/2017.
//

#ifndef C_HCTINTERPOLATOR_H
#define C_HCTINTERPOLATOR_H


#include "HtcElement.h"
#include "PointResult.h"

class HctInterpolator {
private:
    std::vector<HctElement> m_hctElements;

    HctElement & findElement(double x, double y);



public:
    explicit HctInterpolator();
    void setElements(std::vector<HctElement> elements);
    PointResult interpolate(double x, double y);
};


#endif //C_HCTINTERPOLATOR_H
