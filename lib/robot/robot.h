#pragma once

#include <Arduino.h>
#include <armControl.h>
#include <SLIFT.h>
#include <HTHING.h>
#include <irsensor.h>
#include <IRBEACON.h>
#include <pid.h>

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
  void drive_until_cliff();
  void drive_until_black_line();
  void turn_degrees(float degrees)
  void move_meters(float meters);
  void sweep_for_ewok(float angle);
  void move_toward_ewok();
  void calibrate_meters_per_second(int seconds);
  void calibrate_degrees_per_second(int seconds)
  
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
  pid * pid_controller;
};
