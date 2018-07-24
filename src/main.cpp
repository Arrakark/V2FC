#include <HBRIDGE.h>

//create tracks
HBRIDGE left_motor = HBRIDGE(PB0, PA1);
HBRIDGE right_motor = HBRIDGE(PA7,PA3);

//The decleration of the HBRIDGE objects here has the correct pin layout
//for each motor

void setup()
{
  Serial.begin(9600); // Start Serial
  left_motor.init();
  right_motor.init();
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
}
