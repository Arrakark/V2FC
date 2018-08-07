/*
 *  IRBEACON.h
 *  How to use:
 *  IRBEACON::read(PA5) returns a value
 *  if returns 0, there is no beacon in sight
 *  if returns 1, there is a 1khz beacon in sight
 *  if returns 2, there is a 10khz beacon in sight
 * 
 *  IR detector needs to be a black-led-like thing with a 330 pulldown on the emmiter,
 *  emmitter connected to the bluepill, and the collector pulled high to 3.3v!!! 
 *  5V WILL DAMAGE BLUEPILL!!!
 */

#ifndef IRBEACON_H
#define IRBEACON_H

#include <Arduino.h>
#include <HardwareTimer.h>

//DO NOT CHANGE! WORKS PERFECT!
#define SAMPLING_TIME 5 //sampling period in us (microseconds)
#define NUMBER_OF_SAMPLES 300 //number of samples in array

#define TIMER 1
#define NO_BEACON 0
#define ONE_KHZ 1
#define TEN_KHZ 10


class IRBEACON
{
  public:
    static int read(int _pin);
  private:
    static int times_crossed();
    static int pin;
    static int count;
    static int readings[NUMBER_OF_SAMPLES];
    IRBEACON() {}
    static void sample();
};

#endif