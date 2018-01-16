//
// Created by Sebastien Hervieu on 15/01/2018.
//

#include "FunctionInterpolator.h"
#include "TriangleFileReader.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

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
    TriangleFileReader triangleFileReader("../../matlab/HCT.RES", m_pointList);

    // Initialize elements, set initial values
    m_elementList = triangleFileReader.parse();

}

void FunctionInterpolator::interpolateGrid() {
    // Generate grid
    int numSampleX = 10;
    int numSampleY = 10;

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
