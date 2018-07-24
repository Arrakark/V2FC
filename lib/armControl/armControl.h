#pragma once
#ifndef ARMCONTROL_H
#define ARMCONTROL_H

#include "Arduino.h"
#include "Servo.h"

class ARMCONTROL
{
    public:
    bool debug;
    /**
     * Constructor initializing the arm and attaching it to relevant servo
     * pins
    **/
    ARMCONTROL(int arm_servo_pin, int grabber_servo_pin, int grabber_switch, int arm_pot_pin);

    void init();
    /**
     * Base servo moves until potentiometer reads specified value
     **/
    int getEncoderVal();
    void armPosition(int position);
    void stop();
    
    void grabberHug();
    void grabberOpen();
    bool switchStatus();
    bool outOfBounds(int encoder_val);

    void info();

    void armDropoff();
    void armVertical();
    void armSearch();
    void armHorizontal();
    void armPickup();

    private:
        int arm_servo_pin;
        int grabber_servo_pin;
        int grabber_switch;
        int arm_pot_pin;

        int arm_dropoff;
        int arm_vertical;
        int arm_search;
        int arm_horizontal;
        int arm_pickup;

        int grabber_open;
        int grabber_close;        
};

#endif