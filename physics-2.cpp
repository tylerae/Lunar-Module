//
//  Physics.cpp
//  W2 Apollo Practice
//
//  Created by Tyler  Elms on 9/23/22.
//
#define _USE_MATH_DEFINES
#include "physics.h"
#include <iostream>


#include <cmath>

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)


using namespace std;
//Constructor
Physics::Physics()
{
    dx = 0;                  // Current horizontal velocity
    dy = 0;                  // Current vertical velocity
                     // Current altitude
    aDegrees = 0;            // Current angle
                     // Current horizontal position
    aRadians = 0;            // Angle in radians
    accelerationThrust = 0;  // Acceleration due to thrust
    ddxThrust = 0;           // Horizontal acceleration due to thrust
    ddyThrust = 0;           // Vertical acceleration due to thrust
    ddx = 0;                 // Total horizontal acceleration
    ddy = 0;                 // Total vertical acceleration
    v = 0;                   // Total velocity

}

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
 // your function goes here

double Physics::computeDistance(double s, double v, double a, double t)
{
    s = s + (v * t) + (0.5 * a * (t * t));

    return s;
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/

double Physics::computeAcceleration(double fuel)
{
    double a;
    a = THRUST / (WEIGHT + fuel);

    return a;
}


/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/

double Physics::computeVelocity(double v, double a, double t)
{

    v = v + (a * t);

    return v;
}


/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |       /
 *   y |     / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/

double Physics::computeVerticalComponent(double a, double total)
{
    return cos(a) * total;
}

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |      /
 *   y |    / total
 *    |a /
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/

double Physics::computeHorizontalComponent(double a, double total)
{
    return sin(a) * total;
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *   y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/

double Physics::computeTotalComponent(double x, double y) {

    return sqrt((x * x) + (y * y));
}


/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/

double Physics::radiansFromDegrees(double d)
{
    return (d * (M_PI / 180));
}
/*
* GETTERS AND SETTERS
*/
double Physics::getDX() { return this->dx; }
double Physics::getDY() { return this->dy; }

double Physics::getADegrees() { return this->aDegrees; }

double Physics::getARadians() { return this->aRadians; }
double Physics::getAccelerationThrust() { return this->accelerationThrust; }
double Physics::getDDXThrust() { return this->ddxThrust; }
double Physics::getDDYThrust() { return this->ddyThrust; }
double Physics::getDDX() { return this->ddx; }
double Physics::getDDY() { return this->ddy; }
double Physics::getV() { return this->v; }

void Physics::setDX(double value) { this->dx = value; }
void Physics::setDY(double value) { this->dy = value; }

void Physics::setADegrees(double value) { this->aDegrees = value; }

void Physics::setARadians(double value) { this->aRadians = value; }
void Physics::setAccelerationThrust(double value) { this->accelerationThrust = value; }
void Physics::setDDXThrust(double value) { this->ddxThrust = value; }
void Physics::setDDYThrust(double value) { this->ddyThrust = value; }
void Physics::setDDX(double value) { this->ddx = value; }
void Physics::setDDY(double value) { this->ddy = value; }
void Physics::setV(double value) { this->v = value; }