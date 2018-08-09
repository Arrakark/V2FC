#include "beltLift.h"

beltLift::beltLift(int _upSwitch, int _downSwitch, liftMotor *_solar_bot_motor)
{
    upSwitch = _upSwitch;
    downSwitch = _downSwitch;
    solar_bot_motor = _solar_bot_motor;
}

void beltLift::init()
{
    solar_bot_motor->init();
    pinMode(upSwitch,INPUT);
    pinMode(downSwitch,INPUT);
}

void beltLift::liftUp()
{
    while(digitalRead(upSwitch))
    {
        solar_bot_motor->rotate(4095,HIGH);
        delay(20);
    }
}

void beltLift::liftDown()
{
    while(downSwitch)
    {
        solar_bot_motor->rotate(4095,LOW);
        delay(20);
    }
}
