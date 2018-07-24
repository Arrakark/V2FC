#include "qrd_encoder.h"

qrd_encoder::qrd_encoder(int _outputPin, int _numDivisions)
{
    outputPin = _outputPin;
    numDivisions = _numDivisions;

    pinMode(outputPin, INPUT); //assume we have a pull resistor built
    counter = 0;
    measure_state = analogRead(outputPin) > THRESHOLD; //necessary?
}

/*
    resets counter back to 0
*/
void qrd_encoder::reset()
{
    counter = 0;
}

/*
    counts the number of times that the states that got changed
    (black to white or white to black)
*/

void qrd_encoder::count() //need to do this in a while loop? use interrupts???????
{
    measure_state = analogRead(outputPin) > THRESHOLD; //while loop?
    bool previous_state = measure_state;

    if (previous_state != measure_state) //change of state
    {
        counter++;
        previous_state = !previous_state;
    }
}

/*
    returns the distance traveled by the encoder wheel
*/

float qrd_encoder::getDistance()
{
    return WHEEL_RADIUS * counter * (360 / numDivisions) * (PI / 180);
}