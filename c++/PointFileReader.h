//
// Created by anais on 19/12/2017.
//

#ifndef C_POINTFILEREADER_H
#define C_POINTFILEREADER_H
#include <string>
#include <vector>
#include "point.h"

class PointFileReader {
    std::string mFileName;

public:
    PointFileReader(std::string filename);
    std::vector<point> parse();

};


#endif //C_POINTFILEREADER_H
