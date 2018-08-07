#include "HBRIDGE.h"

HBRIDGE::HBRIDGE(int _forward_pin, int _reverse_pin)
{
    forward_pin = _forward_pin;
    reverse_pin = _reverse_pin;
}

void HBRIDGE::init()
{
    //Timer2.setPeriod(50);
    //Timer3.setPeriod(50);
    analogWrite(forward_pin, 0);
    pinMode(forward_pin, PWM);
    delay(20);
    analogWrite(reverse_pin, 0);
    pinMode(forward_pin, PWM);
    delay(20);
}

void HBRIDGE::run(int _vector)
{
    //makes sure that _vector is between -255 and 255
    if (_vector < -255)
        _vector = -255;
    else if (_vector > 255)
        _vector = 255;

    if (_vector > 0)
    {
        analogWrite(reverse_pin, 0);
        delay(4);
        analogWrite(forward_pin, _vector);
    }
    else
    {
        analogWrite(forward_pin, 0);
        delay(4);
        analogWrite(reverse_pin, abs(_vector));
    }
}

void HBRIDGE::stop()
{
    analogWrite(forward_pin, 0);
    analogWrite(reverse_pin, 0);
}