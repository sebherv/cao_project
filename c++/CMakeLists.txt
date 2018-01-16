cmake_minimum_required(VERSION 3.9)
project(c__)

set(CMAKE_CXX_STANDARD 11)

add_executable(c__ main.cpp Point.cpp Point.h Triangle.cpp Triangle.h PointFileReader.cpp PointFileReader.h TriangleFileReader.cpp TriangleFileReader.h FInterpolator.cpp FInterpolator.h HtcElement.cpp HtcElement.h PointResult.cpp PointResult.h HctInterpolator.cpp HctInterpolator.h GInterpolator.cpp GInterpolator.h TrianglesWriter.cpp TrianglesWriter.h FunctionInterpolator.cpp FunctionInterpolator.h)


