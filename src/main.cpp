#include <HBRIDGE.h>
#include <armControl.h>

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
  
  ARMCONTROL::armHorizontal();
  delay(1000);
  ARMCONTROL::armPickup();
  delay(1000);
  ARMCONTROL::grabberHug();
  delay(1000);
  
  if (ARMCONTROL::switchStatus() == 0){
    ARMCONTROL::armDropoff();
    delay(1000);
    ARMCONTROL::grabberOpen();
  }
  else{
    ARMCONTROL::grabberOpen();
    delay(1000);
    ARMCONTROL::armHorizontal();
  }
  delay(1000);
  
  if(ARMCONTROL::debug){
    ARMCONTROL::info();
  }
}
