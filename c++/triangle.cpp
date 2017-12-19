//
// Created by Sebastien Hervieu on 18/12/2017.
//

#include "triangle.h"


void triangle::addPoint(point newPoint) {
    if(m_points.size() < ms_MAXSIZE) {
        m_points.push_back(newPoint);
    } else {
        throw triangle_exception("Too many points");
    }
}
