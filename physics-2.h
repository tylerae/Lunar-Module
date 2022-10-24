//
//  Physics.hpp
//  W2 Apollo Practice
//
//  Created by Tyler  Elms on 9/23/22.
//


#define Physics_hpp
#include <stdio.h>
/*
* The Physics class holds methods that do physics calculations
* and has member variables that hold the current position, velocity,
* acceleration, etc.. values.
*/
class Physics {
private:
    double dx;
    double dy;

    double aDegrees;

    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v;                   // Total velocity



public:
    Physics();
    //Phsyics equations
    double computeDistance(double s, double v, double a, double t);

    double computeAcceleration(double fuel);

    double computeVelocity(double v, double a, double t);

    double computeVerticalComponent(double a, double total);

    double computeHorizontalComponent(double a, double total);

    double computeTotalComponent(double x, double y);

    double radiansFromDegrees(double d);

    //Getters and Setters
    double getDX();
    double getDY();

    double getADegrees();

    double getARadians();
    double getAccelerationThrust();
    double getDDXThrust();
    double getDDYThrust();
    double getDDX();
    double getDDY();
    double getV();

    void setDX(double value);
    void setDY(double value);
    
    void setADegrees(double value);
    
    void setARadians(double value);
    void setAccelerationThrust(double value);
    void setDDXThrust(double value);
    void setDDYThrust(double value);
    void setDDX(double value);
    void setDDY(double value);
    void setV(double value);
};
