#include <iostream>
#include <vector>
#include <fstream>
#include "point.h"
#include "PointFileReader.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Analyse commande line options

    // Read input file list
    PointFileReader pointReader("../../input/hct.pts");
    std::vector<point> pointList = pointReader.parse();

    std::vector<point>::iterator it;
    for(it=pointList.begin(); it!=pointList.end(); it++) {
        std::cout << it->get_id() << ", " << it->get_x() << ", " << it->get_y() << std::endl;
    }

    // Read input triangulation


    return 0;
}

