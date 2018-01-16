//
// Created by Sebastien Hervieu on 16/01/2018.
//

#include <sstream>
#include "PointListWriter.h"


PointListWriter::PointListWriter(std::vector<PointResult> pointList) {
    m_pointResultVector = pointList;
}
std::string PointListWriter::getPointValueListString() {
    return getPointList(false);
}

std::string PointListWriter::getPointErrorListStirng() {
    return getPointList(true);
}

std::string PointListWriter::getPointList(bool printErrorList) {
    std::ostringstream oss;

    for(auto& current : m_pointResultVector) {
        oss << current.getx() << " ";
        oss << current.gety() << " ";
        if(printErrorList) {
            oss << current.geterr() << std::endl;
        } else {
            oss << current.getz() << std::endl;
        }
    }

    return oss.str();
}
