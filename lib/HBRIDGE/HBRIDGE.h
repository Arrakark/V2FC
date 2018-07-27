#ifndef HBRIDGE_H
#define HBRIDGE_H

#include <Arduino.h>
#include <HardwareTimer.h>

class HBRIDGE
{
  public:
    /*
    Make sure that the pins passed are pwm enabled pins. Attaches
    these pins to the HBRIDGE
    */
    HBRIDGE(int _forward_pin, int _reverse_pin);
    /*
    Safely initializes the HBRIDGE pins. Make sure to run this in
    setup for each HBRIDGE
    */
    void init();
    /*
    Takes an integer argument between -255 and 255. Positive values
    move the robot forwards and negative values move the robot backwards.
    A value of 0 stops the robot
    */
    void run(int _vector);
    /*
    The equivalent of saying run(0)
    */
    void stop();


  private:
    int forward_pin;
    int reverse_pin;
};

#endif
