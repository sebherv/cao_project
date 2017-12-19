//
// Created by Sebastien Hervieu on 18/12/2017.
//

#ifndef C_TRIANGLE_H
#define C_TRIANGLE_H


#include "point.h"
#include <vector>
#include <array>


class triangle {
private:
    int id;
    std::array<point,3> m_points; // Liste des points constituant le triangle

public:
    triangle(int idTriangle, point pt1, point pt2, point pt3);
    void affiche();

};


#endif //C_TRIANGLE_H
