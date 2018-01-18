//
// Created by Sebastien Hervieu on 15/01/2018.
//

#include <sstream>
#include "TrianglesWriter.h"

TrianglesWriter::TrianglesWriter() {

}

std::string TrianglesWriter::generateOutputContent(std::vector<HctElement> &triangleList) {

    std::ostringstream oss;
    for(auto& current : triangleList) {
        oss << current.getOutputLine();
    }
    return oss.str();
}

