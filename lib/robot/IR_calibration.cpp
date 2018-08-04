/**
 * Calibrate ewok distance based on ambient IR
 * */
#include <robot.h>
robot atb = robot();

void setup()
{
    //Start Serial
    Serial.begin(230400, SERIAL_8E1);
    atb.init();
    ARMCONTROL::armSearch();
}

void loop()
{
    robot::delay_update(15000);
    //======CALIBRATION=======
    Serial.println("FIRST EWOK DISTANCE:");
    robot::delay_update(5000);

    for(int i = 0; i < 50; i++){
        atb.front_sensor->update();
        Serial.println(atb.front_sensor->min_distance());
        atb.delay_update(100);
    }

    Serial.println("SECOND EWOK DISTANCE");
    robot::delay_update(20000);

    for(int i = 0; i < 50; i++){
         atb.front_sensor->update();
    Serial.println(atb.front_sensor->min_distance());
    atb.delay_update(20);
    }

    Serial.println("THIRD EWOK DISTANCE");
    
    robot::delay_update(20000);
    
        for(int i = 0; i < 50; i++){
             atb.front_sensor->update();
        Serial.println(atb.front_sensor->min_distance());
        atb.delay_update(20);
    }
    
    Serial.println("FOURTH EWOK DISTANCE");
    robot::delay_update(20000);
    for(int i = 0; i < 50; i++){
         atb.front_sensor->update();
        Serial.println(atb.front_sensor->min_distance());
        atb.delay_update(20);
    }

    Serial.println("CHEWIE DISTANCE");
    robot::delay_update(20000);
    for(int i = 0; i < 50; i++){
        atb.front_sensor->update();
        Serial.println(atb.front_sensor->min_distance());
        atb.delay_update(20);
    }
    
    Serial.println("GAP DETECTION: CLIFF_DISTANCE");
    robot::delay_update(20000);
    for(int i = 0; i < 100; i++){
         atb.bottom_sensor->update();
        Serial.println(atb.bottom_sensor->min_distance());
        atb.delay_update(20);
    }

    Serial.println("LEFT SENSOR: CLIFF BEFORE SECOND GAP");
    robot::delay_update(20000);
    for(int i = 0; i<100; i++){
         atb.left_sensor->update();
        Serial.println(atb.left_sensor->mean());
        atb.delay_update(20);
    }

    Serial.println("TURN TABLE GAP");
    robot::delay_update(20000);
    atb.find_second_edge();
    
    Serial.println("DONE");
    while(1){

    }
}