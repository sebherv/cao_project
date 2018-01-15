//
// Created by Sebastien Hervieu on 15/01/2018.
//

#ifndef C_TRIANGLESWRITER_H
#define C_TRIANGLESWRITER_H

#include <string>
#include "htcElement.h"



class TrianglesWriter {
private:
public:
    TrianglesWriter();
    std::string generateOutputContent(std::vector<HctElement>& triangleList);
};


#endif //C_TRIANGLESWRITER_H
