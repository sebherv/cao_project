//
// Created by Sebastien Hervieu on 15/01/2018.
//

#ifndef C_FONCTIONINTERPOLATOR_H
#define C_FONCTIONINTERPOLATOR_H


#include <vector>
#include "Point.h"
#include "HtcElement.h"
#include "PointResult.h"
#include "HctInterpolator.h"

class FunctionInterpolator {
private:
    std::vector<point> m_pointList;
    std::vector<HctElement> m_elementList;
    std::vector<PointResult> m_pointResultVector;

    HctInterpolator mInterpolator;

    // Min Max interpolation ranges
    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;

    // Post Processing
    double m_errmin;
    double m_errmax;

    PointResult m_point1;
    PointResult m_point2;
    PointResult m_point3;

    // Interpolation Steps
    void computePointValues();
    void generateHctElements();
    void interpolateGrid();
    void computeError();
    void computeSpecificPoints();

public:
    // Constructor
    FunctionInterpolator(std::vector<point> pointList, double minX, double maxX, double minY, double maxY);

    // Perform all the interpolation for the numeric function
    void interpolate();

    // Virtual methods
    virtual double getf(double x, double y) = 0;
    virtual double getf_dx(double x, double y) = 0;
    virtual double getf_dy(double x, double y) = 0;


};


#endif //C_FONCTIONINTERPOLATOR_H
