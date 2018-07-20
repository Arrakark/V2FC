#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "Arduino.h"
#include <ADS7828.h> // Include ADS7828.h for TI ADS7828 functions

#define ROW 20
#define COL 9
#define MAX_VALUE 30
#define MIN_VALUE 0
#define SENSOR_COUNT 8

class irsensor
{
  public:
    irsensor();
    irsensor(unsigned char, int lookup_table[ROW][COL]);
    void update();
    float max_distance();
    float min_distance();
    float weighted_mean();
    float inverse_weighted_mean();
    float mean();
    int max_position();
    int min_position();
    int adc_readings[SENSOR_COUNT];
    float distance_readings[SENSOR_COUNT];
  private:
    ADS7828 adc;
    void get_distance();
    int (*lookup_table)[COL];
};

#endif