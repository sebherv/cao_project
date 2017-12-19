//
// Created by Sebastien Hervieu on 18/12/2017.
//
#include <iostream>
#include "triangle.h"


triangle::triangle(int idTriangle, int idPt1, int idPt2, int idPt3) : id(idTriangle) {
    m_pointIds.push_back(idPt1);
    m_pointIds.push_back(idPt2);
    m_pointIds.push_back(idPt3);
}

void triangle::affiche() {
    std::cout << id << std::endl;

}
