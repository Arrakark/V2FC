#include "HTHING.h"

HTHING::HTHING(int passed_speed_pin, int passed_direction_pin)
{
    speed_pin = passed_speed_pin;
    direction_pin = passed_direction_pin;
    pinMode(speed_pin, OUTPUT);
    pinMode(direction_pin, OUTPUT);
    stop();
}

void HTHING::run(int vector)
{
    //cap the vector between -255 and 255
    if (vector > 255)
    {
        vector = 255;
    }
    if (vector < -255)
    {
        vector = -255;
    }
    if (vector > 0)
    {
        digitalWrite(direction_pin, HIGH);
        analogWrite(speed_pin, 255 - vector);
    }
    if (vector <= 0)
    {
        digitalWrite(direction_pin, LOW);
        analogWrite(speed_pin, abs(vector));
    }
}

void HTHING::stop()
{
    run(0);
}