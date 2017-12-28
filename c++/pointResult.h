//
// Created by Sebastien Hervieu on 26/12/2017.
//

#ifndef C_POINTRESULT_H
#define C_POINTRESULT_H


class pointResult {
private:
    double m_x;
    double m_y;
    double m_z;
    double m_err;

public:
    pointResult();
    pointResult(double x, double y, double z, double err);

    double getx() const;
    double gety() const;
    double getz() const;
    double geterr() const;

    void seterr(double m_err);
};


#endif //C_POINTRESULT_H
