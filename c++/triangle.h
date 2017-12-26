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
    double omega_x; // Coordonnée x du barycentre
    double omega_y; // Coordonnée y du barycentre


public:
    triangle();
    triangle(int idTriangle, point pt1, point pt2, point pt3);
    triangle(const triangle& other);
    triangle( triangle&& other);
    triangle& operator=(const triangle& other);
    triangle& operator=(triangle&& other);
    void affiche();
    bool isInside(double x, double y);

    point& getPoint(int i);

    double getOmega_x() const { return omega_x; }
    double getOmega_y() const { return omega_y; }
    void getCartesianFromBarycentric(double lambda1,
                                     double lambda2,
                                     double lambda3,
                                     double& x,
                                     double& y);

    void getBarycentricFromCartesian(double x,
                                     double y,
                                     double& lambda1,
                                     double& lambda2,
                                     double& lambda3);
};


#endif //C_TRIANGLE_H
