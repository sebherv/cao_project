//
// Created by Sebastien Hervieu on 18/12/2017.
//

#ifndef C_POINT_H
#define C_POINT_H


class point {
private:
    int m_id;
    double m_x;
    double m_y;
    double m_f;
    double m_df_dx;
    double m_df_dy;

public:
    point();
    point(int id, double m_x, double m_y);
    point(const point& other);

    bool operator<(const point& other);

    int get_id() const;

    double get_x() const;

    double get_y() const;

    double get_f() const;

    double get_df_dx() const;

    double get_df_dy() const;

    void set_f(double _f);

    void set_df_dx(double _df_dx);

    void set_df_dy(double _df_dy);
};


#endif //C_POINT_H
