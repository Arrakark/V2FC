#ifndef SURPRISE_H
#define SURPRISE_H

#include <Arduino.h>

class surprise
{
public:
  static void run_surprise();

private:
  static void beep(int note, int duration);
  static void firstSection();
  static void secondSection();
  surprise(){};
};

#endif
