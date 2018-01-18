//
// Created by Sebastien Hervieu on 26/12/2017.
//

#include "PointResult.h"

PointResult::PointResult() {

}

PointResult::PointResult(double x, double y, double z, double err) {
    m_x = x;
    m_y = y;
    m_z = z;
    m_err = err;
}

double PointResult::getx() const {
    return m_x;
}

double PointResult::gety() const {
    return m_y;
}

double PointResult::getz() const {
    return m_z;
}

double PointResult::geterr() const {
    return m_err;
}

void PointResult::seterr(double m_err) {
    PointResult::m_err = m_err;
}


