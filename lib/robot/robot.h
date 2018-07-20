#pragma once

#include <Arduino.h>
#include <armControl.h>
#include <SLIFT.h>
#include <HTHING.h>
#include <irsensor.h>
#include <IRBEACON.h>

enum state {
  do_nothing,
  manual_control,
  run_full_track,

}

class robot
{
  public:
  //methods and constructor
  robot();


  state current_state;
  //different parts of the robot
  //initialized in robot constructor
  ARMCONTROL * arm;
  HTHING * left_motor;
  HTHING * right_motor;
  irsensor * bottom_sensor;
  irsensor * front_sensor;
  irsensor * left_sensor;
  irsensor * right_sensor;
  SLIFT * lift;
};
