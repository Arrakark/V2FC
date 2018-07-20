#pragma once

#include <Arduino.h>
#include <armControl.h>
#include <SLIFT.h>
#include <HTHING.h>
#include <irsensor.h>
#include <IRBEACON.h>

#define NORMAL_SPEED 150
#define FULL_CLIFF_DISTANCE 15
#define GAP_CLIFF_DISTANCE 10
#define METERS_PER_SECOND 1.0
#define DEGREES_PER_SECOND 180.0
#define CLOSEST_DISTANCE_TO_EWOK 3.0
#define EWOK_SCANNING_INTERVAL 100 //interval in ms to scan for the ewok

class robot
{
public:
  //methods and constructor
  robot();

  //different parts of the robot
  //initialized in robot constructor
  ARMCONTROL *arm;
  HTHING *left_motor;
  HTHING *right_motor;
  irsensor *bottom_sensor;
  irsensor *front_sensor;
  irsensor *left_sensor;
  irsensor *right_sensor;
  SLIFT *lift;
};
