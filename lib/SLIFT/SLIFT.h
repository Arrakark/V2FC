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
        Servo slift_servo;
    private:
        bool atLimit(int _dir);
        int dir_array[3];
        int limit_array[3];
        int servo_pin;
};

#endif