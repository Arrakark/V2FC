/*********************************************************************
Control class for arm motion. The arm has 3 positions: 
 - horizontal: searching for fluffies
 - down: grab fluffies by feet
 - up: elevate fluffies to basket
 The claw has open and closed positions. A limit switch within the claw
 indicates whether a fluffy is successfully grabbed. 
*********************************************************************/

#include "armControl.h"

#define ARM_SERVO PB8
#define ARM_POT PB1
#define GRABBER_SERVO PB9
#define GRABBER_SWITCH PB12

#define DEADBAND 20
#define STOP 1473
#define GRABBER_OPEN 160
#define GRABBER_CLOSE 5
#define UP_LIMIT 2030
#define DOWN_LIMIT 90

/**
 * Obtain the following values from manual potentiometer testing
 * 1474: stops servo
 * greater than 1474 (eg.2000): bring arm down
 * smaller than 1474 (eg.1000): bring arm up
 */
#define RAISE 1000
#define LOWER 2000

Servo arm_servo;
Servo grabber_servo;
//constructor
ARMCONTROL::ARMCONTROL(int p_arm_servo_pin, int p_grabber_servo_pin, int p_grabber_switch, int p_arm_pot_pin)
{
    arm_servo_pin = p_arm_servo_pin;
    grabber_servo_pin = p_grabber_servo_pin;
    grabber_switch = p_grabber_switch;
    arm_pot_pin = p_arm_pot_pin;

    arm_default = 350;
    arm_up = 1900;
    arm_search = 150;
}

void ARMCONTROL::init()
{
    pinMode(grabber_switch, INPUT);
    pinMode(arm_pot_pin, INPUT);

    arm_servo.attach(arm_servo_pin);
    arm_servo.writeMicroseconds(STOP);
    grabber_servo.attach(grabber_servo_pin);
    grabber_servo.write(GRABBER_OPEN);
}
int ARMCONTROL::getEncoderVal()
{
    return analogRead(ARM_POT);
}
/**
 * Move arm to the desired position. There are three positions: default (horizontal), searching (slightly down) and up.
 **/
void ARMCONTROL::armPosition(int position)
{
    int encoder_val = getEncoderVal();
    while ((encoder_val < position - DEADBAND) || (encoder_val > position + DEADBAND))
    {
        if (encoder_val > position + DEADBAND)
        {
            arm_servo.writeMicroseconds(LOWER);
        }
        else if (encoder_val < position - DEADBAND)
        {
            arm_servo.writeMicroseconds(RAISE);
        }
        encoder_val = getEncoderVal();
    }
    stop();
}

void ARMCONTROL::stop()
{
    arm_servo.writeMicroseconds(STOP);
}

bool ARMCONTROL::outOfBounds(int encoder_val)
{
    if (encoder_val < UP_LIMIT || encoder_val > DOWN_LIMIT)
        return true;
    else
        return false;
}

void ARMCONTROL::grabberHug()
{
    grabber_servo.write(GRABBER_CLOSE);
}

void ARMCONTROL::grabberOpen()
{
    grabber_servo.write(GRABBER_OPEN);
}

int ARMCONTROL::switchStatus()
{
    return digitalRead(GRABBER_SWITCH);
}

void ARMCONTROL::info()
{
    Serial.println("switch: " + String(digitalRead(GRABBER_SWITCH)));
    Serial.println("encoder: " + String(getEncoderVal()));
}

void ARMCONTROL::armUp()
{
   armPosition(arm_up);
}

void ARMCONTROL::armDefault()
{
    armPosition(arm_default);
}

void ARMCONTROL::armSearch()
{
   armPosition(arm_search);
}