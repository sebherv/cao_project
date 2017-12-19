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

public:
    TriangleFileReader(std::string filename);
    std::vector<triangle> parse();
};


#endif //C_TRIANGLEFILEREADER_H
