#include "Point.h"
#include "PointFileReader.h"
#include "Triangle.h"
#include "TriangleFileReader.h"
#include "FInterpolator.h"
#include "GInterpolator.h"
#include "PointResult.h"
#include "HctInterpolator.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <time.h>


int main() {
    std::cout << "Hello, World!" << std::endl;

    // Analyse commande line options

    // Read input file list
    PointFileReader pointReader("../../input/hct.pts");
    std::vector<point> pointList = pointReader.parse();

    // trier par id croissant
    sort(pointList.begin(),pointList.end());

    // Trouver les coordonnées maximales
    double minX, minY, maxX, maxY;
    bool init_minmax = true;

    std::vector<point>::iterator it;
    for(it=pointList.begin(); it!=pointList.end(); it++) {
        if(init_minmax) {
            minX = maxX = it->get_x();
            minY = maxY = it->get_y();
            init_minmax = false;
        } else {
            if (it->get_x() < minX) {
                minX = it->get_x();
            } else if(it->get_x() > maxX) {
                maxX = it->get_x();
            }

            if(it->get_y() < minY) {
                minY = it->get_y();
            } else if(it->get_y() > maxY) {
                maxY = it->get_y();
            }
        }
    }

    //Extrema
    std::cout << "minX = " << minX << "; maxX = " << maxX << std::endl;
    std::cout << "minY = " << minY << "; maxY = " << maxY << std::endl;

    // Interpolate f=exp(x+y)
    FInterpolator fInterpolator(pointList, minX, maxX, minY, maxY);
    fInterpolator.interpolate();

    // DEBUT TRAITEMENT G
    GInterpolator gInterpolator(pointList, minX, maxX, minY, maxY);
    gInterpolator.interpolate();

    std::cout << "Program ended!" << std::endl;

    return 0;
}

