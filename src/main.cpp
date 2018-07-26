#include <robot.h>

robot atb = robot();

void setup()
{
    Serial.begin(230400, SERIAL_8E1); // Start Serial    Wire.begin();
    //Initialize the tracks, scissor lift, and arm
    //ARMCONTROL::init(PB8, PB9, PB12, PB1);
    atb.init();
    delay(2000);
    atb.follow_right_edge_until_ewok();
    // ARMCONTROL::grabberHug();
    // delay(2000);
    // ARMCONTROL::armDropoff();
    // delay(2000);
    // ARMCONTROL::grabberOpen();
}

void loop(void)
{
    //ARMCONTROL::armPickup();
}