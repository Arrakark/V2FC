#pragma once

#include <Arduino.h>

class pid
{
  public:
    //consturctor
    pid();
    //member functions
    float output(float error);

    //take care when modifying these variables. Can lead to unexpected results if deleted or remapped.
    float p_gain, i_gain, d_gain;
    float p_limit, i_limit, d_limit;
    float i_sum;
    float d_error_prev;
  private:
	float apply_limit(float, float);
	unsigned long last_cycle_time;
};
