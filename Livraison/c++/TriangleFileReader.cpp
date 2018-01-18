//
// Created by anais on 19/12/2017.
//

#include <fstream>
#include <iostream>
#include "TriangleFileReader.h"


TriangleFileReader::TriangleFileReader(std::string filename,  std::vector<point> pointList) : mFileName(filename) {
    m_pointList = pointList;
}

std::vector<HctElement> TriangleFileReader::parse() {
    std::vector<HctElement> parsedData;
    //Ouvrir le fichier
    std::ifstream myfile(mFileName);

    while(!myfile.eof()) {
        int id_triangle;
        int idSommet1;
        int idSommet2;
        int idSommet3;

        myfile >> id_triangle >> idSommet1 >> idSommet2 >> idSommet3;
        HctElement newtriangle(id_triangle,
                             m_pointList[idSommet1-1],
                             m_pointList[idSommet3-1],
                             m_pointList[idSommet2-1]);

        parsedData.push_back(newtriangle);
    }

    return parsedData;
}
