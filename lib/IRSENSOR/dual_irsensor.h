#ifndef DUAL_IRARRAY_H
#define DUAL_IRARRAY_H

#include "Arduino.h"
#include <irsensor.h>

#define SENSOR_COUNT 16

class dual_irsensor : public irsensor
{
  public:
    dual_irsensor(irsensor * left_sensor, irsensor * right_sensor);
    void update();
    int adc_readings[SENSOR_COUNT];
    float distance_readings[SENSOR_COUNT];
  private:
    irsensor * left_sensor;
    irsensor * right_sensor;
};

#endif