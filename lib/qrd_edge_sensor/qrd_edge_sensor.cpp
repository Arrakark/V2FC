#include "qrd_edge_sensor.h"


qrd_edge_sensor::qrd_edge_sensor(int _input_pin)
{
    input_pin = _input_pin;
}

void qrd_edge_sensor::init()
{
     //no need INPUT_PULLUP as there are already pullup resistors
    pinMode(input_pin,INPUT);

    sensor_value = 0;
}

void qrd_edge_sensor::update()
{
    sensor_value = analogRead(input_pin);
}

bool qrd_edge_sensor::detect_edge()
{
    bool flag = false;

    if(sensor_value > EDGE_THRESHOLD)
        flag = true;

    return flag;
}