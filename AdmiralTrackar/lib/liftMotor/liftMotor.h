#pragma once
#include <Arduino.h>

class liftMotor
{
public:
	//consturctor
	liftMotor(int pwn_pin, int direction_pin);
	//member functions
    void init();
	void rotate(int dutyCycle, int direction);

private:
    int pwn_pin;
    int direction_pin;
};