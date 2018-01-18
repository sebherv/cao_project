//
// Created by Sebastien Hervieu on 15/01/2018.
//

#include "FunctionInterpolator.h"
#include "TriangleFileReader.h"
#include "TrianglesWriter.h"
#include "PointListWriter.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <sstream>

FunctionInterpolator::FunctionInterpolator(std::vector<point> pointList, double minX, double maxX, double minY, double maxY)
: m_minX(minX), m_maxX(maxX), m_minY(minY), m_maxY(maxY) {
    m_pointList =  pointList;
}

void FunctionInterpolator::interpolate() {
    // First set the values for f(x,y) , df/dx and df/dy
    computePointValues();

    // Generate HctElement list
    generateHctElements();

    // Compute Interpolation points based on grid
    interpolateGrid();

    // Compute Error
    computeError();

    // Compute at specific points
    computeSpecificPoints();
}

void FunctionInterpolator::computePointValues() {
    for(auto& point : m_pointList) {
        double x = point.get_x();
        double y = point.get_y();

        point.set_f(getf(x,y));
        point.set_df_dx(getf_dx(x,y));
        point.set_df_dy(getf_dy(x,y));
    }
}

void FunctionInterpolator::generateHctElements() {
    // Read input triangulation
    TriangleFileReader triangleFileReader("../matlab/Triangle.RES", m_pointList);

    // Initialize elements, set initial values
    m_elementList = triangleFileReader.parse();

}

void FunctionInterpolator::interpolateGrid() {
    // Generate grid
    int numSampleX = 50;
    int numSampleY = 50;

    mInterpolator.setElements(m_elementList);

    for (int i = 0; i <= numSampleX; i++) {
        for (int j = 0; j <= numSampleY; j++) {
            // Generate point
            double currentX = m_minX + ((m_maxX - m_minX) / numSampleX) * i;
            double currentY = m_minY + ((m_maxY - m_minY) / numSampleY) * j;
            try {

                // Compute current value
                m_pointResultVector.push_back(mInterpolator.interpolate(currentX, currentY));

            } catch (const std::exception &e) {
                std::cout << e.what();
                exit(-1);
            }
        }
    }
}

void FunctionInterpolator::computeError() {
    for(auto &current : m_pointResultVector) {
        // Calculer l'erreur:
        current.seterr(getf(current.getx(), current.gety()) - current.getz());

        std::cout << current.getx();
        std::cout << " " << current.gety();
        std::cout << " " << current.getz();
        std::cout << " " << current.geterr() << std::endl;

    }

    double errmin = m_pointResultVector[0].geterr();
    double errmax = m_pointResultVector[0].geterr();
    for(auto &current : m_pointResultVector) {
        if(std::abs(errmin) > std::abs(current.geterr())) {
            errmin = current.geterr();
        }

        if(std::abs(errmax) < std::abs(current.geterr())) {
            errmax = current.geterr();
        }
    }
    std::cout << "Error min: " << errmin << std::endl;
    std::cout << "Error max: " << errmax << std::endl;

}

void FunctionInterpolator::computeSpecificPoints() {
    // calcul à des points précis:
    m_point1 = mInterpolator.interpolate(2.5,0.8);
    m_point2 = mInterpolator.interpolate(0.2, 1.1);
    m_point3 = mInterpolator.interpolate(2.9, 2.5);
}

std::string FunctionInterpolator::getTriangleListString() {
    std::ostringstream oss;
    oss << "Liste des triangles: " << std::endl;

    TrianglesWriter writer;
    oss << writer.generateOutputContent(m_elementList);

    oss << std::endl;

    return oss.str();
}

std::string FunctionInterpolator::getPointListValues() {
    PointListWriter writer(m_pointResultVector);
    return writer.getPointValueListString();
}

std::string FunctionInterpolator::getPointListErrors() {
    PointListWriter writer(m_pointResultVector);
    return writer.getPointErrorListStirng();
}

std::string FunctionInterpolator::getResultFileData() {
    std::ostringstream oss;
    oss << "Données pour ";
    oss << getFunctionLabel();
    oss << std::endl;

    oss << "Liste des N points et valeurs de la fonction:" << std::endl;
    oss << "i\t" << "xi\t" << "yi\t" << "f(xi,yi)\t" << "df/dx(xi,yi\t" << "df/dy(xi,yi" << std::endl;

    for(auto& current : m_pointList) {
        oss << current.get_id() << "\t";
        oss << current.get_x() << "\t";
        oss << current.get_y() << "\t";
        oss << current.get_df_dx() << "\t";
        oss << current.get_df_dy() << "\t";
        oss << std::endl;
    }

    oss << std::endl;

    oss << "Valeurs de l'interpolant: " << std::endl;
    oss << "- au point (2.5, 0.8): " << m_point1.getz() << std::endl;
    oss << "- au point (0.2, 1.1): " << m_point2.getz() << std::endl;
    oss << "- au point (2.9, 2.5): " << m_point3.getz() << std::endl;

    oss << std::endl;

    oss << "Valeurs minimale et maximale de f - S : " << std::endl;
    oss << "Err min = " << m_errmin << std::endl;
    oss << "Err max = " << m_errmax << std::endl;

    return oss.str();
}
