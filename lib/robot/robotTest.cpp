#include "HBRIDGE.h"
#include "armControl.h"
#include "SLIFT.h"
#include "IRBEACON.h"
#include "irsensor.h"

#define DELAY_VAL 1000

//Create left and right tracks
HBRIDGE left_motor = HBRIDGE(PB0, PA1);
HBRIDGE right_motor = HBRIDGE(PA7,PA3);
//Create scissor lift
SLIFT atb_slift = SLIFT(PA8);
//Create arm
ARMCONTROL atb_arm = ARMCONTROL(PB8,PB9,PB12,PB1);

void setup() {
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
        -arm vertical
        -arm to basket position
        -ewok release
    Scissor Lift
        -check if scissor lift is in bottom position (should be true if scissor lift is down)
        -check if up position limit switch works (person presses this)
        -check if basket limit switch works
        -move scissor lift into up position
        -check that stay function works
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
    //Arm Testing
    Serial.println("ARM HORIZONTAL");
    atb_arm.armHorizontal();
    delay(DELAY_VAL);
    Serial.println("ARM SEARCH");
    atb_arm.armSearch();
    delay(DELAY_VAL);
    Serial.println("ARM PICKUP");
    atb_arm.armPickup();
    delay(DELAY_VAL);
    Serial.println("GRABBER OPEN");
    atb_arm.grabberOpen();
    Serial.println("PRESS GRABBER SWITCH TO CONTINUE");
    while (!atb_arm.switchStatus()) {
        delay(10);
    }
    Serial.println("GRABBER CLOSING");
    atb_arm.grabberHug();
    delay(DELAY_VAL);
    Serial.println("ARM VERTICAL");
    atb_arm.armVertical();
    delay(DELAY_VAL);
    Serial.println("ARM DROP OFF");
    atb_arm.armDropoff();
    delay(DELAY_VAL);
    Serial.println("GRABBER OPEN");
    atb_arm.grabberOpen();
    delay(DELAY_VAL);
    Serial.println("ARM HORIZONTAL");
    atb_arm.armHorizontal();
    Serial.println("ARM TESTING DONE");

    //Scissor lift Testing
    Serial.println("PRESS DOWN POSITION LIMIT SWITCH TO CONITNUE");
    while (!atb_slift.atDownLimit()) {
        delay(10);
    }
    Serial.println("PRESS UP POSITION LIMIT SWITCH TO CONITNUE");
    while (!atb_slift.atUpLimit()) {
        delay(10);
    }
    Serial.println("PRESS BASKET LIMIT SWITCH TO CONITNUE");
    while (!atb_slift.atBasketLimit()) {
        delay(10);
    }
    Serial.println("MOVING TO UP POSITION");
    atb_slift.moveUp();
    delay(DELAY_VAL);
    Serial.println("STAING IN POSITION - we never actually need to use this function");
    atb_slift.stay();
    delay(DELAY_VAL);
    Serial.println("MOVING TO UP POSITION");
    atb_slift.moveDown();
    delay(DELAY_VAL);
    Serial.println("SCISSOR LIFT TESTING DONE");

    //Motor Testing
    Serial.println("LEFT MOTOR FORWARD");
    left_motor.run(180);
    delay(3000);
    Serial.println("STOP");
    left_motor.stop();
    delay(DELAY_VAL);
    Serial.println("LEFT MOTOR REVERSE");
    left_motor.run(-180);
    delay(3000);
    Serial.println("STOP");
    left_motor.stop();
    delay(DELAY_VAL);

    Serial.println("RIGHT MOTOR FORWARD");
    right_motor.run(180);
    delay(3000);
    Serial.println("STOP");
    right_motor.stop();
    delay(DELAY_VAL);
    Serial.println("RIGHT MOTOR REVERSE");
    right_motor.run(-180);
    delay(3000);
    Serial.println("STOP");
    right_motor.stop();
    delay(DELAY_VAL);

    Serial.println("BOTH MOTOR FORWARD");
    left_motor.run(180);
    right_motor.run(180);
    delay(3000);
    Serial.println("STOP");
    left_motor.stop();
    right_motor.stop();
    delay(DELAY_VAL);
    Serial.println("BOTH MOTOR REVERSE");
    left_motor.run(-180);
    right_motor.run(-180);
    delay(3000);
    Serial.println("STOP");
    left_motor.stop();
    right_motor.stop();
    delay(DELAY_VAL);

    Serial.println("LEFT MOTOR FORWARD RIGHT MOTOR REVERSE");
    left_motor.run(180);
    right_motor.run(-180);
    delay(3000);
    Serial.println("STOP");
    left_motor.stop();
    right_motor.stop();
    delay(DELAY_VAL);
    Serial.println("RIGHT MOTOR FORWARD LEFT MOTOR REVERSE");
    left_motor.run(-180);
    right_motor.run(180);
    delay(3000);
    Serial.println("STOP");
    left_motor.stop();
    right_motor.stop();
    delay(DELAY_VAL);

    //Sensor Array Tests
    

    //Beacon Sensor Test

}