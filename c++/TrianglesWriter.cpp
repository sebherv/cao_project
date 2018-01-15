//
// Created by Sebastien Hervieu on 15/01/2018.
//

#include <sstream>
#include "TrianglesWriter.h"

std::string TrianglesWriter::generateOutputContent(std::vector<HctElement> &triangleList) {

    std::stringstream outputString();
    for(auto& current : triangleList) {
        //outputString << current.getOutputLine();

    }
    return std::string();
}
