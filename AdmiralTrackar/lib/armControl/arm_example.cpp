#include "armControl.h"

#define ARM_SERVO PB8   
#define ARM_POT PB1
#define GRABBER_SERVO PB9
#define GRABBER_SWITCH PB12 

void setup(void)
{
  Serial.begin(230400, SERIAL_8E1);
  ARMCONTROL::init(ARM_SERVO, GRABBER_SERVO, GRABBER_SWITCH, ARM_POT);
  ARMCONTROL::grabberOpen();
}

void loop(void)
{
  //delay(2000);
  //ARMCONTROL::armVertical();
  ARMCONTROL::grabberOpen();
  delay(2000);
  ARMCONTROL::armHorizontal();
  ARMCONTROL::grabberHug();
}
