#include "lander.h"
#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)
/*
* Construct the lander.
*/
Lander::Lander(double x, double y) {
	this->point = Point(x, y);
	this->angle.setDegrees(0);
	this->fuel = 5000.00;
}

//Getters
Point Lander::getPoint() {
	return this->point;
}
double Lander::getVelocity()
{
	return this->physics.getV();
}
double Lander::getAngleRad()
{
	return this->angle.getRadians();
}
double Lander::getAngleDeg()
{
	return this->angle.getDegrees();
}
void Lander::setAngle(double amount)
{
	this->angle.setRadians(angle.getRadians() + amount);
}
//Setters
Lander& Lander::operator-=(double amount)
{
	this->fuel -= amount;
	return *this;
}

double Lander::getFuel()
{
	return this->fuel;
}

/*
* Handles everything in order to move the lander.
*/
void Lander::moveLander(bool isThrusting)
{	
	//Set the acceleration due to thrust. This changes based on the fuel amount, since the added weight changes the amount of force.
	this->physics.setAccelerationThrust(this->physics.computeAcceleration(this->fuel));
	
	//If the lander is thrusting, the acceleration due to thrust will be equivalent to the accelerationThrust value
	//that was just set. However, we have to split it into the X and Y components.
	if (isThrusting) {
		this->physics.setDDXThrust(this->physics.computeHorizontalComponent(this->angle.getRadians(), this->physics.getAccelerationThrust()));
		this->physics.setDDYThrust(this->physics.computeVerticalComponent(this->angle.getRadians(), this->physics.getAccelerationThrust()));
	} else //If the lander isn't thrusting, acceleration due to thrust will be equal to 0.
	{
		this->physics.setDDXThrust(0);
		this->physics.setDDYThrust(0);
	}
	//Set the total acceleration for each component.
	this->physics.setDDX(this->physics.getDDXThrust());
	this->physics.setDDY(this->physics.getDDYThrust() + GRAVITY);

	//Set the velocity values for each component.
	this->physics.setDX(this->physics.computeVelocity(this->physics.getDX(), this->physics.getDDX(), .3));
	this->physics.setDY(this->physics.computeVelocity(this->physics.getDY(), this->physics.getDDY(), .3));
	//Comput the total velocity component so that we can display it and use it elsewhere.
	this->physics.setV(this->physics.computeTotalComponent(this->physics.getDX(), this->physics.getDY()));
	//Change the current point of the lander.
	this->point.setX(this->physics.computeDistance(this->point.getX(), this->physics.getDX(), this->physics.getDDX(), .3));
	this->point.setY(this->physics.computeDistance(this->point.getY(), this->physics.getDY(), this->physics.getDDY(), .3));
}