//using the the robot class
#include <Wire.h>
#include <Arduino.h>
#include <robot.h>
#include <irsensor.h>
#include <armControl.h>
#include <SLIFT.h>
#include <linefollower.h>
#include <HBRIDGE.h>
#include <IRBEACON.h>

//creating robot object
robot atb = robot(); //admiral track bar

//global variables
bool ewok_trigger = false;
bool left_trigger = false;
bool right_trigger = false;
bool mid_trigger = false;
int num_ewok_grabbed = 0;
unsigned long start_event_time;
unsigned long end_event_time;

//function prototypes (might be changed to robot member functions)
void ewok_triggering();
void sweep_find_ewok();
void sweep_back();
void grab_ewok();

//stage function prototypes
void second_stage();

//==============================================================================================================

void setup()
{
    Serial.begin(9600); // Start Serial
    Serial.println("Sketch begin");
    Wire.begin();
    atb.init();
}

void loop()
{
}

//==============================================================================================================

//stage  functions

/*
    Second Stage of Competition

    Before: robot just fully crossed the first gap (straight and in the middle of tap)
            arm is horizontal 
            grabber is open

    Goals:  - pickup second ewok (at the right)
            - sense appropriate IR Beacon signal (10 kHz)
            - line follow through the archway within 5 seconds the start of 10 kHz signal
*/

void second_stage()
{
    //pick up second ewok (to the right)

    atb.line_follow_meters(0.3); //***
    atb.sweep_for_ewok(45);      //***
    grab_ewok();
    atb.turn_degrees(-45); //turn back to original position

    //----------------------------------------------------------------

    //sense appropriate IR Beacon Signal

    //line follow to appropriate IR Beacon Position
    atb.line_follow_meters(0.4); //***

    //adjust robot arm to appropriate IR Beacon sensing position
    ARMCONTROL::armVertical();

    //IR Beacon Sensing
    int value = IRBEACON::read(PA5);
    if (value == 2)
    {
        Serial.println("10khz Beacon detected!");
    }
}

//functions (might be added to the robot class if needed)

/*
function that triggers for ewok grabbing when ewok is near and stops the robot

function ends when:
left and right motors are stopped
grabber is open
arm is in search position

this/similar functions like that would be useful after grabbing the first ewok
*/
void ewok_triggering()
{
    //updating all three sensors
    atb.left_sensor->update();
    atb.right_sensor->update();
    atb.front_sensor->update();

    //***
    //left sensor triggering
    if (atb.left_sensor->min_distance < 4 && atb.left_sensor->inverse_weighted_mean() > 4.5)
    {
        left_trigger = true;
        ewok_trigger = true;
    }

    //right sensor triggering
    else if (atb.right_sensor->min_distance < 4 && atb.right_sensor->inverse_weighted_mean() < 4.5)
    {
        right_trigger = true;
        ewok_trigger = true;
    }

    //front sensor trigger
    else if (atb.front_sensor->min_distance < 4)
    {
        ewok_trigger = true;
    }

    atb.left_motor->stop();
    atb.right_motor->stop();
    ARMCONTROL::grabberOpen();
    ARMCONTROL::armSearch();
}

//=======================================

/*
sweep for ewok, depending how the ewok triggered
function ends when robot (or front sensor) is directly in front of ewok

Thoughts: will claw hit the ewok when it's sweeping?
Do we need our robot to step back first
or
Have our claw open
(before ewok_triggering/after ewok_triggering?)

For now, assume these thoughts are not true

Regardless think we should have some functions that are like that after the first ewok
*/
void sweep_find_ewok()
{
    start_event_time = millis();
    //sweep depending if the ewok is first sensed by the left or right sensor
    if (left_trigger)
    {
        // ***
        //turn robot to the left until second (default orientation) sensor of front sensor is less than 30
        // or first 2 (default) sensors of front sensor?
        while (atb.front_sensor->distance_readings[1] < 30)
        {
            atb.left_motor->run(-80); //default speed for sweeping <- slow enough for sensors
            atb.right_motor->run(80); //default speed for sweeping <- slow enough for sensors
        }

        //stop robot in the middle?

        //after ewok is centered, make left_trigger back to false
        //left_trigger = false;
    }

    else if (right_trigger)
    {
        // ***
        //turn robot to the right until second last (default orientation) sensor of front sensor is less than 30
        // or last 2 (default) sensors of front sensor?
        while (atb.front_sensor->distance_readings[6] < 30)
        {
            atb.left_motor->run(80);   //default speed for sweeping <- slow enough for sensors
            atb.right_motor->run(-80); //default speed for sweeping <- slow enough for sensors
        }

        //stop robot in the middle?

        //after ewok is centered, make right_trigger back to false
        //right_trigger = false;
    }

    //centering to ewok
    atb.front_sensor->update();

    while (atb.front_sensor->inverse_weighted_mean() != 4.5)
    {
        //to the left of sensor array (default orientation),but ewok to the robot's left -> turn left
        if (atb.front_sensor->inverse_weighted_mean() < 4.5)
        {
            atb.left_motor->run(-80); //default speed for sweeping <- slow enough for sensors
            atb.right_motor->run(80);
        }

        //to the right of sensor array (default orientation),but ewok to the robot's right -> turn right
        else if (atb.front_sensor->inverse_weighted_mean() > 4.5)
        {
            atb.left_motor->run(80); //default speed for sweeping <- slow enough for sensors
            atb.right_motor->run(-80);
        }
    }

    //stop once ewok is located in front of the robot & front sensor
    atb.left_motor->stop();
    atb.right_motor->stop();

    end_event_time = millis();
}

//=======================================

/*
	turns robot back to original position after it sweeps left or right to grab an ewok
	function should end when robot is stopped and is back to original position (maybe stepped a bit backwards)
*/
void sweep_back()
{
    //if sees ewok in the left before and it swept left, sweep robot to right
    if (left_trigger)
    {
        left_trigger = false;
        atb.left_motor->run(80);
        atb.right_motor->run(-80);
    }

    //if sees ewok in the right before and it swept right, sweep robot to left
    if (right_trigger)
    {
        right_trigger = false;
        atb.left_motor->run(-80);
        atb.right_motor->run(80);
    }

    delay(end_event_time - start_event_time);

    start_event_time = 0;
    end_event_time = 0;
}

//=======================================

void grab_ewok()
{
    //***assume arm is open and in search position in the beginning

    //zero when limit switch is pressed

    //repeat motion of grab_ewok until grabber switch is PRESSED
    while (ARMCONTROL::switchStatus()) // ***
    {
        //arm going down first
        ARMCONTROL::armPickup();

        //close the grabber to get the ewok
        ARMCONTROL::grabberHug();

        //count number of ewoks grabbed or check if the switch is pressed
        if (!ARMCONTROL::switchStatus()) //***
            num_ewok_grabbed++;

        //bring arm up towards the robot's basket
        ARMCONTROL::armDropoff();

        //open grabber
        ARMCONTROL::grabberOpen();

        //set arm back to default horizontal position
        ARMCONTROL::armHorizontal();
    }
}
