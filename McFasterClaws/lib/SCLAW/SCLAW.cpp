#include "SCLAW.h"


SCLAW::SCLAW(int _pincer_servo_pin, int _support_servo_pin, int _pickup_pin){
    pincer_servo_pin = _pincer_servo_pin;
    support_servo_pin = _support_servo_pin;
    pickup_pin = _pickup_pin;
}

void SCLAW::init(int _val_open, int _val_close, int _val_pickup, int _val_dropoff) {
    val_close = _val_close;
    val_open = _val_open;
    val_dropoff = _val_dropoff;
    val_pickup = _val_pickup;

    pincer_servo.attach(pincer_servo_pin);
    support_servo.attach(support_servo_pin);
    pinMode(pickup_pin, INPUT);

    pincer_servo.write(val_open);
    support_servo.write(val_pickup);
}

void SCLAW::hug() {
     pincer_servo.write(val_close);
}

void SCLAW::open() {
    pincer_servo.write(val_open);
}

void SCLAW::pickup() {
   // support_servo.attach(support_servo_pin);
    support_servo.write(val_pickup);
    //support_servo.detach();
}

void SCLAW::dropoff() {
    //support_servo.attach(support_servo_pin);
    support_servo.write(val_dropoff);

}

// bool SCLAW::checkSwitch() {
//     if (digitalRead(pickup_pin) == LOW) return true;
//     else return false;
// }

//IF LOW, SOMETHING IS DETECTED WOOHOO
bool SCLAW::checkQSD(){
    if(digitalRead(pickup_pin) == LOW) return true;
    else return false;
}

void SCLAW::grabEwok() {
    pincer_servo.write(val_open);
    support_servo.write(val_pickup);
    
    hug();
    delay(500);
    dropoff();
    delay(1000);
    open();
    delay(500);
    // hug();
    delay(500);
    pickup();
    delay(500);
    // open();
    
}

void SCLAW::info(){
    // Serial.println(checkQSD());
}