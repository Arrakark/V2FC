#include <robot.h>
//#include <surprise.h>
robot atb = robot();

void setup()
{
    //Start Serial
    Serial.begin(230400, SERIAL_8E1);
    atb.init();
    delay(500);
  

    //========================== FIRST EWOK ==========================
    //atb.first_ewok_pick_up();
    //========================== SECOND EWOK ==========================
    //atb.second_ewok_pick_up();
    //========================== IR BEACON ARCHWAY WAIT ==========================
    //atb.archway_crossing();
    //========================== LINE FOLLOW TO THIRD EWOK ==========================
    //atb.third_ewok_pick_up();
    //========================== SECOND GAP CROSSING ==========================

    //========================== FOURTH EWOK ==========================
    //========================== CHEWBACCA ==========================
    //========================== ZIPLINE ==========================
    atb.sweep_for_zipline(RIGHT);
    //atb.turn_degrees(90);
}

void loop()
{
    atb.delay_update(100);
    atb.sensor_inverse_mean();
//atb.move_meters(-1);
//atb.sensor_min_distance();
//atb.sensor_mean();
}