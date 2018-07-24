#include "armControl.h"

#define ARM_SERVO PB8   
#define ARM_POT PB1
#define GRABBER_SERVO PB9
#define GRABBER_SWITCH PB12 

//ARMCONTROL ATB_arm = ARMCONTROL(ARM_SERVO, GRABBER_SERVO, GRABBER_SWITCH, ARM_POT);

void setup(void)
{
  Serial.begin(9600);
  ARMCONTROL::init(ARM_SERVO, GRABBER_SERVO, GRABBER_SWITCH, ARM_POT);
  ARMCONTROL::debug = true;
  delay(1000);
}

void loop(void)
{
  
  // ATB_arm.grabberHug();
  // ATB_arm.grabberOpen();

  //ATB_arm.armPosition(ATB_arm.getDefaultPosition());
  //delay(1000);
 // ATB_arm.armPosition(ATB_arm.getSearchPosition());
  //delay(100);
  if(ARMCONTROL::debug){
    ARMCONTROL::info();
  }
  delay(500);
}
