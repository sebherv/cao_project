//
// Created by Sebastien Hervieu on 18/12/2017.
//

#ifndef C_TRIANGLE_H
#define C_TRIANGLE_H


#include <vector>
#include "point.h"

class triangle_exception: public std::exception {
private:
    char* m_what;
public:
    triangle_exception(char* what): m_what(what) {};
    virtual const char* what() const throw() {
        return m_what;
    }
};


class triangle {
private:
    const int ms_MAXSIZE = 3;
    std::vector<point> m_points; // Liste des points constituant le triangle

public:
    void addPoint(point newPoint);
};


#endif //C_TRIANGLE_H
