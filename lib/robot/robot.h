#pragma once

#include <Arduino.h>
#include <armControl.h>
#include <SLIFT.h>
#include <HTHING.h>
#include <irsensor.h>
#include <IRBEACON.h>
#include <pid.h>
#include <HBRIDGE.h>

#define NORMAL_SPEED 230
#define TURN_SPEED 255
#define FULL_CLIFF_DISTANCE 20
#define GAP_CLIFF_DISTANCE 10
#define METERS_PER_SECOND 0.656
#define DEGREES_PER_SECOND 140.0
#define CLOSEST_DISTANCE_TO_EWOK 4.0
#define LINE_DISTANCE 5.0
#define EWOK_SCANNING_INTERVAL 100 //interval in ms to scan for the ewok

class robot
{
public:
  //methods and constructor
  robot();
  void init();
  void drive_until_cliff();
  void drive_until_black_line();
  void turn_degrees(float degrees);
  void move_meters(float meters);
  void sweep_for_ewok(float angle);
  void move_toward_ewok();
  void calibrate_meters_per_second(int seconds);
  void calibrate_degrees_per_second(int seconds);

  //different parts of the robot
  //initialized in robot constructor
  ARMCONTROL *arm;
  HBRIDGE *left_motor;
  HBRIDGE *right_motor;
  irsensor *bottom_sensor;
  irsensor *front_sensor;
  irsensor *left_sensor;
  irsensor *right_sensor;
  SLIFT *lift;
  pid *pid_controller;
};