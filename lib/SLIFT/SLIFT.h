#ifndef SLIFT_H
#define SLIFT_H

#include <Arduino.h>
#include <Servo.h>

class SLIFT
{
    public:
        SLIFT(int _pin);
        void init();
        void moveUp();
        void moveDown();
        void stay();
        bool atDownLimit();
        bool atUpLimit();
        bool atBasketLimit();
        Servo slift_servo;
        void disconnect();
    private:
        int dir_array[3];
        int limit_array[3];
        int servo_pin;
};

#endif