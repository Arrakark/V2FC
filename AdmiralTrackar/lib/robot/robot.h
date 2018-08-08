#pragma once

#include <Arduino.h>
#include <armControl.h>
#include <SLIFT.h>
#include <HTHING.h>
#include <irsensor.h>
#include <IRBEACON.h>
#include <pid.h>
#include <HBRIDGE.h>
#include <linefollower.h>
#include <COMMUNICATOR.h>

// #define NORMAL_SPEED 150
#define NORMAL_SPEED 150
#define TURN_SPEED 120

#define METERS_PER_SECOND 0.46333333 //NORMAL_SPEED is 130 -> 0.46333333m/s
#define DEGREES_PER_SECOND 86        //TURN_SPEED is 200 -> 86 deg/sec
#define RIGHT -1
#define LEFT 1
#define ONCE 1
#define TWICE 2


//gaps
#define TURN_TABLE_GAP 10.3


class robot
{
public:
  //methods and constructor
  robot();
  void init();
  void drive_until_black_line();
  void turn_degrees(float degrees);
  void move_meters(float meters);
  void calibrate_meters_per_second(int seconds);
  void calibrate_degrees_per_second(int seconds);
  void ram_meters(float meters);
  static void delay_update(long ms);
  static void check_sensors();
  void sensor_info();
  void turn_until_black_line(int turn_dir);
  void find_gap_one(float _def_speed);
  void wait_for_10khz();
  void line_follow_until_beacon();
  void turn_table_detect(int num);
  void line_follow_until_right_ewok();


  //competition surface stages
  void establish_communication();
  void first_ewok_pick_up();
  void second_ewok_pick_up();
  void archway_crossing();
  void third_ewok_pick_up();
  void return_home();

  //info
  void sensor_mean();
  void sensor_inverse_mean();
  void sensor_min();

  //different parts of the robot
  //initialized in robot constructor
  HBRIDGE *left_motor;
  HBRIDGE *right_motor;
  irsensor *bottom_sensor;
  pid *pid_controller;
  linefollower *line_follower;
  COMMUNICATOR *arm_board_comm;
};  
