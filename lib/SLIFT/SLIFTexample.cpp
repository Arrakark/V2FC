//This file is intended for testing the scissor lift mechanism
//The scissor lift class will be in different files
#include <Arduino.h>
#include <Servo.h>

#define DEBUG true
#define SERVOPIN PA8
#define POTPIN PA1

int lift_value = 0;

Servo s_lift;

void setup() {
    Serial.begin(9600);
    pinMode(SERVOPIN,OUTPUT);
    pinMode(POTPIN,INPUT);
    s_lift.attach(SERVOPIN);
}

void loop() {
    lift_value = map(analogRead(POTPIN),0,4096,0,180);
    if (DEBUG) Serial.println("SERVO VALUE : " + String(lift_value));
    s_lift.write(lift_value);
    delay(5);
}