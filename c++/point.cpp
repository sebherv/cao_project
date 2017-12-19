//
// Created by Sebastien Hervieu on 18/12/2017.
//

#include "point.h"

point::point() {}

point::point(int id, double x, double y) : m_id(id), m_x(x), m_y(y) {}

point::point(const point& other) : m_id(other.m_id),
                                   m_x(other.m_x) ,
                                   m_y(other.m_y) ,
                                   m_f(other.m_f) ,
                                   m_df_dx(other.m_df_dx) ,
                                   m_df_dy(other.m_df_dy) {}

bool point::operator<(const point& other) const {
    return this->m_id < other.m_id;
}

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

void point::set_f(double _f) {
    m_f = _f;
}

void point::set_df_dx(double _df_dx) {
    m_df_dx = _df_dx;
}

void point::set_df_dy(double _df_dy) {
    m_df_dy = _df_dy;
}
