#ifndef SLIFT_H
#define SLIFT_H

#include <Arduino.h>
#include <Servo.h>

class SLIFT
{
    public:
        SLIFT(int _pin);
        static void init();
        static int move(int _dir);
    private:
        static Servo slift_servo;
        static bool atLimit(int _dir);
        static const int dir_array[3];
        static const int limit_array[3];
        static int servo_pin;
};

#endif