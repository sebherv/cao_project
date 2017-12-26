//
// Created by Sebastien Hervieu on 18/12/2017.
//
#include <iostream>
#include "triangle.h"



triangle::triangle(int idTriangle, point pt1, point pt2, point pt3) : id(idTriangle) {
    m_points[0] = pt1;
    m_points[1] = pt2;
    m_points[2] = pt3;

    // Calculer les coordonnées du barycentre
    getCartesianFromBarycentric(1/3, 1/3, 1/3, omega_x, omega_y);
}

triangle::triangle(const triangle &other) {
    id = other.id;
    m_points = other.m_points;
}

triangle::triangle(triangle &&other) {
    id = other.id;
    m_points = other.m_points;
}

triangle& triangle::operator=(const triangle &other) {
    id = other.id;
    m_points = other.m_points;
    return *this;
}

triangle& triangle::operator=(triangle &&other) {
    id = other.id;
    m_points = other.m_points;
    return *this;
}


void triangle::affiche() {
    std::cout << id << std::endl;
}

point& triangle::getPoint(int i) {
    return m_points[i];
}

void triangle::getCartesianFromBarycentric(double lambda1,
                                           double lambda2,
                                           double lambda3,
                                           double &x,
                                           double &y) {
    // Calculate from first point
    x = lambda2 * (getPoint(2).get_x() - getPoint(1).get_x())
        + lambda3 * (getPoint(3).get_x() - getPoint(1).get_x())
        + getPoint(1).get_x();

    y = lambda2 * (getPoint(2).get_y() - getPoint(1).get_y())
        + lambda3 * (getPoint(3).get_y() - getPoint(1).get_y())
        + getPoint(1).get_y();

}

void triangle::getBarycentricFromCartesian(double x,
                                           double y,
                                           double &lambda1,
                                           double &lambda2,
                                           double &lambda3) {
    double x1 = getPoint(1).get_x();
    double x2 = getPoint(2).get_x();
    double x3 = getPoint(3).get_x();
    double y1 = getPoint(1).get_y();
    double y2 = getPoint(2).get_y();
    double y3 = getPoint(3).get_y();


    lambda1 = ((y2-y3)*(x-x3) + (x3-x2)*(y-y3)) / ((y2-y3)*(x1-x3)+(x3-x2)*(y1-y3));
    lambda2 = ((y2-y1)*(x-x3) + (x1-x3)*(y-y3)) / ((y2-y3)*(x-x3)+ (x3-x2)*(y1-y3));
    lambda3 = 1 - lambda1 - lambda2;
}
