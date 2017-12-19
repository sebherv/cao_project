//
// Created by Sebastien Hervieu on 18/12/2017.
//

#include "point.h"


point::point(int id, double x, double y) : m_id(id), m_x(x), m_y(y) {}

int point::get_id() const {
    return m_id;
}

double point::get_x() const {
    return m_x;
}

double point::get_y() const {
    return m_y;
}

double point::get_f() const {
    return m_f;
}

double point::get_df_dx() const {
    return m_df_dx;
}

double point::get_df_dy() const {
    return m_df_dy;
}
