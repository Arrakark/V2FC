//#include "armControl.h"
#include <SLIFT.h>

// #define ARM_SERVO PB8   
// #define ARM_POT PB1
// #define GRABBER_SERVO PB9
// #define GRABBER_SWITCH PB12 

#define SLIFT_SERVO PA8

//ARMCONTROL ATB_arm = ARMCONTROL(ARM_SERVO, GRABBER_SERVO, GRABBER_SWITCH, ARM_POT);
SLIFT ATB_slift = SLIFT(SLIFT_SERVO);

void setup(void)
{
  Serial.begin(9600);
  //ATB_arm.init();
  //ATB_arm.debug = true;
  delay(6000);
  Serial.println("Going to init");
  ATB_slift.init();
  Serial.println("Initialized");
  delay(100);
  Serial.println("Goin Up");
  ATB_slift.moveUp();
  Serial.println("wut");
  ATB_slift.moveDown();
  //ATB_slift.slift_servo.writeMicroseconds(1405);
}

void loop(void)
{
//   ATB_arm.armPosition(ATB_arm.getDefaultPosition());
  
//   // ATB_arm.grabberHug();
//   // ATB_arm.grabberOpen();

//   //ATB_arm.armPosition(ATB_arm.getDefaultPosition());
//   //delay(1000);
//  // ATB_arm.armPosition(ATB_arm.getSearchPosition());
//   //delay(100);
//   if(ATB_arm.debug){
//     ATB_arm.info();
//   }
//   delay(500);
}
