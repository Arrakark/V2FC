#include <SCLAW.h>
#include <COMMUNICATOR.h>
#include <Arduino.h>
#include <Servo.h>

#define DELAY_TIME_LONG 500
#define DELAY_TIME_SHORT 4

COMMUNICATOR main_board_comm(PB7,PB6);
SCLAW right_claw(PA1,PA0,PB13);
SCLAW left_claw(PA3,PA2,PB12);


void first_ewok_sequence() {
    while (true) {
        if (right_claw.checkQSD()) break;
        delay(DELAY_TIME_SHORT);
    }
    //setting the transmission to true will stop admiral trackbar.
    //Admiral trackbar will remain stopped untill the signal is over.
    main_board_comm.setTransmission(true);
    right_claw.grabEwok();
    main_board_comm.setTransmission(false);
}

void second_ewok_sequence() {
    //This keeps this blue pill paused untill admiral trackbar
    //crosses the first gap. Admiral trackbar must send a high signal
    //for a while for this loop to stop
    while (true) {
        if (main_board_comm.checkReveice()) break;
        delay(DELAY_TIME_SHORT);
    }
    //now we are going to start checking for the next ewok.
    while (true) {
        if (right_claw.checkQSD()) break;
        delay(DELAY_TIME_SHORT);
    }
    //setting the transmission to true will stop admiral trackbar.
    //Admiral trackbar will remain stopped untill the signal is over.
    //Here the robot picksup the second ewok, and it puts the claws into
    //position to cross through the archway
    main_board_comm.setTransmission(true);
    right_claw.grabEwok();
    right_claw.dropoff();
    right_claw.hug();
    left_claw.hug();
    delay(DELAY_TIME_LONG);
    left_claw.dropoff();
    main_board_comm.setTransmission(false);
}

void third_ewok_sequence() {
    //This makes the arms stay in the up position untill
    //admiral trackbar tells the McFaster Claws. 
    while (true) {
        if (main_board_comm.checkReveice()) break;
        delay(DELAY_TIME_SHORT);
    }

    //Now the McFaster claws go down to be able to pick
    //up the third ewok

    left_claw.pickup();
    left_claw.open();
    delay(DELAY_TIME_LONG);
    right_claw.pickup();

    while (true){
        if (left_claw.checkQSD()) break;
    }

    //Now we stop Admiral Trackbar while the McFaster Claws
    //pickup the third Ewok

    main_board_comm.setTransmission(true);
    left_claw.grabEwok();
    main_board_comm.setTransmission(false);
}

void return_sequence() {
    right_claw.dropoff();
    right_claw.hug();
    left_claw.hug();
    delay(DELAY_TIME_LONG);
    left_claw.dropoff();
}

void setup() {
    Serial.begin(9600);
    main_board_comm.init();
    right_claw.init();
    left_claw.init();

    first_ewok_sequence();
    second_ewok_sequence();
    third_ewok_sequence();
    return_sequence();
}

void loop() {
    
}