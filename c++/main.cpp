#include "point.h"
#include "PointFileReader.h"
#include "triangle.h"
#include "TriangleFileReader.h"
#include "Fonction_F.h"
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

    std::vector<point>::iterator it;
    for(it=pointList.begin(); it!=pointList.end(); it++) {
        std::cout << it->get_id() << ", " << it->get_x() << ", " << it->get_y() << std::endl;
        it->set_f(Fonction_F::getf(it->get_x(),it->get_y() ));
        it->set_df_dx(Fonction_F::getf_dx(it->get_x(),it->get_y() ));
        it->set_df_dy(Fonction_F::getf_dy(it->get_x(),it->get_y() ));
    }

    // Read input triangulation
    TriangleFileReader triangleFileReader("../../matlab/HCT.RES", pointList);
    std::vector<triangle> triangleList = triangleFileReader.parse();

    for(auto &current : triangleList ) {
        current.affiche();
    }


    return 0;
}

