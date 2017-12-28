#include "point.h"
#include "PointFileReader.h"
#include "triangle.h"
#include "TriangleFileReader.h"
#include "Fonction_F.h"
#include "pointResult.h"
#include "HctInterpolator.h"
#include <iostream>
#include <fstream>


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
    TriangleFileReader triangleFileReader("../../matlab/HCT.RES", pointList);
    std::vector<HctElement> triangleList = triangleFileReader.parse();

    for(auto &current : triangleList ) {
        current.affiche();
    }

    // Generate grid
    int numSampleX = 30;
    int numSampleY = 30;

    std::vector<pointResult> pointResultVector(0);
    HctInterpolator interpolator(triangleList);

    for (int i = 0; i <= numSampleX; i++) {
        for (int j = 0; j <= numSampleY; j++) {
            // Generate point
            double currentX = minX + ((maxX - minX) / numSampleX) * i;
            double currentY = minY + ((maxY - minY) / numSampleY) * j;
            try {

                // Compute current value
                pointResultVector.push_back(interpolator.interpolate(currentX, currentY));

            } catch (const std::exception &e) {
                std::cout << e.what();
                return -1;
            }
        }
    }


    int i = 0;
    for(auto &current : pointResultVector) {
        std::cout << i << ": x = " << current.getx();
        std::cout << ", y = " << current.gety();
        std::cout << ", z = " << current.getz() << std::endl;
    }
    std::cout << "Program ended!" << std::endl;

    return 0;
}

