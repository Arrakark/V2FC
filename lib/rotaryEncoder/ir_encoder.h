//encoder function that's only for distance (PA4 & PA2)

#ifndef ir_encoder_H
#define ir_encoder_H

#include "Arduino.h"

#define WHEEL_RADIUS 3.115 //[cm]
#define PI 3.141592650000000209
#define DEBOUNCE_CONST 7000 //will need to adjust this number for debouncing

class ir_encoder
{
public:
	ir_encoder(int inputPin, int numDivisions);
	void init();
	void encoder_function();
	float getDistance();
	void reset();

	//   private: //somehow private doesn't work in the main function
	int inputPin;
	int numDivisions;
	volatile int encoder_count;
	int prev_state = 0;
};

#endif