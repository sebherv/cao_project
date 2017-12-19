//
// Created by anais on 19/12/2017.
//

#include <fstream>
#include <iostream>
#include "TriangleFileReader.h"


TriangleFileReader::TriangleFileReader(std::string filename,  std::vector<point> pointList) : mFileName(filename) {
    m_pointList = pointList;
}

std::vector<triangle> TriangleFileReader::parse() {
    std::vector<triangle> parsedData;
    //Ouvrir le fichier
    std::ifstream myfile(mFileName);

    while(!myfile.eof()) {
        int id_triangle;
        int idSommet1;
        int idSommet2;
        int idSommet3;

        myfile >> id_triangle >> idSommet1 >> idSommet2 >> idSommet3;
        triangle newtriangle(id_triangle,
                             m_pointList[idSommet1],
                             m_pointList[idSommet2],
                             m_pointList[idSommet3]);

        parsedData.push_back(newtriangle);
    }

    return parsedData;
}
