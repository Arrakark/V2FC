/**
 *Time trial code: 07/27/2018 
 **/
#include <robot.h>
robot atb = robot();

void setup()
{
    //Start Serial
    Serial.begin(230400, SERIAL_8E1);
    atb.init();
    // ARMCONTROL::grabberHug();
    // atb.line_follow_until_right_ewok();
    // ARMCONTROL::grabberOpen();
    // robot::delay_update(500);
    // atb.move_toward_ewok();
    // atb.move_meters(-0.05);
    // atb.grab_ewok();
    // atb.turn_until_black_line(-1);
    // atb.turn_degrees(-1);
    // robot::delay_update(2000);
}

void loop(){
    atb.line_follower->pid_controller.p_gain = 550.0;
    atb.line_follower->default_speed = 120.0;
    atb.line_follower->follow_line();
    atb.delay_update(20);
    // atb.right_sensor->info();
    atb.right_sensor->update();
    Serial.println(atb.right_sensor->mean());
}