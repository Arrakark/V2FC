#include <robot.h>
#define DELAY 2000
robot atb = robot();

void setup()
{
    Serial.begin(230400, SERIAL_8E1); // Start Serial    Wire.begin();
    //Initialize the tracks, scissor lift, and arm
    //ARMCONTROL::init(PB8, PB9, PB12, PB1);
    atb.init();
    // delay(2000);
    // atb.follow_right_edge_until_ewok();

}

void loop(void)
{
    //ARMCONTROL::armPickup();
    ARMCONTROL::armVertical();
    delay(DELAY);
    ARMCONTROL::armHorizontal();
    delay(DELAY);
    ARMCONTROL::grabberHug();
    delay(DELAY);
    ARMCONTROL::armDropoff();
    delay(DELAY);
    ARMCONTROL::armSearch();
    delay(DELAY);
    ARMCONTROL::grabberOpen();
    delay(DELAY);
    ARMCONTROL::grabberHug();
    delay(DELAY);
}