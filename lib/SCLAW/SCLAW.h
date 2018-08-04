#ifndef SCLAW_H
#define SCLAW_H

#include <Arduino.h>
#include <Servo.h>

class SCLAW:
{
public:
    SCLAW(int _pincer_servo_pin, int _support_servo_pin, int _pickup_pin);
    void init();
    void hug();
    void open();
    void pickup();
    void dropoff();
private:
    int val_open;
    int val_close;
    int val_pickup;
    int val_dropoff;

    Servo pincer_servo;
    Servo support_servo;

    int pincer_servo_pin;
    int support_servo_pin;
    int pickup_pin;

};

#endif
