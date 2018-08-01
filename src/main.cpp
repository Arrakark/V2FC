#include <robot.h>
//#include <surprise.h>
robot atb = robot();

void setup()
{
    //Start Serial
    Serial.begin(230400, SERIAL_8E1);
    atb.init();
    delay(500);
    //surprise::run_surprise();

    // //==========================FIRST STAGE==========================
    //atb.first_ewok_pick_up();

    // //==========================SECOND STAGE==========================
    // atb.turn_until_black_line(LEFT); //sweep back to black line after grabbing ewok
    // robot::delay_update(500);
    // atb.turn_degrees(10); //to make the turn_until_black_line stop
    // robot::delay_update(500);
    // //This will try to cross the gap and then turn back onto the line
    // atb.find_gap_one(); 
    // robot::delay_update(500);
    // atb.move_meters(-0.2);
    // robot::delay_update(500);
    
    // atb.find_gap_one();
    // robot::delay_update(500);
    // atb.move_meters(-0.2);
    // robot::delay_update(500);
    // atb.move_meters(0.8);
    // ARMCONTROL::armPickup();
    // atb.move_toward_ewok();
    // robot::delay_update(500);
    // atb.grab_ewok();
    // robot::delay_update(500);
    // atb.move_meters(-0.2);
    // robot::delay_update(500);
    // atb.turn_until_black_line(LEFT);
    // robot::delay_update(500);
    //========================== IR BEACON ARCHWAY ==========================
    // ARMCONTROL::grabberHug();
    // ARMCONTROL::armDropoff();
    // robot::delay_update(1000);
    // atb.line_follow_until_beacon();
    // atb.wait_for_10khz();

    // //turn 90 degrees to the right
    // atb.line_follower->cross_gap=false;
    // atb.line_follower->default_speed=85;

    // //follow line until 3rd ewok is detected
    // atb.line_follow_until_second_ewok();
    //========THIRD EWOK==========
    ARMCONTROL::armVertical();
    atb.delay_update(500);
    atb.find_second_edge(); 
    ARMCONTROL::grabberOpen();
    ARMCONTROL::armPickup();
    atb.move_meters(-0.55);
    atb.delay_update(500);
    
    atb.sweep_ewok(LEFT);
    //atb.turn_degrees(45);

    atb.delay_update(500);
    atb.move_toward_ewok();
    atb.delay_update(500);
    atb.grab_ewok();

    //atb.turn_degrees(30);
    //atb.sweep_ewok(LEFT);
   // atb.move_toward_ewok();
    //move a bit more forward to approach ewok
   // atb.move_meters(0.07);
    //atb.grab_ewok();
    //atb.turn_until_black_line(RIGHT);
}

void loop()
{

   
   //atb.line_follower->follow_line();
    // atb.line_follower->follow_line();
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
    //atb.line_follower->follow_line();
    // atb.bottom_sensor->update();
    // atb.bottom_sensor->info();
    // Serial.println();
    // atb.delay_update(20);
    // atb.left_sensor->update();
    // atb.right_sensor->update();
    // atb.front_sensor->update();
    // Serial.print(atb.left_sensor->mean()); 
    // Serial.print(",");
    // Serial.print(atb.front_sensor->mean()); 
    // Serial.print(",");
    // Serial.println(atb.right_sensor->mean());
    atb.delay_update(20);
    atb.left_sensor->update();
    atb.right_sensor->update();
    atb.front_sensor->update();
    Serial.print(atb.left_sensor->min_distance()); 
    Serial.print(",");
    Serial.print(atb.front_sensor->min_distance()); 
    Serial.print(",");
    Serial.println(atb.right_sensor->min_distance());

    // atb.line_follow_until_second_ewok();
}