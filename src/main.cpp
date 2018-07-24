#include <HBRIDGE.h>
#include <armControl.h>


//creating robot object
robot admiral_track_bar = robot();


void setup()
{
    Serial.begin(9600); // Start Serial
    Serial.println("Sketch begin");
    admiral_track_bar.init();
    Wire.begin();
    delay(5000);
    admiral_track_bar.calibrate_meters_per_second(5);
}

void loop()
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

