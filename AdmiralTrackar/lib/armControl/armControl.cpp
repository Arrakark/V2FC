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

#define DEADBAND 100
#define STOP 1473
#define GRABBER_OPEN 170
// #define GRABBER_CLOSE 25
#define GRABBER_CLOSE 35
#define GRABBER_TIGHT_CLOSE 25
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

int ARMCONTROL::arm_pickup = 2920;
int ARMCONTROL::arm_search = 2800;
int ARMCONTROL::arm_horizontal = 2600;
int ARMCONTROL::arm_vertical = 1540;
//int ARMCONTROL::arm_dropoff = 1380;
int ARMCONTROL::arm_dropoff = 1300;
int ARMCONTROL::position = 2600;
bool ARMCONTROL::debug = false;

int ARMCONTROL::arm_pot_pin = -1;
int ARMCONTROL::grabber_switch = -1;
int ARMCONTROL::grabber_servo_pin = -1;
int ARMCONTROL::arm_servo_pin = -1;
pid * ARMCONTROL::pid_controller = new pid();

void ARMCONTROL::init(int p_arm_servo_pin, int p_grabber_servo_pin, int p_grabber_switch, int p_arm_pot_pin)
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

    position = arm_horizontal;

    pinMode(grabber_switch, INPUT_PULLUP);
    pinMode(arm_pot_pin, INPUT);

    pid_controller->p_gain = 0.7;
    pid_controller->p_limit = 500;
    
    arm_servo.attach(arm_servo_pin);
    arm_servo.writeMicroseconds(STOP);
    grabber_servo.attach(grabber_servo_pin);
    grabber_servo.writeMicroseconds(GRABBER_OPEN);
}

void ARMCONTROL::disconnect(){
    arm_servo.detach();
    grabber_servo.detach();
}
int ARMCONTROL::getEncoderVal()
{
    return analogRead(ARM_POT);
}
/**
 * Move arm to the desired position. There are three positions: default (horizontal), searching (slightly down) and up.
 **/
void ARMCONTROL::update()
{
    int encoder_val = getEncoderVal();
    float value = pid_controller->output(encoder_val - position);
    arm_servo.writeMicroseconds(STOP + value);
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

bool ARMCONTROL::switchStatus()
{
    int reading = digitalRead(GRABBER_SWITCH);
    if (reading == 0)
        return (true);
    else
        return (false);
}

void ARMCONTROL::info()
{
    Serial.println("position: " + String(ARMCONTROL::position));
    Serial.println("switch: " + String(digitalRead(GRABBER_SWITCH)));
    Serial.println("encoder: " + String(getEncoderVal()));
}

void ARMCONTROL::arm45(){
    position = 2000;
}

void ARMCONTROL::armDropoff()
{
    position = arm_dropoff;
}

void ARMCONTROL::armVertical()
{
    position = arm_vertical;
}

void ARMCONTROL::armSearch()
{
    position = arm_search;
}

void ARMCONTROL::armHorizontal()
{
    position = arm_horizontal;
}

void ARMCONTROL::armPickup()
{
    position = arm_pickup;
}

void ARMCONTROL::grabberTightHug(){
    grabber_servo.write(GRABBER_TIGHT_CLOSE);
}

void ARMCONTROL::arm80(){
    position = 1600;
}