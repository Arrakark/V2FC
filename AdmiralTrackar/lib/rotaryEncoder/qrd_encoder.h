#ifndef qrd_encoder_H
#define qrd_encoder_H

#include "Arduino.h"

#define THRESHOLD 1500 //[analog readings]
#define WHEEL_RADIUS 3.115 //[cm]
#define PI 3.14159265

class qrd_encoder
{
  public:
    qrd_encoder();
    qrd_encoder(int outputPin, int numDivisions);
    float getDistance();
    void reset();
    void count();

    
  private:
    int outputPin;
    int numDivisions;
    int counter;
    bool measure_state;
};

#endif