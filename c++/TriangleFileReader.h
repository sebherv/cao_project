//
// Created by anais on 19/12/2017.
//

#ifndef C_TRIANGLEFILEREADER_H
#define C_TRIANGLEFILEREADER_H

#include <string>
#include <vector>
#include "triangle.h"


class TriangleFileReader {
    std::string mFileName;
    std::vector<point> m_pointList;

public:
    TriangleFileReader(std::string filename, std::vector<point> pointList);
    std::vector<triangle> parse();
};


#endif //C_TRIANGLEFILEREADER_H
