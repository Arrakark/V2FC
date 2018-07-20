#include "robot.h"



robot::robot()
{
    //elbow servo is servo 1, grabber servo is servo 2
    //limit switch is the first limit switch
    arm = new ARMCONTROL(PB8, PB9, PB12, PB1);
    //left motor is motor 2
    left_motor = new HTHING(PB0, PB3);
    //left motor is motor 3
    right_motor = new HTHING(PA7, PB5);
    bottom_sensor = new irsensor(0x49, lookup_table_2);
    front_sensor = new irsensor(0x48, lookup_table_1);
    left_sensor = new irsensor(0x4A, lookup_table_3);
    right_sensor = new irsensor(0x4B, lookup_table_4);
    lift = new SLIFT(int _pin);
}