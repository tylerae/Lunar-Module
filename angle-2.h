#ifndef angle_h
#define angle_h
#include <iostream> // for cout, cin
#include <stdio.h>

/***************************************************
 * ANGLE CLASS
 * Handles conversion of angles and radians
 **************************************************/

class Angle {

private:
    double angleInRadians;

    double convertToDegrees(double radian);

    double convertToRadians(double degree);

    void normalize();

public:

    double getDegrees();

    double getRadians();

    void setDegrees(double degree);

    void setRadians(double radian);

    Angle();

};



#endif /* angle_h */
