#pragma once
#ifndef ARMCONTROL_H
#define ARMCONTROL_H

#include "Arduino.h"
#include "Servo.h"
#include "Time.h"
#include <HardwareTimer.h>
#include <pid.h>

class ARMCONTROL
{
  public:
    static bool debug;
    /**
     * Constructor initializing the arm and attaching it to relevant servo
     * pins
    **/
    //ARMCONTROL(int arm_servo_pin, int grabber_servo_pin, int grabber_switch, int arm_pot_pin);

    static void init(int, int, int, int);
    /**
     * Base servo moves until potentiometer reads specified value
     **/
    static int getEncoderVal();
    static void update();
    static void stop();

    static void grabberHug();
    static void grabberOpen();
    static bool switchStatus();
    static bool outOfBounds(int encoder_val);

    static void info();

    static void armDropoff();
    static void armVertical();
    static void armSearch();
    static void armHorizontal();
    static void armPickup();

  private:
    ARMCONTROL() {}
    static int position;

    static int arm_servo_pin;
    static int grabber_servo_pin;
    static int grabber_switch;
    static int arm_pot_pin;

    static int arm_dropoff;
    static int arm_vertical;
    static int arm_search;
    static int arm_horizontal;
    static int arm_pickup;

    static int grabber_open;
    static int grabber_close;

    static pid * pid_controller;
  };

#endif