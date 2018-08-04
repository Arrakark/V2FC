#include "SCLAW.h"

SCLAW::SCLAW(int _pincer_servo_pin, int _support_servo_pin, int _pickup_pin){
    pincer_servo_pin = _pincer_servo_pin;
    support_servo_pin = _support_servo_pin;
    pickup_pin = _pickup_pin;
}

void SCLAW::init() {
    pincer_servo.attach(pincer_servo_pin);
    support_servo.attach(support_servo_pin);
    pinMode(pickup_pin,INPUT_PULLUP);
}

void SCLAW::hug() {
     
}

void SCLAW::open() {

}

void SCLAW::pickup() {

}

void SCLAW::dropoff() {

}