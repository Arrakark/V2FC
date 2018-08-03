#include <robot.h>
//#include <surprise.h>
robot atb = robot();

void setup()
{
    //Start Serial
    Serial.begin(230400, SERIAL_8E1);
    atb.init();
    ARMCONTROL::armVertical();
    //========================== FIRST EWOK ==========================
    //atb.first_ewok_pick_up();
    //========================== SECOND EWOK ==========================
    //atb.second_ewok_pick_up();
    //========================== IR BEACON ARCHWAY WAIT ==========================
    //atb.archway_crossing();
    //========================== LINE FOLLOW TO THIRD EWOK ==========================
    atb.third_ewok_pick_up();
    atb.delay_update(1000);
    //========================== SECOND GAP CROSSING ==========================
    atb.second_gap_crossing();
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
    // atb.bottom_sensor->update();
    //atb.bottom_sensor->info();
    //atb.delay_update(20);

    //atb.sensor_info();
    //atb.sensor_inverse_mean();
//atb.move_meters(-1);
//atb.sensor_min_distance();
atb.sensor_mean();
}