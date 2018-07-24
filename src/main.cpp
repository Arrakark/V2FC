#include "armControl.h"

#define ARM_SERVO PB8   
#define ARM_POT PB1
#define GRABBER_SERVO PB9
#define GRABBER_SWITCH PB12 

void setup(void)
{
  Serial.begin(230400, SERIAL_8E1);
  ARMCONTROL::init(ARM_SERVO, GRABBER_SERVO, GRABBER_SWITCH, ARM_POT);
  ARMCONTROL::armVertical();
}

void loop(void)
{
    ARMCONTROL::info();
}
