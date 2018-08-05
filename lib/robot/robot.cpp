#include "robot.h"

//detect ewoks
int lookup_table_5[20][9] = {{1, 137, 127, 124, 128, 131, 131, 138, 145}, {3, 144, 135, 133, 136, 140, 137, 147, 153}, {5, 157, 145, 145, 144, 149, 147, 154, 164}, {7, 169, 154, 153, 152, 156, 154, 161, 172}, {10, 196, 171, 167, 165, 169, 167, 176, 187}, {12, 244, 182, 176, 173, 178, 177, 186, 200}, {15, 875, 204, 192, 189, 195, 194, 207, 238}, {17, 1227, 236, 210, 204, 216, 212, 236, 455}, {20, 1568, 495, 271, 243, 319, 280, 507, 864}, {23, 1745, 746, 541, 473, 676, 629, 849, 1138}, {25, 1866, 906, 732, 689, 895, 855, 1051, 1304}, {28, 2013, 1102, 967, 953, 1162, 1132, 1310, 1525}, {30, 2126, 1239, 1129, 1129, 1340, 1313, 1482, 1677}, {33, 2248, 1392, 1307, 1325, 1536, 1512, 1678, 1850}, {36, 2329, 1496, 1436, 1467, 1678, 1660, 1816, 1972}, {39, 2426, 1607, 1558, 1598, 1806, 1790, 1942, 2084}, {42, 2473, 1670, 1637, 1685, 1894, 1882, 2036, 2172}, {44, 2520, 1724, 1700, 1752, 1961, 1951, 2102, 2233}, {46, 2559, 1771, 1752, 1809, 2019, 2011, 2162, 2291}, {50, 2616, 1843, 1834, 1898, 2107, 2100, 2254, 2378}};

//line following
int lookup_table_2[20][9] = {{1, 125, 121, 128, 125, 124, 131, 134, 148},
                             {3, 132, 128, 143, 134, 132, 140, 142, 157},
                             {5, 145, 140, 151, 144, 142, 151, 153, 171},
                             {7, 155, 149, 158, 152, 150, 159, 163, 185},
                             {10, 170, 164, 171, 165, 162, 173, 180, 231},
                             {12, 181, 175, 182, 174, 170, 183, 193, 586},
                             {15, 202, 194, 207, 191, 183, 201, 227, 1272},
                             {17, 232, 212, 252, 207, 194, 221, 369, 1615},
                             {20, 493, 350, 733, 326, 220, 436, 902, 1966},
                             {23, 772, 671, 1107, 739, 318, 826, 1240, 2171},
                             {25, 932, 856, 1321, 985, 549, 1058, 1436, 2284},
                             {28, 1102, 1047, 1546, 1245, 808, 1310, 1645, 2406},
                             {30, 1254, 1208, 1725, 1440, 1006, 1500, 1806, 2515},
                             {33, 1311, 1269, 1809, 1538, 1105, 1595, 1878, 2545},
                             {36, 1422, 1387, 1944, 1689, 1261, 1743, 2001, 2622},
                             {39, 1433, 1403, 1974, 1724, 1300, 1778, 2023, 2625},
                             {42, 1572, 1548, 2130, 1895, 1473, 1947, 2166, 2727},
                             {44, 1614, 1587, 2171, 1939, 1521, 1990, 2203, 2750},
                             {46, 1658, 1630, 2223, 1992, 1579, 2045, 2245, 2775},
                             {50, 1660, 1640, 2240, 1999, 1590, 2055, 2255, 2780}};

//sense left edge
int lookup_table_3[20][9] = {{1, 139, 136, 144, 132, 133, 134, 138, 145},
                             {3, 145, 144, 152, 140, 140, 141, 145, 151},
                             {5, 156, 154, 161, 150, 149, 152, 155, 161},
                             {7, 166, 163, 172, 158, 158, 161, 165, 172},
                             {10, 185, 177, 189, 170, 170, 174, 180, 187},
                             {12, 200, 188, 206, 179, 179, 184, 192, 199},
                             {15, 238, 204, 253, 190, 191, 198, 211, 218},
                             {17, 462, 225, 604, 203, 203, 213, 239, 248},
                             {20, 842, 369, 11085, 231, 231, 255, 476, 481},
                             {23, 1106, 662, 1416, 364, 358, 510, 804, 757},
                             {25, 1217, 792, 1563, 537, 531, 679, 950, 880},
                             {28, 1399, 992, 1767, 786, 784, 923, 1165, 1070},
                             {30, 1487, 1095, 1871, 925, 927, 1062, 1289, 1179},
                             {33, 1569, 1189, 1973, 1059, 1064, 1192, 1398, 1273},
                             {36, 1720, 1344, 2102, 1224, 1229, 1351, 1549, 1414},
                             {39, 1786, 1417, 2175, 1323, 1329, 1448, 1638, 1496},
                             {42, 1870, 1504, 2253, 1424, 1429, 1548, 1730, 1584},
                             {44, 1968, 1603, 2337, 1528, 1537, 1648, 1827, 1679},
                             {46, 2080, 1715, 2434, 1651, 1661, 1770, 1947, 1795},
                             {50, 2200, 1839, 2531, 1779, 1788, 1893, 2068, 1917}};

//sense right edge
int lookup_table_4[20][9] = {{1, 137, 126, 124, 120, 126, 124, 136, 136},
                             {3, 152, 138, 137, 131, 140, 135, 151, 146},
                             {5, 169, 148, 148, 142, 151, 146, 161, 161},
                             {7, 184, 158, 155, 150, 159, 154, 171, 171},
                             {10, 243, 177, 169, 161, 172, 167, 192, 188},
                             {12, 702, 195, 180, 170, 182, 177, 217, 203},
                             {15, 1259, 273, 200, 184, 199, 193, 595, 254},
                             {17, 1612, 728, 241, 199, 223, 212, 1091, 605},
                             {20, 1878, 1139, 627, 231, 424, 312, 1525, 1005},
                             {23, 2099, 1447, 1017, 449, 800, 690, 1829, 1306},
                             {25, 2182, 1587, 1214, 668, 1002, 909, 1992, 1466},
                             {28, 2354, 1818, 1505, 985, 1287, 1213, 2225, 1711},
                             {30, 2442, 1944, 1673, 1167, 1452, 1392, 2355, 1849},
                             {33, 2504, 2039, 1803, 1312, 1586, 1538, 2461, 1967},
                             {36, 2611, 2173, 1969, 1490, 1747, 1712, 2594, 2121},
                             {39, 2694, 2283, 2107, 1638, 1880, 1856, 2704, 2254},
                             {42, 2752, 2358, 2205, 1746, 1979, 1965, 2786, 2354},
                             {44, 2792, 2379, 2234, 1778, 2007, 1996, 2801, 2373},
                             {46, 2761, 2384, 2246, 1794, 2002, 2016, 2816, 2393},
                             {50, 2805, 2440, 2320, 1874, 2096, 2098, 2877, 2469}};

robot::robot()
{
    //elbow servo is servo 1, grabber servo is servo 2
    //limit switch is the first limit switch
    right_claw = new SCLAW(SUPPORT_SERVO,PINCER_SERVO,GRABBER_SWITCH);
    left_motor = new HBRIDGE(PB0, PA1);
    right_motor = new HBRIDGE(PA3, PA7);
    bottom_sensor = new irsensor(0x49, lookup_table_2);
    front_sensor = new irsensor(0x48, lookup_table_5);
    left_sensor = new irsensor(0x4A, lookup_table_3);
    right_sensor = new irsensor(0x4B, lookup_table_4);
    // lift = new SLIFT(PA8); //init later when needed <- avoid timer conflicts
    line_follower = new linefollower(left_motor, right_motor, bottom_sensor);
}

void robot::init()
{
    right_claw->init();
    left_motor->init();
    right_motor->init();
    right_claw->init();
    Wire.begin();
    pinMode(PC13, OUTPUT);
    robot::check_sensors();
    robot::delay_update(500);
}

void robot::check_sensors()
{

    digitalWrite(PC13, HIGH);

    byte error, address;
    int nDevices;

    nDevices = 0;
    for (address = 72; address < 76; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            //Serial.print("I2C device found at address 0x");
            //if (address < 16)
            //Serial.print("0");
            //Serial.print(address, HEX);
            // Serial.println("  !");
            nDevices++;
        }
    }
    if (nDevices != 4)
    {
        digitalWrite(PC13, HIGH);
    }
    else
    {
        digitalWrite(PC13, LOW);
    }
}

//Does as name implies, drives forward until a cliff is detected
void robot::drive_until_cliff()
{
    bottom_sensor->update();
    while (bottom_sensor->mean() < 11)
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
        bottom_sensor->update();
        Serial.println(bottom_sensor->mean());
        robot::delay_update(10);
    }
    left_motor->stop();
    right_motor->stop();
}

//Does as name implies, drives forward until a cliff is detected
void robot::drive_until_cliff_early()
{
    left_sensor->update();
    right_sensor->update();
    while (left_sensor->mean() < 30 && right_sensor->mean() < 30)
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
        left_sensor->update();
        right_sensor->update();
        robot::delay_update(10);
    }
    left_motor->stop();
    right_motor->stop();
}

//Does as name implies, drives forward until a line is detected
void robot::drive_until_black_line()
{
    bottom_sensor->update();
    while (bottom_sensor->max_distance() < LINE_DISTANCE)
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
        bottom_sensor->update();
    }
    left_motor->stop();
    right_motor->stop();
}
/**
 * Follows the line untill BOTH beacon sensors
 * detect a signal. A signal is defined as IR
 * light that is either 1kHz or 10 kHz. Random
 * IR noise will not be considered a signal
 */
void robot::line_follow_until_beacon()
{
    while (IRBEACON::read(PA5) == NO_BEACON || IRBEACON::read(PA0) == NO_BEACON)
    {
        line_follower->follow_line();
        delay_update(20);
    }
    move_meters(-0.01);
}

/*
 * Hardcoded turns. Use compass function: compass_turn_degrees
 * for more accuracy. 
 * 
 * Turns the specified number of degrees
 * left is negative degrees, right is positive degrees
 *  
 */
// void robot::compass_turn_degrees(float degrees){

// }

void robot::turn_degrees(float degrees)
{
    if (degrees < 0)
    {
        //physically turns left
        left_motor->run(TURN_SPEED);
        right_motor->run(-TURN_SPEED);
    }
    else
    {
        //physically turns right
        left_motor->run(-TURN_SPEED);
        right_motor->run(TURN_SPEED);
    }
    delay_update((abs(degrees) / DEGREES_PER_SECOND) * 1000);
    left_motor->stop();
    right_motor->stop();
}

void robot::delay_update(long ms)
{
    unsigned long starttime = millis();
    while (millis() < starttime + ms)
    {
        //ARMCONTROL::update();
        robot::check_sensors();
        delay(5);
    }
}

/*
 *  Moves the specified number of meters
 *  positive is forward, negative is backwards
 *  Used to test how far we have to go to get up the second platform
 */
void robot::ram_meters(float meters)
{
    if (meters > 0)
    {
        left_motor->run(255);
        right_motor->run(255);
    }
    else
    {
        left_motor->run(-255);
        right_motor->run(-255);
    }
    delay_update(((float)abs(meters) / METERS_PER_SECOND) * 1000);
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
        left_motor->run(-NORMAL_SPEED);
        right_motor->run(-NORMAL_SPEED);
    }
    delay_update(((float)abs(meters) / METERS_PER_SECOND) * 1000);
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
    unsigned long scan_duration = (abs(angle) / DEGREES_PER_SECOND) * 1000;

    while (millis() < start_time + scan_duration)
    {
        if (angle > 0)
        {
            left_motor->run(TURN_SPEED);
            right_motor->run(-TURN_SPEED);
        }
        else
        {
            left_motor->run(-TURN_SPEED);
            right_motor->run(TURN_SPEED);
        }
        front_sensor->update();
        if (front_sensor->mean() < EWOK_LONG_DISTANCE_DETECTION)
        {
            break;
        }
        Serial.println(front_sensor->min_distance());
    }
    left_motor->stop();
    right_motor->stop();
}

/*
 *  Move toward ewok until it is within grabbing range
 */
void robot::move_toward_ewok(double distance_to_ewok)
{
    front_sensor->update();
    //while (front_sensor->min_distance() > CLOSEST_DISTANCE_TO_EWOK)
    while (front_sensor->min_distance() > distance_to_ewok)
    {
        left_motor->run(EWOK_SPEED);
        right_motor->run(EWOK_SPEED);
        front_sensor->update();
    }
    left_motor->stop();
    right_motor->stop();
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
    delay_update(seconds * 1000);
    left_motor->stop();
    right_motor->stop();
}

/*
 *  Turn right for specified number of seconds
 *  Used to calibrate constant DEGREES_PER_SECOND
 *  Count how many degrees the robot has moved, then divide by seconds and set that as constant
 *  The more seconds you turn the more accurate the calibration
 */
void robot::calibrate_degrees_per_second(int seconds)
{
    left_motor->run(TURN_SPEED);
    right_motor->run(-TURN_SPEED);
    delay_update(seconds * 1000);
    left_motor->stop();
    right_motor->stop();
}

void robot::grab_ewok()
{
    ARMCONTROL::armPickup();
    robot::delay_update(500);
    ARMCONTROL::grabberTightHug();
    robot::delay_update(1000);
    ARMCONTROL::armDropoff();
    robot::delay_update(2000);
    ARMCONTROL::grabberOpen();
    robot::delay_update(1000);
    ARMCONTROL::armSearch();
}

/*
 *  Follows the right edge using the right edge sensor until a minimum value is reached on the front sensor
 * 
 *  Used for getting and grabbing the first ewok
 */
void robot::follow_right_edge_until_ewok()
{
    pid edge_follower = pid();
    edge_follower.p_gain = 85;
    edge_follower.p_limit = 100;
    do
    {
        front_sensor->update();
        right_sensor->update();
        float error = right_sensor->inverse_weighted_mean() - 5.3;
        float control = edge_follower.output(error);
        right_motor->run(130 + (int)control);
        left_motor->run(130 - (int)control);
    } while (front_sensor->min_distance() > CLOSEST_DISTANCE_TO_EWOK);
    left_motor->stop();
    right_motor->stop();
    move_meters(-0.05);
}

/*
Follows black line for a certain amount of meters
*/

void robot::line_follow_meters(float meters)
{
}

void robot::line_follow_until_right_ewok()
{
    float min_value = 30.0;
    while (1)
    {
        right_sensor->update();
        bottom_sensor->update();
        line_follower->follow_line();
        robot::delay_update(4);
        Serial.println(bottom_sensor->mean());
        if (bottom_sensor->mean() < min_value)
        {
            min_value = bottom_sensor->mean();
        }
        //needs to be between 1.3 and 1.5
        if (bottom_sensor->mean() > 1.382465057179161 * min_value)
        {
            break;
        }
    }
    move_meters(-0.01);
    //robot::delay_update(((float)abs(meters) / METERS_PER_SECOND) * 1000);
}

void robot::sensor_info()
{
    left_sensor->info();
    front_sensor->info();
    right_sensor->info();
    Serial.println();
}

/**
 * Moves robot in a specified direction until it senses the black tape.
 * Param: turn direction. num > 0 means turn right, num < 0 means turn left
 **/
void robot::turn_until_black_line(int turn_dir)
{
    if (turn_dir > 0)
    {
        do
        {
            bottom_sensor->update();
            left_motor->run(TURN_SPEED);
            right_motor->run(-TURN_SPEED);
            // } while (bottom_sensor->max_distance() < LINE_DISTANCE);
            // } while (bottom_sensor->max_distance() < 12);
        } while (bottom_sensor->max_distance() < 15); //the 7th ir_sensor tends to shoot up to high values very quickly
    }

    else
    {
        do
        {
            bottom_sensor->update();
            left_motor->run(-TURN_SPEED);
            right_motor->run(TURN_SPEED);
            // } while (bottom_sensor->max_distance() < 12);
        } while (bottom_sensor->max_distance() < 15); //the 7th ir_sensor tends to shoot up to high values very quickly
    }

    left_motor->run(0);
    right_motor->run(0);
}

void robot::line_follow_until_second_ewok()
{
    do
    {
        right_sensor->update();
        line_follower->pid_controller.p_gain = 500.0;
        line_follower->pid_controller.p_limit = 150.0;
        line_follower->pid_controller.d_gain = 2.0;
        line_follower->pid_controller.d_limit = 100.0;
        line_follower->follow_line();
        delay_update(4);
    } while (right_sensor->min_distance() > 9);

    move_meters(-0.05);
}

void robot::wait_for_10khz()
{
    //wait for 10khz to pass
    while (IRBEACON::read(PA5) == TEN_KHZ || IRBEACON::read(PA0) == TEN_KHZ)
    {
        delay_update(20);
    }
    delay_update(20);
    //wait for 1khz to pass
    while (IRBEACON::read(PA5) != TEN_KHZ || IRBEACON::read(PA0) != TEN_KHZ)
    {
        delay_update(20);
    }
}
/**
 * This is the edge in front of the IR beacon 
 **/
void robot::find_second_edge()
{
    unsigned long start_time = millis();
    line_follower->pid_controller.p_gain = 600.0;
    line_follower->pid_controller.p_limit = 250;
    line_follower->cross_gap = false;
    line_follower->default_speed = 120;
    do
    {
        bottom_sensor->update();
        Serial.println(bottom_sensor->mean());
        bottom_sensor->update();
        line_follower->follow_line();
        delay_update(4);
    } while (bottom_sensor->min_distance() < CLIFF_DISTANCE);
    move_meters(-0.05);
}

void robot::find_gap_one()
{
    // unsigned long start_time = millis();
    line_follower->cross_gap = false;
    do
    {
        bottom_sensor->update();
        line_follower->pid_controller.p_gain = 600.0;
        // line_follower->pid_controller.p_gain = 800.0;
        line_follower->pid_controller.p_limit = 250;
        // line_follower->pid_controller.d_gain = 2.0;
        // line_follower->pid_controller.d_limit = 100.0;
        // line_follower->default_speed = 70.0;
        line_follower->default_speed = 90.0; //goal: not knock over second ewok
        line_follower->follow_line();
        delay_update(4);
        // } while (bottom_sensor->min_distance() < 4);
    } while (bottom_sensor->mean() < 15);
    move_meters(-0.05);
}
/*
 *  Line follow until the second ewok for a minimum of milliseconds specified.
 *  This should help avoid noise from the IR beacon!
 */
void robot::line_follow_until_second_ewok_2(float milliseconds)
{
    unsigned long start_time = millis();
    do
    {
        right_sensor->update();
        line_follower->pid_controller.p_gain = 600.0;
        line_follower->pid_controller.p_limit = 250;
        line_follower->pid_controller.d_gain = 2.0;
        line_follower->pid_controller.d_limit = 100.0;
        line_follower->default_speed = 100.0;
        // line_follower->default_speed = 100.0;
        // line_follower->pid_controller.p_gain = 500.0;
        // line_follower->pid_controller.p_limit = 150.0;
        // line_follower->pid_controller.d_gain = 2.0;
        // line_follower->pid_controller.d_limit = 100.0;
        line_follower->follow_line();
        delay_update(4);
    } while (right_sensor->min_distance() > 12 || millis() < start_time + milliseconds);

    move_meters(-0.05);
}

void robot::sweep_for_zipline(int turn_dir)
{

    ARMCONTROL::arm80();
    delay_update(1000);
    //if sees ewok in the left before and it swept left, sweep robot to right
    if (turn_dir > 0)
    {
        //while (!(atb.front_sensor->distance_readings[0] < EWOK_LONG_DISTANCE_DETECTION))
        do
        {
            front_sensor->update();
            left_motor->run(FAST_TURN_SPEED);
            delay_update(20);
            right_motor->run(-FAST_TURN_SPEED);
        } while (front_sensor->min_distance() > 35);
    }

    //if sees ewok in the right before and it swept right, sweep robot to left
    else
    {
        do
        {
            front_sensor->update();
            left_motor->run(-FAST_TURN_SPEED);
            right_motor->run(FAST_TURN_SPEED);
            delay_update(20);
        } while (front_sensor->min_distance() > 35);
    }

    left_motor->run(0);
    right_motor->run(0);
}

void robot::sweep_ewok(int turn_dir)
{
    //if sees ewok in the left before and it swept left, sweep robot to right
    if (turn_dir > 0)
    {
        //while (!(atb.front_sensor->distance_readings[0] < EWOK_LONG_DISTANCE_DETECTION))
        do
        {
            front_sensor->update();
            left_motor->run(SWEEP_SPEED);
            delay_update(20);
            right_motor->run(-SWEEP_SPEED);
        } while (front_sensor->min_distance() > 42);
    }

    //if sees ewok in the right before and it swept right, sweep robot to left
    else
    {
        do
        {
            front_sensor->update();
            left_motor->run(-SWEEP_SPEED);
            right_motor->run(SWEEP_SPEED);
            delay_update(20);
        } while (front_sensor->min_distance() > 42);
    }

    left_motor->run(0);
    right_motor->run(0);
}

/*
    Let the robot sense the stormtropper (assuming its platform won't rotate) and ewok
    Stop robot once it senses the ewok
*/

void robot::line_follow_until_third_ewok()
{
    int flag = 0;
    while (flag != 2)
    {
        left_sensor->update();
        line_follower->follow_line();
        robot::delay_update(4);

        if (left_sensor->min_distance() < CLOSEST_DISTANCE_TO_EWOK)
        {
            flag++;
        }
    }
    move_meters(-0.01);
    //robot::delay_update(((float)abs(meters) / METERS_PER_SECOND) * 1000);
}

/**
 * Begin when the bottom sensor is touching the line. Line-follow up to the first ewok
 * and grab it.
 * */
void robot::first_ewok_pick_up()
{
<<<<<<< HEAD
    // while(1) {
    // robot::delay_update(2000);
    // right_claw->pickup();
    // robot::delay_update(2000);
    // right_claw->open();
    // robot::delay_update(2000);
    // right_claw->hug();
    // robot::delay_update(2000);
    // right_claw->dropoff();
    // robot::delay_update(2000);
    // right_claw->open();
    // robot::delay_update(2000);
    // right_claw->hug();

    // }
    float min_value = 30.0;
    while (1)
    {
        right_sensor->update();
        bottom_sensor->update();
        line_follower->follow_line();
        robot::delay_update(4);
        if (right_claw->checkSwitch()) break;
        if (bottom_sensor->mean() < min_value)
        {
            min_value = bottom_sensor->mean();
        }

    }
    move_meters(-0.01);
    right_claw->grabEwok();

=======
    line_follow_until_right_ewok();
    while(1){
    line_follower->default_speed = 110;
    line_follower->follow_line();
        robot::delay_update(4);
        if (right_grab_ewok()) {
            break;
        }
    }
    // move_meters(-0.01);
>>>>>>> 07a39864d1540f38cdcdd67f24b2c049d2cdd2e3
}

//wall following attempt to get to third ewok. We are no longer using this function
void robot::forward_until_wall()
{
    ARMCONTROL::armPickup();
    ARMCONTROL::grabberHug();
    do
    {
        left_sensor->update();
        right_motor->run(90);
        left_motor->run(90);
        delay_update(20);
    } while (left_sensor->min_distance() > 41);

    right_motor->run(0);
    left_motor->run(0);
}

void robot::follow_left_wall_until_ewok()
{
    ARMCONTROL::armPickup();
    ARMCONTROL::grabberHug();
    pid edge_follower = pid();
    edge_follower.p_gain = 300;
    edge_follower.p_limit = 100;
    do
    {
        front_sensor->update();
        left_sensor->update();
        float error = left_sensor->inverse_weighted_mean() - 3.8;
        float control = edge_follower.output(error);
        right_motor->run(90 - (int)control);
        left_motor->run(90 + (int)control);
        delay_update(20);
    } while (front_sensor->min_distance() > 12);
    left_motor->stop();
    right_motor->stop();
    move_meters(-0.05);
}

/**
 *Begin at the position where first ewok was picked up. Turn left until it finds the black line again.
 **/
void robot::second_ewok_pick_up()
{

    //This will find the gap and back up
    find_gap_one();
    robot::delay_update(500);
    // robot::delay_update(500);
    move_meters(-0.15);
    robot::delay_update(500);
    turn_until_black_line(LEFT); //sweep back to black line after grabbing ewok
    robot::delay_update(500);
    //realign with the gap again
    find_gap_one();
    robot::delay_update(500);
    //robot::delay_update(500);
    move_meters(-0.15);
    robot::delay_update(500);
    robot::delay_update(500);
    //cross the gap
    move_meters(0.7);
    //follow-line until ewok
    while(1){
    line_follower->follow_line();
        robot::delay_update(4);
        if (right_grab_ewok()) {
            break;
        }
    }

}

/**
 * After picking up the second ewok, back up and realign with black tape. Close the grabber and
 * bring it to vertical position. Wait for any stale 10 kHz signal and 1kHz signal to pass. As soon as it 
 * detects a fresh 10 Khz signal, we can proceed to line follow to the 3rd ewok.
 */

void robot::archway_crossing()
{
    //outside competition surface:
    //red light = 10 kHz
    //no light = 1kHz
    //inside competition is reversed
    move_meters(-0.1);
    delay_update(500);
    turn_until_black_line(LEFT);
    robot::delay_update(500);
    //move arm out of the way
    ARMCONTROL::grabberHug();
    ARMCONTROL::armVertical();
    robot::delay_update(1000);
    line_follow_until_beacon();
    wait_for_10khz();
}
void robot::third_ewok_pick_up()
{
    ARMCONTROL::armVertical();
    turn_table_detect(TWICE);
    robot::delay_update(1000);
    ARMCONTROL::armSearch();
    ARMCONTROL::grabberOpen();
    robot::delay_update(2000);
    move_meters(0.45);
    robot::delay_update(2000);
    //CALIBRATION VALUE 15
    turn_degrees(18);
    robot::delay_update(2000);
    move_toward_ewok(THIRD_EWOK_DISTANCE); //too fast
    move_meters(0.01);
    ARMCONTROL::armPickup();
    robot::delay_update(500);
    ARMCONTROL::grabberTightHug();
    robot::delay_update(1000);
    ARMCONTROL::armHorizontal();
    // atb.turn_degrees(15);
    turn_degrees(5);
    //CALIBRATION: 0.37
    move_meters(0.40);
    robot::delay_update(2000);
    //CALIBRATION: -50
    turn_degrees(-46);
    ARMCONTROL::armHorizontal();
    move_meters(0.25);
    robot::delay_update(2000);
    ARMCONTROL::grabberOpen();
    // atb.follow_left_wall_until_ewok();
    // atb.find_second_edge();
}

/**
 * Line-follow to the edge in front of second IR beacon. Back up to find the third ewok.
 */
void robot::third_ewok_pick_up_old()
{
    //ARMCONTROL::armVertical();
    //robot::delay_update(500);
    find_second_edge();
    ARMCONTROL::grabberOpen();
    ARMCONTROL::armPickup();
    move_meters(-0.48);
    //move_meters(-0.45);
    delay_update(500);
    sweep_ewok(LEFT);

    robot::delay_update(500);
    move_toward_ewok(THIRD_EWOK_DISTANCE);
    //move_meters(0.05);
    robot::delay_update(500);

    ARMCONTROL::armPickup();
    robot::delay_update(500);
    ARMCONTROL::grabberTightHug();
    robot::delay_update(1000);
    ARMCONTROL::armHorizontal();

    turn_degrees(15);

    // turn_degrees(-40);
    move_meters(0.35);
    turn_degrees(-35);
    move_meters(0.1);

    ARMCONTROL::grabberOpen();
}

/**
 * Tries to follow the zipline however it is limited by the sensor's 30 cm range.
 */

void robot::zipline_follow()
{
    pid zipline_follower = pid();
    zipline_follower.p_gain = 300;
    zipline_follower.p_limit = 300;
    do
    {
        front_sensor->update();
        bottom_sensor->update();
        float error = front_sensor->inverse_weighted_mean() - 4.5;
        float control = zipline_follower.output(error);
        right_motor->run(90 + (int)control);
        left_motor->run(90 - (int)control);
    } while (bottom_sensor->min_distance() < 12);
    left_motor->stop();
    right_motor->stop();
    move_meters(-0.05);
}

/**
 * CONTINUE writing this function.
 * Align to get onto second gap. Needs a function to ensure
 * it has moved past straight edge AND elevated platform edge.
 * */
void robot::second_gap_crossing()
{
    robot::delay_update(1000);
    move_meters(-0.1);
    ARMCONTROL::armSearch();
    // turn_degrees(88);
    turn_degrees(44); //turns to the right
    do
    {
        left_sensor->update();
        turn_degrees(1);
        //keep turning while left sensor is off the edge
    } while (left_sensor->mean() > 30);
    turn_degrees(4);
    robot::delay_update(1000);
    ARMCONTROL::armHorizontal();
    move_meters(0.4);
    drive_until_cliff();
    second_gap_auto();
    ARMCONTROL::armPickup();
    robot::delay_update(200);
    move_toward_ewok(FOURTH_EWOK_DISTANCE);
    move_meters(-0.07);
    grab_ewok();
    delay_update(1000);
    ARMCONTROL::grabberTightHug();
}

void robot::second_gap_auto()
{
    do
    {
        bottom_sensor->update();
        left_motor->run(255);
        right_motor->run(255);
        delay_update(20);
    } while (bottom_sensor->mean() > 15);
    ram_meters(0.09);
}


/**
 * Navigate across turn table.
 * Param: number of gaps to recgonize. Either once or twice.
 * One gap recognition is for finding the zipline to drop off the first 3 ewoks.
 * Both gap recognition is for traversing from archway towards third ewok.
 **/
void robot::turn_table_detect(int num)
{
    line_follower->pid_controller.p_gain = 600.0;
    line_follower->pid_controller.p_limit = 250;
    line_follower->cross_gap = false;
    line_follower->default_speed = 120;
    int flag = 0;
    unsigned long time_flag = millis();
   
    do
    {
        bottom_sensor->update();
        // Serial.println(bottom_sensor->mean());
        bottom_sensor->update();
        line_follower->follow_line();
        delay_update(4);
        //
        if (bottom_sensor->mean() > TURN_TABLE_GAP && flag == 0)
        {
            flag = 1;
            time_flag = millis();
            //if we want to stop after passing one edge of turn table
            if(num == ONCE){
                break;
            }
        }
    } while (flag != 1 || millis() < time_flag + 200 || bottom_sensor->mean() < TURN_TABLE_GAP);
    move_meters(-0.05);
}

// void robot::fourth_ewok_pick_up(){

// }

/**
 * After picking up the fourth ewok, turn 90 degrees and start
 * edge following up to chewbacca. Send change in slope, start sweeping
 * for chewbacca. Grab it!!!
 * */
void robot::chewbacca_pick_up()
{
    // move_meters(-0.1)
    turn_degrees(43); //this should turn 90 degrees
    move_meters(0.2);
    delay_update(500);
    ARMCONTROL::armSearch();
    ARMCONTROL::grabberOpen();
    //
    pid bridge_crosser = pid();
    bridge_crosser.p_gain = 85;
    bridge_crosser.p_limit = 100;
    do
    {
        left_sensor->update();
        right_sensor->update();
        front_sensor->update();
        //biases the error with 30
        float error = right_sensor->mean() - left_sensor->mean() + 10;
        float control = bridge_crosser.output(error);
        right_motor->run(130 - (int)control);
        left_motor->run(130 + (int)control);
        delay_update(20);
        //this looks for Chewie!!!
    } while (front_sensor->min_distance() > CHEWIE_DISTANCE);
    left_motor->stop();
    right_motor->stop();
    ARMCONTROL::armPickup();
    delay_update(1000);
    move_meters(0.02);
    grab_ewok();
}

/**
 * Max sensor value for IR array is 30. Inverse weighted mean takes current reading and
 * subtract it from 30 and computes the weighted mean from 8 sensor values using sensor indices. 
 */
void robot::sensor_inverse_mean()
{
    robot::delay_update(20);
    left_sensor->update();
    right_sensor->update();
    front_sensor->update();
    Serial.print(left_sensor->inverse_weighted_mean());
    Serial.print(",");
    Serial.print(front_sensor->inverse_weighted_mean());
    Serial.print(",");
    Serial.println(right_sensor->inverse_weighted_mean());
}

void robot::sensor_mean()
{
    robot::delay_update(20);
    left_sensor->update();
    right_sensor->update();
    front_sensor->update();
    Serial.print(left_sensor->mean());
    Serial.print(",");
    Serial.print(front_sensor->mean());
    Serial.print(",");
    Serial.println(right_sensor->mean());
}

void robot::sensor_min()
{
    robot::delay_update(20);
    left_sensor->update();
    right_sensor->update();
    front_sensor->update();
    Serial.print(left_sensor->min_distance());
    Serial.print(",");
    Serial.print(front_sensor->min_distance());
    Serial.print(",");
    Serial.println(right_sensor->min_distance());
}

/*
    zipline mechanism for sending chewbacca and ewoks home

    release the basket by hooking basket at zipline and then 
    have the scissor lift to move downwards 

    will be used once Chewy is picked up

    Assumptions:
                 - 3 ewoks + Chewy in basket
                 - grabber is open
                 - arm is in Search position
                 - robot is facing in front of Chewy
*/

void robot::zipline_finish()
{
    int ground_value = 17; //min dist for ground is 17 in left_sensor
    int platform_value = 12; //min dist for platform in left_sensor is 11-12
    //close grabber
    ARMCONTROL::grabberHug();
    delay_update(500); //***
    //need to change arm position into Horizontal??? *******

    //adjusting basket hook on zipline

    //move robot forward until all of left sensor sees the 'ground'
    do
    {
        left_sensor->update();
        left_motor->run(80);
        right_motor->run(80);
    } while(left_sensor->min_distance() < ground_value - 1); //**

    //rotate to the right until all of left sensor sees the 'platform'
    do
    {
        left_sensor->update();
        //'opposite signs' from motors
        left_motor->run(-80);
        right_motor->run(80);
    } while(left_sensor->min_distance() > platform_value  + 1); //***

    //move robot forward until all of left sensor sees the 'ground'
    do
    {
        left_sensor->update();
        left_motor->run(80);
        right_motor->run(80);
    } while(left_sensor->min_distance() < ground_value - 1); //**

    //rotate motor to the right until all or most of the left_sensor sees 'platform' ********
    do
    {
        left_sensor->update();
        //'opposite signs' from motors
        left_motor->run(-80);
        right_motor->run(80);
    } while(left_sensor->distance_readings[5] > platform_value + 1);
    // } while(left_sensor->min_distance() < platform_value); //***

    
//     //hooking basket onto zipline

//     //initialize scissor lift object
//     lift = new SLIFT(PA8);
//     lift->init();

//     //lift scisoor lift 
//     lift->moveUp();

    /* 
        to hook the basket onto zipline, move robot forward until both 
        left and right sensors all see 'ground' and that the bottom sensor 
        just sees 'ground' ***************
    */
   do
   {
       left_sensor->update();
       right_sensor->update();
       bottom_sensor->update();
       left_motor->run(80);
       right_motor->run(80);
   } while(left_sensor->min_distance() < ground_value - 1 && right_sensor->min_distance() < ground_value - 1 && bottom_sensor->min_distance() < CLIFF_DISTANCE);

//    //move scissor lift downwards
//    lift->moveDown();
   //disconnect lift servo
   lift->disconnect();
}


/*
    Backup plan for just bringing three ewoks back home with the basket

    Precondition:
                 - 3 ewoks in basket
                 - robot facing in front of the third ewok
                 - grabber is open
                 - arm is in Search position
*/
void robot::zipline_for_three_ewoks()
{
    //rotate robot to the right for about 135 degrees (before it touches a black line)
    turn_degrees(135); //positive degrees is right

    //rotate robot to the right until it sees black line/tape
    turn_until_black_line(RIGHT);

    //line follow until it sees the gap of the rotary platform
    turn_table_detect(ONCE);

    //rotate robot to the right for about 45 degrees (will need to adjust)
    turn_degrees(45);

    //intialize scissor lift mechanism
    lift = new SLIFT(PA8);
    lift->init();

    //lift up the scissor lift
    lift->moveUp();

    //move robot straight until all of (or most of) right sensor sees 'CLIFF'
    do
    {
        left_motor->run(80);
        right_motor->run(80);
    } while(right_sensor->distance_readings[1] < CLIFF_DISTANCE);

    //disconnect the scissor lift in the end
    lift->disconnect();
}

//=================================SIDE CLAWS==================================/
bool robot::right_grab_ewok() {    
    if (right_claw->checkQSD()) {
        move_meters(-0.03);
        right_claw->hug();
        robot::delay_update(500);
        right_claw->dropoff();
        robot::delay_update(1000);
        right_claw->open();
        robot::delay_update(500);
        right_claw->pickup();
        robot::delay_update(500);
    
        return true;
    }
        return false;
}