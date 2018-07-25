#include "ir_encoder.h"

//constructor: inputPin is either PA4 or PA2 & numDivisions = number of divisions in encoder pattern
ir_encoder::ir_encoder(int _inputPin, int _numDivisions)
{
	inputPin = _inputPin;
	numDivisions = _numDivisions;
	encoder_count = 0;
}

void ir_encoder::init()
{
	pinMode(inputPin, INPUT_PULLUP);
}

/*
    function for external interrupt 
    (however member functions don't work well for the attachInterrupt function)

    encoder values are best read when the external interrupt is FALLING or RISING
    therefore, will need to times 2 for the number of counts
*/
void ir_encoder::encoder_function()
{
	for (int i = 0; i < DEBOUNCE_CONST; i++)
	{
		if (digitalRead(inputPin) != 0)
		{
			return;
		}
	}
	encoder_count += 2;
}

float ir_encoder::getDistance()
{
	//need radians not degrees
	return WHEEL_RADIUS * encoder_count * (360 / numDivisions) * (PI / 180);
}

void ir_encoder::reset()
{
	encoder_count = 0;
}