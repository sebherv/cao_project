//
// Created by Sebastien Hervieu on 16/01/2018.
//

#ifndef C_POINTLISTWRITER_H
#define C_POINTLISTWRITER_H


#include <vector>
#include <string>
#include "PointResult.h"

class PointListWriter {
private:
    std::vector<PointResult> m_pointResultVector;
    std::string getPointList(bool printErrorList);
public:
    PointListWriter(std::vector<PointResult> pointList);
    std::string getPointValueListString();
    std::string getPointErrorListStirng();
};


#endif //C_POINTLISTWRITER_H
