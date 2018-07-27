/**
 *Time trial code: 07/27/2018 
 **/
#include <robot.h>
#define DELAY 2000
#define LONG_DELAY 5000
robot atb = robot();
SLIFT lift = SLIFT(PA8);


void setup()
{
    //Start Serial
    Serial.begin(230400, SERIAL_8E1);     
    //Wire.begin();
    //Initialize the tracks, scissor lift, and arm
    atb.init();
    //atb.drive_until_cliff_early();
    //atb.follow_right_edge_until_ewok();
    //atb.grab_ewok();
    // atb.turn_degrees(-910);


    //===============GRAB FIRST EWOK =======================//
    atb.move_meters(1.6);
    atb.grab_ewok();
    atb.turn_degrees(180);
    atb.move_meters(1.6);
    //======================================================//

    //=============ARM CONTROL EXAMPLE =====================//
    ARMCONTROL::armSearch();
    robot::delay_update(DELAY);
    ARMCONTROL::grabberOpen();
    robot::delay_update(DELAY);
    ARMCONTROL::grabberHug();
robot::delay_update(2000);
    //if switch is detected, dropoff ewok
    if(ARMCONTROL::switchStatus){
        ARMCONTROL::armDropoff();
        robot::delay_update(LONG_DELAY);
        ARMCONTROL::grabberOpen();
        robot::delay_update(DELAY);
    } else {
        //if switch is not detected, no fluffies were detected
        //open claws and return to search position
        ARMCONTROL::grabberOpen();
        robot::delay_update(DELAY);
        ARMCONTROL::armSearch();
        robot::delay_update(DELAY);
    }
    //=======================================================//


    //================IR BEACON DETECTION====================//
    //IRBEACON::read(PA5);
    //IRBEACON::read(PA0);

    //=============CROSS FIRST GAP==========================//



    //=============CROSS SECOND GAP========================//




    //=============SCISSOR LIFT DEMO======================//
    ARMCONTROL::disconnect();
    robot::delay_update(2000);
    lift.init();
    robot::delay_update(2000);
    while (!lift.atDownLimit())
    {
        robot::delay_update(10);
    }
    while (!lift.atUpLimit())
    {
        robot::delay_update(10);
    }
    while (!lift.atBasketLimit())
    {
        robot::delay_update(10);
    }
    lift.moveUp();
    robot::delay_update(2000);
    lift.stay();
    robot::delay_update(2000);
    lift.moveDown();
    robot::delay_update(2000);

    //===============LINE FOLLOWING DEMO==================//

    //=============EDGE DETECTION DEMO ==================//









}

void loop(void)
{
    //========================SENSE FIRST EWOK ============================
    //atb.follow_right_edge_until_ewok();
    //atb.grab_ewok();





// atb.sensor_info();
//       atb.right_motor->run(100);
//       atb.left_motor->run(100);
//       robot::delay_update(1000);
//       atb.right_motor->run(-100);
//       atb.left_motor->run(-100);
//       robot::delay_update(1000);
}