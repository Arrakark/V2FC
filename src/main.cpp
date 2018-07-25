#include <robot.h>

robot atb = robot();

void setup(void)
{
    Serial.begin(230400, SERIAL_8E1);
    atb.init();
    ARMCONTROL::armSearch();
    ARMCONTROL::grabberOpen();
    delay(1000);
    //atb.drive_until_black_line();
    //atb.calibrate_degrees_per_second(5);
    //atb.calibrate_meters_per_second(5);
    //atb.move_meters(2);
    //delay(1000);
    atb.follow_right_edge_until_ewok();
    //atb.turn_degrees(180);
    //delay(1000);
    //atb.move_meters(2);
    //atb.drive_until_cliff();
}

void loop(void)
{
    atb.front_sensor->update();
    for (int i = 0; i < 8; i++)
    {
        Serial.print(atb.front_sensor->distance_readings[i]);
        Serial.print(" ");
    }
    Serial.print("   ");
    Serial.print(atb.front_sensor->inverse_weighted_mean());
    Serial.println();
    delay(500);
}
