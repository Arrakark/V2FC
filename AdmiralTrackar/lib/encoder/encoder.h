#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"
#include <HardwareTimer.h>


class encoder
{
public:
	encoder(int _pin1, int pin_2);
    int count;
private:
    static void encoder_rise_1();
    static void encoder_rise_2();
};

encoder encoder_instance;

#endif