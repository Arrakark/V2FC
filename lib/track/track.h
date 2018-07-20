/*
 * Track class
 * Extends the functionality of the h-thing (motor) class by putting motor
 * in closed-loop PID control using the encoders.
 * UNFINISHED FOR NOW!
 */

#pragma once

#include <HTHING.h>
#include <pid.h>

class track {
public:
    track(HTHING *);
    void run(int vector);
    void stop();
private:
    HTHING * motor;
};