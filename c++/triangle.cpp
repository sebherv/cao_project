//
// Created by Sebastien Hervieu on 18/12/2017.
//
#include <iostream>
#include "triangle.h"



triangle::triangle(int idTriangle, point pt1, point pt2, point pt3) : id(idTriangle) {
    m_points[0] = pt1;
    m_points[1] = pt2;
    m_points[2] = pt3;
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
