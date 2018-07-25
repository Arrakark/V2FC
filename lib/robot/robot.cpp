#include "robot.h"

//detect ewoks
int lookup_table_1[20][9] = {{1, 131, 125, 134, 132, 129, 133, 135, 140},
                             {3, 140, 134, 145, 143, 140, 143, 149, 150},
                             {5, 150, 145, 155, 151, 147, 152, 157, 159},
                             {7, 160, 156, 163, 159, 156, 160, 165, 168},
                             {10, 174, 169, 176, 170, 166, 171, 176, 179},
                             {12, 182, 177, 183, 176, 172, 177, 184, 187},
                             {15, 196, 188, 196, 188, 182, 188, 195, 198},
                             {17, 207, 195, 205, 196, 189, 195, 204, 206},
                             {20, 227, 207, 222, 210, 200, 206, 218, 219},
                             {23, 373, 229, 277, 243, 220, 225, 255, 251},
                             {25, 417, 237, 337, 268, 229, 235, 281, 267},
                             {28, 629, 305, 613, 527, 291, 301, 551, 489},
                             {30, 768, 429, 764, 703, 445, 459, 745, 685},
                             {33, 856, 540, 900, 860, 601, 617, 883, 818},
                             {36, 960, 659, 1038, 1014, 757, 779, 1038, 971},
                             {39, 1029, 736, 1131, 1122, 866, 891, 1142, 1077},
                             {42, 1081, 785, 1198, 1202, 947, 976, 1223, 1155},
                             {44, 1097, 809, 1227, 1236, 981, 1015, 1255, 1188},
                             {46, 1092, 810, 1233, 1247, 991, 1026, 1258, 1192},
                             {50, 1156, 889, 1314, 1337, 1081, 1123, 1351, 1291}};

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
    left_motor = new HBRIDGE(PA1, PB0);
    right_motor = new HBRIDGE(PA3, PA7);
    bottom_sensor = new irsensor(0x49, lookup_table_2);
    front_sensor = new irsensor(0x48, lookup_table_1);
    left_sensor = new irsensor(0x4A, lookup_table_3);
    right_sensor = new irsensor(0x4B, lookup_table_4);
    lift = new SLIFT(PA8);
    line_follower = new linefollower(left_motor, right_motor, bottom_sensor);
}

void robot::init()
{
    left_motor->init();
    right_motor->init();
    Wire.begin();
    ARMCONTROL::init(ARM_SERVO, GRABBER_SERVO, GRABBER_SWITCH, ARM_POT);
    ARMCONTROL::armSearch();
    ARMCONTROL::grabberOpen();
    delay(500);
}

//Does as name implies, drives forward until a cliff is detected
void robot::drive_until_cliff()
{
    bottom_sensor->update();
    while (bottom_sensor->mean() < FULL_CLIFF_DISTANCE)
    {
        left_motor->run(NORMAL_SPEED);
        right_motor->run(NORMAL_SPEED);
        bottom_sensor->update();
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

/*
 *  Turns the specified number of degrees
 *  left is negative degrees, right is positive degrees
 */
void robot::turn_degrees(float degrees)
{
    if (degrees > 0)
    {
        //turn right
        left_motor->run(TURN_SPEED);
        right_motor->run(-TURN_SPEED);
    }
    else
    {
        //turn left
        left_motor->run(-TURN_SPEED);
        right_motor->run(TURN_SPEED);
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
        left_motor->run(-NORMAL_SPEED);
        right_motor->run(-NORMAL_SPEED);
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
void robot::move_toward_ewok()
{
    front_sensor->update();
    while (front_sensor->min_distance() > CLOSEST_DISTANCE_TO_EWOK)
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
    delay(seconds * 1000);
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
    delay(seconds * 1000);
    left_motor->stop();
    right_motor->stop();
}

/*
 *  Follows the right edge using the right edge sensor until a minimum value is reached on the front sensor
 * 
 *  Used for getting and grabbing the first ewok
 */
void robot::follow_right_edge_until_ewok()
{
    pid edge_follower = pid();
    edge_follower.p_gain = 20;
    edge_follower.p_limit = 50;
    
    do
    {
        front_sensor->update();
        right_sensor->update();
        float error = right_sensor->inverse_weighted_mean() - 5.3;
        float control = edge_follower.output(error);
        right_motor->run(EWOK_SPEED + (int)control);
        left_motor->run(EWOK_SPEED - (int)control);
        delay(20);
    } while (front_sensor->min_distance() > CLOSEST_DISTANCE_TO_EWOK);

    left_motor->stop();
    right_motor->stop();
}