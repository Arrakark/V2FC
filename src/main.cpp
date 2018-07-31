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

    ARMCONTROL::grabberHug();
    atb.line_follow_until_right_ewok();
    ARMCONTROL::grabberOpen();
    robot::delay_update(500);
    atb.move_toward_ewok();
    atb.move_meters(-0.05);
    atb.grab_ewok();
    atb.turn_until_black_line(-1);
    atb.turn_degrees(-1);
    robot::delay_update(2000);
    atb.line_follow_until_second_ewok();
    robot::delay_update(2000);
    // atb.move_meters(-0.05);
    atb.sweep_ewok(1);
    // atb.move_toward_ewok();
    atb.move_meters(0.08);
    atb.grab_ewok();
    // ARMCONTROL::arm45();
    // robot::delay_update(2000);
    // atb.wait_for_10khz();
    // atb.turn_until_black_line(-1);
}

void loop()
{
    // ARMCONTROL::grabberOpen();
    // robot::delay_update(2000);

    // ARMCONTROL::armPickup();
    // robot::delay_update(2000);

    // ARMCONTROL::grabberHug();
    // robot::delay_update(2000);

    // ARMCONTROL::armDropoff();
    // robot::delay_update(2000);

    // ARMCONTROL::grabberOpen();
    // robot::delay_update(2000);

    // ARMCONTROL::armSearch();
    // robot::delay_update(2000);

    // atb.line_follower->pid_controller.p_gain = 550.0;
    // atb.line_follower->default_speed = 120.0;
    // atb.line_follower->follow_line();
    // ARMCONTROL::arm45();
    atb.delay_update(20);
    // atb.right_sensor->info();
    // atb.sensor_info();
    // atb.left_sensor->update();
    // atb.right_sensor->update();
    // atb.front_sensor->update();
    // Serial.print(atb.left_sensor->mean()); 
    // Serial.print(" ");
    // Serial.print(atb.front_sensor->mean()); 
    // Serial.print(" ");
    // Serial.println(atb.right_sensor->mean());

    // Serial.print(atb.left_sensor->min_distance()); 
    // Serial.print(" ");
    // Serial.print(atb.front_sensor->min_distance()); 
    // Serial.print(" ");
    // Serial.println(atb.right_sensor->min_distance());
    // atb.right_sensor->update();
    // Serial.println(atb.right_sensor->min_distance());

    // atb.line_follow_until_second_ewok();
}