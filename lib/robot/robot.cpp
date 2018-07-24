#include "robot.h"

robot::robot()
{
    //elbow servo is servo 1, grabber servo is servo 2
    //limit switch is the first limit switch
    arm = new ARMCONTROL(PB8, PB9, PB12, PB1);
    //left motor is motor 2
    left_motor = new HBRIDGE(PB0, PA1);
    //left motor is motor 3
    right_motor = new HBRIDGE(PA7, PA3);
    //bottom_sensor = new irsensor(0x49, lookup_table_2);
    //front_sensor = new irsensor(0x48, lookup_table_1);
    //left_sensor = new irsensor(0x4A, lookup_table_3);
    //right_sensor = new irsensor(0x4B, lookup_table_4);
    lift = new SLIFT(PA8);
}

//Does as name implies, drives forward until a cliff is detected
void robot::drive_until_cliff()
{
    while (bottom_sensor->mean() < FULL_CLIFF_DISTANCE)
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
    }
    left_motor.stop();
    right_motor.stop();
}

//Does as name implies, drives forward until a line is detected
void robot::drive_until_black_line()
{
    while (bottom_sensor->min_distance() > LINE_DISTANCE)
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
    }
    left_motor.stop();
    right_motor.stop();
}

/*
 *  Turns the specified number of degrees
 *  left is negative degrees, right is positive degrees
 */
void robot::turn_degrees(float degrees)
{
    if (degrees > 0)
    {
        //turn right
        left_motor->run(NORMAL_SPEED);
        right_motor->run(-NORMAL_SPEED);
    }
    else
    {
        //turn left
        left_motor->run(-NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
    }
    delay((abs(degrees) / DEGREES_PER_SECOND) * 1000);
    left_motor->stop();
    right_motor->stop();
}

/*
 *  Moves the specified number of meters
 *  positive is forward, negative is backwards
 */
void robot::move_meters(float meters)
{
    if (meters > 0)
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
    }
    else
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
    }
    delay(((float)abs(meters) / METERS_PER_SECOND) * 1000);
    left_motor->stop();
    right_motor->stop();
}

/*
 * Turns the robot in the right or left direction for a specified angle to "scan" for the ewok
 * Then, turns back to face the ewok
 * Ewok must be within sweep distance (~15cm)
 * Parameters: Angle to sweep (degrees, negative is left, positive is right)
 */
void robot::sweep_for_ewok(float angle)
{
    unsigned long start_time = millis();
    unsigned long scan_duration = (abs(degrees) / DEGREES_PER_SECOND) * 1000;
    //scanning paramters
    int scan_number = (int)(scan_duration / EWOK_SCANNING_INTERVAL);
    float scan_distances[scan_number] = {100};
    int scan_count = 0;
    //specifies the time-boundary of the sweep
    while (scan_count < scan_number)
    {
        //turns in specified direction
        if (angle > 0)
        {

            left_motor->run(NORMAL_SPEED);
            right_motor->run(-NORMAL_SPEED);
        }
        else
        {
            left_motor->run(-NORMAL_SPEED);
            right_motor->run(NORMAL_SPEED);
        }
        scan_distances[scan_count] = front_sensor->min_distance();
        scan_count++;
        delay(EWOK_SCANNING_INTERVAL);
    }
    //got scan results, stop the motors
    left_motor->stop();
    right_motor->stop();

    //find minimum in scan array
    float min_value = 100;
    int min_position = 0;
    for (int x = 0; x < scan_number; x++)
    {
        if (scan_distances[x] < min_value)
        {
            min_value = scan_distances[x];
            min_position = x;
        }
    }

    //turn back to the ewok
    float angle_back_to_ewok = (scan_number - min_position) * EWOK_SCANNING_INTERVAL * 1000 * DEGREES_PER_SECOND;
    if (angle > 0)
    {
        //initially scanned to the right, so turn back to the left
        turn_degrees(-angle_back_to_ewok);
    }
    else
    {
        turn_degrees(angle_back_to_ewok);
    }
}

/*
 *  Move toward ewok until it is within grabbing range
 */
void robot::move_toward_ewok()
{
    while (front_sensor->min_distance() < CLOSEST_DISTANCE_TO_EWOK)
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
    }
    left_motor.stop();
    right_motor.stop();
}

/*
 *  Move forward for specified number of seconds
 *  Used to calibrate constant METERS_PER_SECOND
 *  Count how many meters robot has moved, then divide by seconds and set that as constant
 *  The more seconds you move forward the more accurate the calibration
 */
void robot::calibrate_meters_per_second(int seconds)
{
    left_motor->run(NORMAL_SPEED);
    right_motor->run(NORMAL_SPEED);
    delay(seconds * 1000);
    left_motor.stop();
    right_motor.stop();
}

/*
 *  Turn right for specified number of seconds
 *  Used to calibrate constant DEGREES_PER_SECOND
 *  Count how many degrees the robot has moved, then divide by seconds and set that as constant
 *  The more seconds you turn the more accurate the calibration
 */
void robot::calibrate_degrees_per_second(int seconds)
{
    left_motor->run(NORMAL_SPEED);
    right_motor->run(-NORMAL_SPEED);
    delay(seconds * 1000);
    left_motor.stop();
    right_motor.stop();
}

