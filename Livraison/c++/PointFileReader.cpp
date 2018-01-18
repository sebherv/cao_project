//
// Created by anais on 19/12/2017.
//

#include <fstream>
#include "PointFileReader.h"

PointFileReader::PointFileReader(std::string filename) : mFileName(filename){}

std::vector<point> PointFileReader::parse() {
    std::vector<point> parsedData;
    //Ouvrir le fichier
    std::ifstream myfile(mFileName);

    // Read the first line --> number points
    int num;
    myfile >> num;

    // Read dummies from first line
    int dummy;
    myfile >> dummy >> dummy;


    for(int i = 0; i < num; i++) {
        int id;
        double x, y;

        myfile >> id >> x >> y;
        point newPoint(id, x, y);
        parsedData.push_back(newPoint);
    }

    return parsedData;
}