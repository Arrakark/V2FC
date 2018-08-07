#ifndef HTHING_H
#define HTHING_H

#include "Arduino.h"

class HTHING
{
public:
	/**
	 * Attaches an H-THING to pins on the TINAH/Arduino/Blue Pill
	 * 
	 * Speed pin should be a PWM pin, direction should be a regular digital I/O
	 * Be careful when enterning the pins here; you could burn something out.
	 */
	HTHING(int speed_pin, int direction_pin);
	/**
	 * Runs the motor with the specified vector.
	 * 
	 * Parameter must be a number between -255 and 255.
	 */
	void run(int vector);
	/**
	 * Stops the motor
	 */
	void stop();

private:
	int speed_pin;
	int direction_pin;
};

#endif