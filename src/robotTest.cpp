#include "HBRIDGE.h"
#include "armControl.h"
#include "SLIFT.h"
#include "IRBEACON.h"
#include "irsensor.h"

//Create left and right tracks
HBRIDGE left_motor = HBRIDGE(PB0, PA1);
HBRIDGE right_motor = HBRIDGE(PA7,PA3);
//Create scissor lift
SLIFT atb_slift = SLIFT(PA8);
//Create arm
ARMCONTROL atb_arm = ARMCONTROL(PB8,PB9,PB12,PB1);

void main (void) {
    Serial.begin(9600);

    //Initialize the tracks, scissor lift, and arm
    left_motor.init();
    right_motor.init();
    atb_slift.init();
    atb_arm.init();
}

/*
The loop tests the following functions of the robot
in the order they are shown:
    Arm
        -horizontal
        -search position
        -ewok position
        -ewok grab and switch satisfaction (press manually to continue program)
        -arm to basket position
        -ewok release
    Scissor Lift
        -check if scissor lift is in bottom position (should be true if scissor lift is down)
        -check if up position limit switch works (person presses this)
        -move scissor lift into up position
        -check if basket limit switch works (remove basket to make slift progress)
        -move scissor lift to down position
    Tracks
        -move left track forwards
        -move left track backwards
        -move right track forwards
        -move right track backards
        -move both tracks forwards
        -move both tracks backwards
        -move them in opposite directions
        -switch the opposite directions
        -full stop
    Sensor Arrays
        -PID array
        -ewok array
        -left edge array
        -right edge array
    Beacon Sensor


*/
void loop (void) {
    atb_arm.armHorizontal();
    delay(1000);
    atb_arm.armSearch();
    delay(1000);
    atb_arm.armPickup();
    delay(1000);
    atb_arm.grabberOpen();

}