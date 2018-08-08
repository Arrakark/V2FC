#include <SCLAW.h>
#include <COMMUNICATOR.h>
#include <Arduino.h>
#include <Servo.h>

#define DELAY_TIME_LONG 500
#define DELAY_TIME_SHORT 4

COMMUNICATOR main_board_comm(PB7,PB6);
SCLAW right_claw(PA1,PA0,PB13);
SCLAW left_claw(PA3,PA2,PB12);

void establish_communication() {
    while (true) {
        if (main_board_comm.checkReceive()) break;
    }
    main_board_comm.setTransmission(true);
    delay(40);
    main_board_comm.setTransmission(false);
}

void first_ewok_sequence() {
    Serial.println("In 1");
    left_claw.dropoff();
    left_claw.hug();
    while (true) {
        if (right_claw.checkQSD()) break;
        delay(DELAY_TIME_SHORT);
    }
    //setting the transmission to true will stop admiral trackbar.
    //Admiral trackbar will remain stopped untill the signal is over.
    main_board_comm.setTransmission(true);
    right_claw.grabEwok();
    main_board_comm.setTransmission(false);
    Serial.println("End 1");
}

void second_ewok_sequence() {
    //This keeps this blue pill paused untill admiral trackbar
    //crosses the first gap. Admiral trackbar must send a high signal
    //for a while for this loop to stop
    left_claw.dropoff();
    left_claw.hug();
    while (true) {
        if (main_board_comm.checkReceive()) break;
        delay(DELAY_TIME_SHORT);
    }
    //now we are going to start checking for the next ewok.
    while (true) {
        if (right_claw.checkQSD()) break;
        delay(DELAY_TIME_SHORT);
    }
    //setting the transmission to true will stop admiral trackbar.
    //Admiral trackbar will remain stopped until the signal is over.
    //Here the robot picks up the second ewok, and it puts the claws into
    //position to cross through the archway
    main_board_comm.setTransmission(true);
    right_claw.grabEwok();
    delay(1000);
    right_claw.dropoff();
    right_claw.hug();
    left_claw.hug();
    delay(DELAY_TIME_LONG);
    left_claw.dropoff();
    main_board_comm.setTransmission(false);
    Serial.println("End 2");
    //both arms are folded
}

void third_ewok_sequence() {
    //This makes the arms stay in the up position untill
    //admiral trackbar tells the McFaster Claws
    while (true) {
        if (main_board_comm.checkReceive()) break;
        delay(DELAY_TIME_SHORT);
    }

    //Now the McFaster claws go down to be able to pick
    //up the third ewok

    left_claw.pickup();
    left_claw.open();
    delay(500);
    right_claw.dropoff();

    while (true){
        if (left_claw.checkQSD()) break;
    }

    //Now we stop Admiral Trackbar while the McFaster Claws
    //pickup the third Ewok

    main_board_comm.setTransmission(true);
  
    //This is a different pickup sequence that does not let the ewok fall.
    left_claw.open();
    left_claw.pickup();
    left_claw.hug();
    delay(500);
    left_claw.dropoff();
    delay(500);
    main_board_comm.setTransmission(false);
    Serial.println("End 3");
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
    //open, close, pickup, dropoff
    left_claw.init(120,20,150,1);
    delay(500);
    right_claw.init(40,140,1,180);
    establish_communication();

    Serial.println("Start 1");
    first_ewok_sequence();
    Serial.println("Start 2");
    second_ewok_sequence();
    Serial.println("Start 3");
    third_ewok_sequence();
    Serial.println("Start ret");
    return_sequence();

}

void loop() {
}