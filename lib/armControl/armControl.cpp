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

#define DEADBAND 10
#define STOP 1473
#define GRABBER_OPEN 160
#define GRABBER_CLOSE 5
#define UP_LIMIT 1300
#define DOWN_LIMIT 2950

/**
 * Obtain the following values from manual potentiometer testing
 * 1474: stops servo
 * greater than 1473 (eg.2000): bring arm down
 * smaller than 1473 (eg.1000): bring arm up
 */
#define RAISE 2000
#define LOWER 1000

Servo arm_servo;
Servo grabber_servo;
//constructor
armControl::armControl(int p_arm_servo_pin, int p_grabber_servo_pin, int p_grabber_switch, int p_arm_pot_pin)
{
    arm_servo_pin = p_arm_servo_pin;
    grabber_servo_pin = p_grabber_servo_pin;
    grabber_switch = p_grabber_switch;
    arm_pot_pin = p_arm_pot_pin;


    /**
     * Calibrated values via encoder potentiometer:
     * lower limit: 2950
     * upper limit: 1300
     * horizontal: 2600
     * drop off:1320
     * vertical: 1590
     * search:2800
     * down: pickup (2940)
     */
    arm_pickup = 2940;
    arm_search = 2800;
    arm_horizontal = 2600;
    arm_vertical = 1540;
    arm_dropoff = 1320;
}

void armControl::init()
{
    pinMode(grabber_switch, INPUT_PULLUP);
    pinMode(arm_pot_pin, INPUT);

    arm_servo.attach(arm_servo_pin);
    arm_servo.writeMicroseconds(STOP);
    grabber_servo.attach(grabber_servo_pin);
    grabber_servo.write(GRABBER_OPEN);
}
int armControl::getEncoderVal()
{
    return analogRead(ARM_POT);
}
/**
 * Move arm to the desired position. There are three positions: default (horizontal), searching (slightly down) and up.
 **/
void armControl::armPosition(int position)
{
    int encoder_val = getEncoderVal();
    //encoder value is outside range
    while ((encoder_val < position - DEADBAND) || (encoder_val > position + DEADBAND))
    {
        if (encoder_val > position + DEADBAND)
        {
            arm_servo.writeMicroseconds(RAISE);
        }
        else if (encoder_val < position - DEADBAND)
        {
            arm_servo.writeMicroseconds(LOWER);
        }
        encoder_val = getEncoderVal();
    }
    stop();
}

void armControl::stop()
{
    arm_servo.writeMicroseconds(STOP);
}

bool armControl::outOfBounds(int encoder_val)
{
    if (encoder_val < UP_LIMIT || encoder_val > DOWN_LIMIT)
        return true;
    else
        return false;
}

void armControl::grabberHug()
{
    grabber_servo.write(GRABBER_CLOSE);
}

void armControl::grabberOpen()
{
    grabber_servo.write(GRABBER_OPEN);
}

int armControl::switchStatus()
{
    return digitalRead(GRABBER_SWITCH);
}

void armControl::info()
{
    Serial.println("switch: " + String(digitalRead(GRABBER_SWITCH)));
    Serial.println("encoder: " + String(getEncoderVal()));
}

void armControl::armDropoff()
{
   armPosition(arm_dropoff);
}

void armControl::armVertical()
{
    armPosition(arm_vertical);
}

void armControl::armSearch()
{
   armPosition(arm_search);
}

void armControl::armHorizontal()
{
    armPosition(arm_horizontal);
}

void armControl::armPickup()
{
    armPosition(arm_pickup);
}