#include "armControl.h"

#define ARM_SERVO PB8   
#define ARM_POT PB1
#define GRABBER_SERVO PB9
#define GRABBER_SWITCH PB12 

ARMCONTROL ATB_arm = ARMCONTROL(ARM_SERVO, GRABBER_SERVO, GRABBER_SWITCH, ARM_POT);

void setup(void)
{
  Serial.begin(9600);
  ATB_arm.init();
  ATB_arm.debug = true;
  delay(1000);
}


void loop(void)
{
  
  ATB_arm.armHorizontal();
  delay(1000);
  ATB_arm.armPickup();
  delay(1000);
  ATB_arm.grabberHug();
  delay(1000);
  
  if (ATB_arm.switchStatus() == 0){
    ATB_arm.armDropoff();
    delay(1000);
    ATB_arm.grabberOpen();
  }
  else{
    ATB_arm.grabberOpen();
    delay(1000);
    ATB_arm.armHorizontal();
  }
  delay(1000);
  
  if(ATB_arm.debug){
    ATB_arm.info();
  }
  delay(500);
}
