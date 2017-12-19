//
// Created by Sebastien Hervieu on 18/12/2017.
//

#ifndef C_TRIANGLE_H
#define C_TRIANGLE_H


#include <vector>
#include "point.h"


class triangle {
private:
    int id;
    std::vector<int> m_pointIds; // Liste des points constituant le triangle

public:
    triangle(int idTriangle, int idPt1, int idPt2, int idPt3);
    void affiche();

};


#endif //C_TRIANGLE_H
