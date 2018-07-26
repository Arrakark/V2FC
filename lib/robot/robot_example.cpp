#include <robot.h>

robot atb = robot();

HBRIDGE bridge = HBRIDGE(PB0, PA1);

void setup()
{
    Serial.begin(230400, SERIAL_8E1); // Start Serial    Wire.begin();
    //Initialize the tracks, scissor lift, and arm
    //ARMCONTROL::init(PB8, PB9, PB12, PB1);
    atb.init();
    ARMCONTROL::armPickup();
    ARMCONTROL::grabberOpen();
    delay(500);
    atb.follow_right_edge_until_ewok();
    delay(1000);
    ARMCONTROL::armPickup();
    delay(1000);
    ARMCONTROL::grabberHug();
    delay(1000);
    ARMCONTROL::armDropoff();
    delay(1000);
    ARMCONTROL::grabberOpen();
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