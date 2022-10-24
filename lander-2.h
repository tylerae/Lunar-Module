#include "point.h"
#include "angle.h"
#include "physics.h"
/*********************
* Lander class
* Holds everything the lander needs
* in order to function.
***********************/
class Lander 
{
public:
	Lander(double x, double y);
	Point getPoint();
	double getVelocity();
	double getAngleRad();
	double getAngleDeg();
	void setAngle(double amount);
	void moveLander(bool isThrusting);
	Lander& operator-=(double amount);
	double getFuel();
private:
	Point point = Point();
	Physics physics = Physics();
	Angle angle = Angle();
	double fuel;
};