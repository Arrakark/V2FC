#include <HBRIDGE.h>
#include <armControl.h>


//creating robot object
robot admiral_track_bar = robot();


void setup()
{
    Serial.begin(230400, SERIAL_8E1); // Start Serial
    Serial.println("Sketch begin");
    admiral_track_bar.init();
    //admiral_track_bar.arm->init();
    //admiral_track_bar.arm->armVertical();
    Wire.begin();
    delay(3000);
    //admiral_track_bar.calibrate_degrees_per_second(15);
    //admiral_track_bar.turn_degrees(360);
    //delay(5000);
    //admiral_track_bar.calibrate_meters_per_second(3);
    admiral_track_bar.move_meters(1.75);
    admiral_track_bar.turn_degrees(-90);
    admiral_track_bar.move_meters(1);
    //admiral_track_bar.drive_until_cliff();
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

