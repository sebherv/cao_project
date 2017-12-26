//
// Created by anais on 19/12/2017.
//

#ifndef C_TRIANGLEFILEREADER_H
#define C_TRIANGLEFILEREADER_H

#include "htcElement.h"
#include <string>
#include <vector>


class TriangleFileReader {
    std::string mFileName;
    std::vector<point> m_pointList;

public:
    TriangleFileReader(std::string filename, std::vector<point> pointList);
    std::vector<HctElement> parse();
};


#endif //C_TRIANGLEFILEREADER_H
