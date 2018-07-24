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
    //admiral_track_bar.arm->init();
    //admiral_track_bar.arm->armVertical();
    Wire.begin();
    delay(3000);
    //admiral_track_bar.calibrate_degrees_per_second(15);
    //admiral_track_bar.turn_degrees(360);
    //delay(5000);
    //admiral_track_bar.calibrate_meters_per_second(3);
    //admiral_track_bar.move_meters(2.14);
    admiral_track_bar.drive_until_cliff();
}

void loop()
{
}

