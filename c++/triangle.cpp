//
// Created by Sebastien Hervieu on 18/12/2017.
//
#include "Triangle.h"
#include <cmath>
#include <iostream>


triangle::triangle() {

}

triangle::triangle(int idTriangle, point pt1, point pt2, point pt3) : id(idTriangle) {
    m_points[0] = pt1;
    m_points[1] = pt2;
    m_points[2] = pt3;

    // Calculer les coordonnées du barycentre
    double omx, omy;
    getCartesianFromBarycentric(0.3333, 0.3333, 0.3333, omx, omy);
    omega_x = omx;
    omega_y = omy;
}

triangle::triangle(const triangle &other) {
    id = other.id;
    m_points = other.m_points;
    omega_x = other.omega_x;
    omega_y = other.omega_y;
}

triangle::triangle(triangle &&other) {
    id = other.id;
    m_points = other.m_points;
    omega_x = other.omega_x;
    omega_y = other.omega_y;
}

triangle& triangle::operator=(const triangle &other) {
    id = other.id;
    m_points = other.m_points;
    omega_x = other.omega_x;
    omega_y = other.omega_y;
    return *this;
}

triangle& triangle::operator=(triangle &&other) {
    id = other.id;
    m_points = other.m_points;
    omega_x = other.omega_x;
    omega_y = other.omega_y;
    return *this;
}


void triangle::affiche() {
    std::cout << id << std::endl;
}

point& triangle::getPoint(int i) {
    return m_points[i];
}

void triangle::getCartesianFromBarycentric(double l1,
                                           double l2,
                                           double l3,
                                           double &x,
                                           double &y) {

    double x1 = getPoint(0).get_x();
    double x2 = getPoint(1).get_x();
    double x3 = getPoint(2).get_x();
    double y1 = getPoint(0).get_y();
    double y2 = getPoint(1).get_y();
    double y3 = getPoint(2).get_y();

    x = l1 * x1 + l2 * x2 + l3 * x3;
    y = l1 * y1 + l2 * y2 + l3 * y3;

}

void triangle::getBarycentricFromCartesian(double x,
                                           double y,
                                           double &lambda1,
                                           double &lambda2,
                                           double &lambda3) {
    const double rounderr = 1E-9;

    double x1 = getPoint(0).get_x();
    double x2 = getPoint(1).get_x();
    double x3 = getPoint(2).get_x();
    double y1 = getPoint(0).get_y();
    double y2 = getPoint(1).get_y();
    double y3 = getPoint(2).get_y();


    lambda1 = ((y2-y3)*(x-x3) + (x3-x2)*(y-y3)) / ((y2-y3)*(x1-x3) + (x3-x2)*(y1-y3));
    lambda2 = ((y3-y1)*(x-x3) + (x1-x3)*(y-y3)) / ((y2-y3)*(x1-x3) + (x3-x2)*(y1-y3));

    // Workaround: If one of the coordinate is exactly 1 and
    // the other is very small, then force the very small to 0
    // This is to handle the case when the point to interpolate is
    // one of the summit. In that case rounding errors can lead to
    // one of the coordinates being 1 and the other being ~ e-10
    // leading the point being outside of the triangle
    if((std::abs(lambda1) < rounderr) && (lambda2 == 1)) {
        lambda1 = 0;
    }
    if((std::abs(lambda2) < rounderr) && (lambda1 == 1)) {
        lambda2 = 0;
    }
    if((std::abs(lambda1) < rounderr) && (std::abs(lambda2) < rounderr)) {
        lambda1 = 0; lambda2 = 0;
    }


    lambda3 = 1 - lambda1 - lambda2;

    // Workaround: if lambda3 is very close to 0, round it
    // down to zero
    if(std::abs(lambda3) < rounderr) {
        lambda3 = 0;
    }
}

bool triangle::isInside(double x, double y) {
    double l1, l2, l3;
    getBarycentricFromCartesian(x,y,l1,l2,l3);
    if((l1 >= 0) && (l1 <= 1)
       && (l2 >= 0) && (l2 <= 1) && (l3 >= 0 && l3 <= 1)) {
        return  true;
    }
    return false;
}

