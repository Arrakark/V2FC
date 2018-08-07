#include "encoder.h"

encoder::encoder(int _pin1, int pin_2)
{
    attachInterrupt(_pin1, encoder_rise_1, RISING);
}

void encoder::encoder_rise_1()
{

}

void encoder::encoder_rise_2()
{

}