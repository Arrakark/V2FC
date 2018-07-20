#ifndef SLIFT_H
#define SLIFT_H

#include <Arduino.h>
#include <Servo.h>

class SLIFT
{
    public:
        static int move(int _dir);
        SLIFT(int _pin);
    private:
        static Servo slift_servo;
        static bool atLimit(int _dir);
        static const int dir_array[3];
        static const int limit_array[3];
};

#endif