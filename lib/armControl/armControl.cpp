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

int ARMCONTROL::arm_pickup = 2940;
int ARMCONTROL::arm_search = 2800;
int ARMCONTROL::arm_horizontal = 2600;
int ARMCONTROL::arm_vertical = 1540;
int ARMCONTROL::arm_dropoff = 1320;
int ARMCONTROL::position = 1320;
bool ARMCONTROL::debug = false;

int ARMCONTROL::arm_pot_pin = -1;
int ARMCONTROL::grabber_switch = -1;
int ARMCONTROL::grabber_servo_pin = -1;
int ARMCONTROL::arm_servo_pin = -1;

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
    // ARMCONTROL::arm_pickup = 2940;
    // ARMCONTROL::arm_search = 2800;
    // ARMCONTROL::arm_horizontal = 2600;
    // ARMCONTROL::arm_vertical = 1540;
    // ARMCONTROL::arm_dropoff = 1320;

    position = arm_horizontal;

    pinMode(grabber_switch, INPUT_PULLUP);
    pinMode(arm_pot_pin, INPUT);

    arm_servo.attach(arm_servo_pin);
    grabber_servo.attach(grabber_servo_pin);

    HardwareTimer timer(4);
    // Pause the timer while we're configuring it
    timer.pause();

    // Set up period
    timer.setPeriod(100); // in microseconds

    // Set up an interrupt on channel 1
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1, 1); // Interrupt 1 count after each update
    timer.attachCompare1Interrupt(ARMCONTROL::update);

    // Refresh the timer's count, prescale, and overflow
    timer.refresh();

    // Start the timer counting
    timer.resume();
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
    //encoder value is outside range
    if (encoder_val > position + DEADBAND)
    {
        arm_servo.writeMicroseconds(RAISE);
    }
    else if (encoder_val < position - DEADBAND)
    {
        arm_servo.writeMicroseconds(LOWER);
    }
    else {
        stop();
    }
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
    Serial.println("switch: " + String(digitalRead(GRABBER_SWITCH)));
    Serial.println("encoder: " + String(getEncoderVal()));
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
