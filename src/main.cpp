#include <robot.h>

robot atb = robot();

HBRIDGE bridge = HBRIDGE(PB0, PA1);

void setup()
{
    Serial.begin(230400, SERIAL_8E1); // Start Serial    Wire.begin();
    //Initialize the tracks, scissor lift, and arm
    //ARMCONTROL::init(PB8, PB9, PB12, PB1);
    atb.init();
    ARMCONTROL::disconnect();
    //atb.move_meters(2);
    // ARMCONTROL::grabberHug();
    // delay(2000);
    // ARMCONTROL::armDropoff();
    // delay(2000);
    // ARMCONTROL::grabberOpen();
}

void loop(void)
{
    ARMCONTROL::info();
    delay(300);
    //ARMCONTROL::armPickup();
}