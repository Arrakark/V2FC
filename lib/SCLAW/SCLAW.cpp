#include "SCLAW.h"

#define CLOSED 125
#define OPEN 39
#define REST 0
#define DROPOFF 135

SCLAW::SCLAW(int _pincer_servo_pin, int _support_servo_pin, int _pickup_pin){
    pincer_servo_pin = _pincer_servo_pin;
    support_servo_pin = _support_servo_pin;
    pickup_pin = _pickup_pin;
}

void SCLAW::init() {
    pincer_servo.attach(pincer_servo_pin);
    support_servo.attach(support_servo_pin);
    pinMode(pickup_pin,INPUT_PULLUP);

    pincer_servo.write(OPEN);
    support_servo.write(REST);

}

void SCLAW::hug() {
     pincer_servo.write(CLOSED);
}

void SCLAW::open() {
    pincer_servo.write(CLOSED);
}

void SCLAW::pickup() {
    support_servo.write(REST);
}

void SCLAW::dropoff() {
    support_servo.write(DROPOFF);
}

bool SCLAW::checkSwitch() {
    if (digitalRead(pickup_pin) == LOW) return true;
    else return false;
}

void SCLAW::grabEwok() {
    pincer_servo.write(OPEN);
    support_servo.write(REST);
    if (checkSwitch()) {
        hug();
        delay(200);
        dropoff();
        delay(200);
        open();
        delay(500);
        hug();
        delay(500);
        pickup();
        delay(200);
        open();
    }
}