#include "liftMotor.h"

liftMotor::liftMotor(int _pwn_pin, int _direction_pin)
{
    pwn_pin = _pwn_pin;
    direction_pin = _direction_pin;
}

void liftMotor::init()
{
    pinMode(pwn_pin,OUTPUT);
    pinMode(direction_pin,OUTPUT);
}


/*
    rotate lift motor with a certain PWM duty cycle and a specific direction
    
    parameters: dutycycle: ranges from 0 - 4095
                direction: HIGH or LOW
*/
void liftMotor::rotate(int dutyCycle, int direction)
{
    //rotate from a PWM signal with certain duty cycle
    analogWrite(pwn_pin,dutyCycle);

    //rotate at a specific direction
    digitalWrite(direction_pin,direction);
}