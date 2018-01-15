#include "Point.h"
#include "PointFileReader.h"
#include "Triangle.h"
#include "TriangleFileReader.h"
#include "Fonction_F.h"
#include "Fonction_G.h"
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
        std::cout << it->get_id() << ", " << it->get_x() << ", " << it->get_y() << std::endl;
        it->set_f(Fonction_F::getf(it->get_x(),it->get_y() ));
        it->set_df_dx(Fonction_F::getf_dx(it->get_x(),it->get_y() ));
        it->set_df_dy(Fonction_F::getf_dy(it->get_x(),it->get_y() ));
    }

    //Extrema
    std::cout << "minX = " << minX << "; maxX = " << maxX << std::endl;
    std::cout << "minY = " << minY << "; maxY = " << maxY << std::endl;

    // Read input triangulation
    TriangleFileReader triangleFileReaderF("../../matlab/HCT.RES", pointList);
    std::vector<HctElement> triangleListF = triangleFileReaderF.parse();

    // Generate grid
    int numSampleX = 10;
    int numSampleY = 10;

    std::vector<pointResult> pointResultVectorF(0);
    HctInterpolator interpolatorF(triangleListF);

    for (int i = 0; i <= numSampleX; i++) {
        for (int j = 0; j <= numSampleY; j++) {
            // Generate point
            double currentX = minX + ((maxX - minX) / numSampleX) * i;
            double currentY = minY + ((maxY - minY) / numSampleY) * j;
            try {

                // Compute current value
                pointResultVectorF.push_back(interpolatorF.interpolate(currentX, currentY));

            } catch (const std::exception &e) {
                std::cout << e.what();
                return -1;
            }
        }
    }


    for(auto &current : pointResultVectorF) {
        // Calculer l'erreur:
        current.seterr(Fonction_F::getf(current.getx(), current.gety()) - current.getz());

        std::cout << current.getx();
        std::cout << " " << current.gety();
        std::cout << " " << current.getz();
        std::cout << " " << current.geterr() << std::endl;

    }

    double errmin = pointResultVectorF[0].geterr();
    double errmax = pointResultVectorF[0].geterr();
    for(auto &current : pointResultVectorF) {
        if(std::abs(errmin) > std::abs(current.geterr())) {
            errmin = current.geterr();
        }

        if(std::abs(errmax) < std::abs(current.geterr())) {
            errmax = current.geterr();
        }
    }
    std::cout << "Error min: " << errmin << std::endl;
    std::cout << "Error max: " << errmax << std::endl;

    // calcul à des points précis:
    pointResult point1F = interpolatorF.interpolate(2.5,0.8);
    pointResult point2F = interpolatorF.interpolate(0.2, 1.1);
    pointResult point3F = interpolatorF.interpolate(2.9, 2.5);

    std::cout << "Point (2.5, 0.8): " << point1F.getz() << std::endl;
    std::cout << "Point (0.2, 1.1): " << point2F.getz() << std::endl;
    std::cout << "Point (2.9, 2.5): " << point3F.getz() << std::endl;

    // DEBUT TRAITEMENT G

    for(it=pointList.begin(); it!=pointList.end(); it++) {

        std::cout << it->get_id() << ", " << it->get_x() << ", " << it->get_y() << std::endl;
        it->set_f(Fonction_G::getg(it->get_x(),it->get_y() ));
        it->set_df_dx(Fonction_G::getg_dx(it->get_x(),it->get_y() ));
        it->set_df_dy(Fonction_G::getg_dy(it->get_x(),it->get_y() ));
    }

//Extrema
    std::cout << "minX = " << minX << "; maxX = " << maxX << std::endl;
    std::cout << "minY = " << minY << "; maxY = " << maxY << std::endl;

    // Read input triangulation
    TriangleFileReader triangleFileReaderG("../../matlab/HCT.RES", pointList);
    std::vector<HctElement> triangleListG = triangleFileReaderG.parse();

    std::vector<pointResult> pointResultVectorG(0);
    HctInterpolator interpolatorG(triangleListG);

    for (int i = 0; i <= numSampleX; i++) {
        for (int j = 0; j <= numSampleY; j++) {
            // Generate point
            double currentX = minX + ((maxX - minX) / numSampleX) * i;
            double currentY = minY + ((maxY - minY) / numSampleY) * j;
            try {

                // Compute current value
                pointResultVectorG.push_back(interpolatorG.interpolate(currentX, currentY));

            } catch (const std::exception &e) {
                std::cout << e.what();
                return -1;
            }
        }
    }

    for(auto &current : pointResultVectorG) {
        // Calculer l'erreur:
        current.seterr(Fonction_G::getg(current.getx(), current.gety()) - current.getz());

        std::cout << current.getx();
        std::cout << " " << current.gety();
        std::cout << " " << current.getz();
        std::cout << " " << current.geterr() << std::endl;

    }

    for(auto &current : pointResultVectorG) {
        if(std::abs(errmin) > std::abs(current.geterr())) {
            errmin = current.geterr();
        }

        if(std::abs(errmax) < std::abs(current.geterr())) {
            errmax = current.geterr();
        }
    }
    std::cout << "Error min: " << errmin << std::endl;
    std::cout << "Error max: " << errmax << std::endl;

    // calcul à des points précis:
    pointResult point1G = interpolatorG.interpolate(2.5,0.8);
    pointResult point2G = interpolatorG.interpolate(0.2, 1.1);
    pointResult point3G = interpolatorG.interpolate(2.9, 2.5);

    std::cout << "Point (2.5, 0.8): " << point1G.getz() << std::endl;
    std::cout << "Point (0.2, 1.1): " << point2G.getz() << std::endl;
    std::cout << "Point (2.9, 2.5): " << point3G.getz() << std::endl;




    std::cout << "Program ended!" << std::endl;

    return 0;
}

