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
   // void armDefault();
   // void bottom();
    //void up();
    void stop();
    
    void grabberHug();
    void grabberOpen();
    int switchStatus();
    bool outOfBounds(int encoder_val);

    void info();
    //getters
    int getDefaultPosition();
    int getUpPosition();
    int getSearchPosition();

    private:
        int arm_servo_pin;
        int grabber_servo_pin;
        int grabber_switch;
        int arm_pot_pin;

        int arm_default;
        int arm_up;
        int arm_search;
        int arm_open;
        int arm_close;

        int grabber_open;
        int grabber_close;        
};

#endif