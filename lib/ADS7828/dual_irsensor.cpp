#include <dual_irsensor.h>

dual_irsensor::dual_irsensor(irsensor *_left_sensor, irsensor *_right_sensor) : irsensor()
{
    left_sensor = _left_sensor;
    right_sensor = _right_sensor;
}

void dual_irsensor::update()
{
    //update individual arrays
    left_sensor->update();
    right_sensor->update();

    //concatenate the readings
    for (int i = 0; i < 8; i++)
    {
        adc_readings[i] = left_sensor->adc_readings[i];
    }
    for (int i = 8; i < 16; i++)
    {
        adc_readings[i] = right_sensor->adc_readings[i - 8];
    }

    //concatenate distances
    for (int i = 0; i < 8; i++)
    {
        distance_readings[i] = left_sensor->distance_readings[i];
    }
    for (int i = 8; i < 16; i++)
    {
        distance_readings[i] = right_sensor->distance_readings[i - 8];
    }
}