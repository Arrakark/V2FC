#pragma once
#include <Arduino.h>
#include <liftMotor.h>

class beltLiftz
{
public:
	//consturctor
	beltLift(int upSwitch, int downSwitch, liftMotor* solar_bot_motor);
	//member functions
	void init();
	void liftUp();
	void liftDown();
	liftMotor* solar_bot_motor;
private:
};
