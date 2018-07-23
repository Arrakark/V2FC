#include "SLIFT.h"

#define SERVO_DOWN 1000
#define SERVO_UP 2000
#define SERVO_STATIC 1405

#define PIN_DOWNLIMIT PB13
#define PIN_UPLIMIT PB14
#define PIN_BASKETLIMIT PB15
int dir_array[3] = {SERVO_DOWN, SERVO_UP, SERVO_STATIC};
int limit_array[3] = {PIN_DOWNLIMIT, PIN_UPLIMIT, PIN_BASKETLIMIT};

Servo slift_servo;

SLIFT::SLIFT(int _pin)
{
    servo_pin = _pin;
}

void SLIFT::init(void)
{
    pinMode(servo_pin, OUTPUT);
    pinMode(PIN_DOWNLIMIT, INPUT_PULLUP);
    pinMode(PIN_UPLIMIT, INPUT_PULLUP);
    pinMode(PIN_BASKETLIMIT, INPUT_PULLUP);
    slift_servo.attach(servo_pin);
    slift_servo.writeMicroseconds(SERVO_STATIC);
}

/*
* Move takes an int input of 0, 1, or 2. It move the 
* scissor lift down, up, or keeps it still respectively.
*
* The return value in this case is the integer input.
*
* If the scissor lift needs to move, then the program will
* be not be able to progress untill the limit switch is
* pressed
*
* If the value passes is not 0, 1, or 2, then the scissor
* lift will be kept still. 
*
* The return value in this case is -1. It should indicate
* to the user that there is an error.
*/
void SLIFT::moveUp(){
    slift_servo.writeMicroseconds(SERVO_UP);
    while (!atLimit(PIN_UPLIMIT)) {
        delay(5);
    }
    slift_servo.writeMicroseconds(SERVO_STATIC);
}
void SLIFT::moveDown(){
    slift_servo.writeMicroseconds(SERVO_DOWN);  
    while (!atLimit(PIN_DOWNLIMIT)) {
        delay(5);
    }
    slift_servo.writeMicroseconds(SERVO_STATIC); 
}
void SLIFT::stay(){
    slift_servo.writeMicroseconds(SERVO_STATIC);
}

/*
* The input should be either 0, 1, or 2. In 0 and 1
* represent the limit switches that determine i the
* scissor lift is in the down or up positions 
* respectively. 2 represents the limit switch that 
* determines if the basket on the lift.
*
* The funtion returns true if the limit switch is pressed
* and false if the limit switch is not pressed.
*
* If an invalid value for _dir is passed, the 
* method will return false
*/
bool SLIFT::atLimit(int _pin)
{
    int limit_value = digitalRead(_pin);
    if (limit_value == LOW)
        return (true);
    else
        return (false);
}
