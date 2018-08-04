#ifndef qrd_edge_sensor_H
#define qrd_edge_sensor_H

#define EDGE_THRESHOLD 1000 //works on white surfaces, qrd also might be a bit out of the edge

#include <Arduino.h>

class qrd_edge_sensor
{
    public:
        qrd_edge_sensor(int input_pin);
        void init();
        void update();
        bool detect_edge();
        int sensor_value;
    private:
        int input_pin;
};

#endif