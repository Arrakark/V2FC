#pragma once

#include <Arduino.h>

class surprise_2
{
public:
  static void stop_surprise();
  static void left_surprise();
  static void right_surprise();
  static void run_surprise_2();
  static void init_surprise_2();
private:
  surprise_2(){};
};