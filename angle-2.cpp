#define _USE_MATH_DEFINES // allows use of constants from cmath
#include "angle.h" // h-file 
#include "cmath" // for math
#include <iostream> // for cin, cout
#include <iomanip> // precision

using namespace std;

Angle::Angle() {
    angleInRadians = 0;
}

/***************************************************
 * CONVERT TO DEGREES
 * convert radians into degrees.
 **************************************************/
double Angle::convertToDegrees(double radian) {
    double degree;

    degree = radian / (M_PI / 180);

    return degree;
}

/***************************************************
 * CONVERT TO RADIANS
 * convert degrees into radians.
 **************************************************/

double Angle::convertToRadians(double degree) {
    double radian;

    radian = degree * (M_PI / 180);

    return radian;

}

/***************************************************
 * NORMALIZE
 * take angle reduce it to between 0 and 2π or 0 and 360°.
 * For example, 3π will become π, 362° will become 2°, -5° will become 355°, and -7π will become π.
 **************************************************/
void Angle::normalize() {
    double degrees = convertToDegrees(angleInRadians);
    while (degrees >= 360) {
        degrees -= 360;
    }
    while (degrees < 0) {
        degrees += 360;
    }

    this->angleInRadians = convertToRadians(degrees);
}

/***************************************************
 * GET DEGREE
 * Gets the current degree
 **************************************************/
double Angle::getDegrees() {

    return convertToDegrees(angleInRadians);
}

/***************************************************
 * GET RADIAN
 * Gets the radian value
 **************************************************/
double Angle::getRadians() {

    return angleInRadians;
}

/***************************************************
 * SET DEGREES
 * Gets degree value and sets the current degree
 * INPUT
 *     degree
 **************************************************/
void Angle::setDegrees(double degree) {
    this->angleInRadians = convertToRadians(degree);
    normalize();

}

/***************************************************
 * SET RADIANS
 * Gets radian value and sets the current radian
 * INPUT
 *     radians
 **************************************************/
void Angle::setRadians(double radian) {
    this->angleInRadians = radian;
    normalize();

}