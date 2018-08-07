#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <Arduino.h>

class COMMUNICATOR
{
public:
    COMMUNICATOR(int _transmit_pin, int _receive_pin);
    void init();
    void setTransmission(bool _signal);
    bool checkReveice();
private:
    int transmit_pin;
    int receive_pin;
};

#endif
