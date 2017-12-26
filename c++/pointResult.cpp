//
// Created by Sebastien Hervieu on 26/12/2017.
//

#include "pointResult.h"

pointResult::pointResult() {

}

pointResult::pointResult(double x, double y, double z, double err) {
    m_x = x;
    m_y = y;
    m_z = z;
    m_err = err;
}

double pointResult::getx() const {
    return m_x;
}

double pointResult::gety() const {
    return m_y;
}

double pointResult::getz() const {
    return m_z;
}

double pointResult::geterr() const {
    return m_err;
}


