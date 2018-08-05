#include "SCLAW.h"

<<<<<<< HEAD
#define CLOSED 135
#define OPEN 39
#define REST 0
#define DROPOFF 155
=======
#define CLOSED 155
// #define OPEN 39
#define OPEN 60
#define REST 0
#define DROPOFF 160

#define PINCER_SERVO_PIN PB9
#define SUPPORT_SERVO_PIN PB8
//digital pin to check QSD
#define PICKUP_PIN PA11

SCLAW::SCLAW(){};
>>>>>>> 07a39864d1540f38cdcdd67f24b2c049d2cdd2e3

SCLAW::SCLAW(int _pincer_servo_pin, int _support_servo_pin, int _pickup_pin){
    pincer_servo_pin = _pincer_servo_pin;
    support_servo_pin = _support_servo_pin;
    pickup_pin = _pickup_pin;
}

void SCLAW::init() {
    pincer_servo.attach(pincer_servo_pin);
    support_servo.attach(support_servo_pin);
<<<<<<< HEAD
    support_servo.write(REST);
    delay(1000);
    pinMode(pickup_pin,INPUT_PULLUP);
=======
    // pinMode(pickup_pin,INPUT_PULLUP);
    pinMode(pickup_pin, INPUT);
>>>>>>> 07a39864d1540f38cdcdd67f24b2c049d2cdd2e3

    pincer_servo.write(OPEN);
    support_servo.write(REST);
}

void SCLAW::hug() {
     pincer_servo.write(CLOSED);
}

void SCLAW::open() {
    pincer_servo.write(OPEN);
}

void SCLAW::pickup() {
    support_servo.attach(support_servo_pin);
    support_servo.write(REST);
    delay(500);
    support_servo.detach();
}

void SCLAW::dropoff() {
    support_servo.attach(support_servo_pin);
    support_servo.write(DROPOFF);

}

// bool SCLAW::checkSwitch() {
//     if (digitalRead(pickup_pin) == LOW) return true;
//     else return false;
// }

//IF LOW, SOMETHING IS DETECTED WOOHOO
bool SCLAW::checkQSD(){
    if(digitalRead(PICKUP_PIN) == LOW) return true;
    else return false;
}

<<<<<<< HEAD
void SCLAW::grabEwok() {
    pincer_servo.write(OPEN);
    support_servo.write(REST);
    
    hug();
    delay(500);
    dropoff();
    delay(1200);
    open();
    delay(500);
    hug();
    delay(500);
    pickup();
    delay(200);
    open();
=======
// void SCLAW::grabEwok() {
//     pincer_servo.write(OPEN);
//     support_servo.write(REST);
    
//     if (checkQSD()) {
//         hug();
//         delay(500);
//         dropoff();
//         delay(500);
//         open();
//         delay(500);
//         // hug();
//         delay(500);
//         pickup();
//         delay(500);
//         // open();
//     }
// }

void SCLAW::info(){
    // Serial.println(checkQSD());
>>>>>>> 07a39864d1540f38cdcdd67f24b2c049d2cdd2e3
}