//using the the robot class
#include <Wire.h>
#include <Arduino.h>
#include <robot.h>
#include <irsensor.h>
#include <armControl.h>
#include <SLIFT.h>
#include <linefollower.h>


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
}

