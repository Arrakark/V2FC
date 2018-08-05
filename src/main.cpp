#include <robot.h>
robot atb = robot();

void setup()
{
    //Start Serial
    Serial.begin(230400,  8E1);
    atb.init();

<<<<<<< HEAD
   

    //=====grab third ewok sequence=====/

=======
   //=====grab third ewok sequence=====/
>>>>>>> 07a39864d1540f38cdcdd67f24b2c049d2cdd2e3
    //========================== FIRST EWOK ==========================
     atb.first_ewok_pick_up();
    // atb.right_claw->open();
    //========================== SECOND EWOK ==========================
     //atb.second_ewok_pick_up();
    //========================== IR BEACON ARCHWAY WAIT ==========================
<<<<<<< HEAD
     //atb.archway_crossing();
    //========================== LINE FOLLOW TO THIRD EWOK ==========================
     //atb.third_ewok_pick_up();
     //atb.delay_update(1000);
    //========================== SECOND GAP CROSSING ==========================
    //atb.second_gap_crossing();
=======
    //  atb.archway_crossing();
    //========================== LINE FOLLOW TO THIRD EWOK ==========================
    //  atb.third_ewok_pick_up();
    //  atb.delay_update(1000);
    //========================== SECOND GAP CROSSING ==========================
    // atb.second_gap_crossing();
>>>>>>> 07a39864d1540f38cdcdd67f24b2c049d2cdd2e3
    //========================== FOURTH EWOK ==========================
    //========================== CHEWBACCA ==========================
    //========================== ZIPLINE ==========================
  // atb.turn_degrees(45);
   // // ARMCONTROL::arm80();
    // atb.delay_update(1000);
    // atb.turn_degrees(190);
    //atb.move_meters(-0.2);
    // atb.sweep_for_zipline(RIGHT);
    // atb.delay_update(1000);
    // atb.zipline_follow();
    
    //atb.turn_degrees(90);
}

void loop()
{
    // atb.left_motor->run(255);
    // atb.right_motor->run(255);
    // atb.bottom_sensor->update();
    //atb.bottom_sensor->info();
<<<<<<< HEAD
    //atb.delay_update(20);
    //atb.left_sensor->info();
=======
    // Serial.println(atb.right_claw->checkQSD());
    // atb.right_claw->info();
    // atb.delay_update(500);
    // atb.left_sensor->info();
>>>>>>> 07a39864d1540f38cdcdd67f24b2c049d2cdd2e3
    // atb.front_sensor->info();
    //atb.sensor_inverse_mean();
//atb.move_meters(-1);
//atb.sensor_min_distance();
// atb.bottom_sensor->update();
// Serial.println(atb.bottom_sensor->mean());
}