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
    left_motor = new HBRIDGE(PB0, PA1);
    right_motor = new HBRIDGE(PA3, PA7);
    bottom_sensor = new irsensor(0x49, lookup_table_2);
    line_follower = new linefollower(left_motor, right_motor, bottom_sensor);
    arm_board_comm = new COMMUNICATOR(PB9, PB8);
}

void robot::init()
{
    left_motor->init();
    right_motor->init();
    arm_board_comm->init();
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
    if (nDevices != 1)
    {
        digitalWrite(PC13, HIGH);
    }
    else
    {
        digitalWrite(PC13, LOW);
    }
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

void robot::sensor_info()
{
    bottom_sensor->info();
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

            //255 before
            left_motor->run(TURN_SPEED);
            right_motor->run(-TURN_SPEED);
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

void robot::find_gap_one(float _def_speed)
{
    // unsigned long start_time = millis();
    line_follower->cross_gap = false;
    do
    {
        bottom_sensor->update();
        line_follower->pid_controller.p_gain = 900.0;
        line_follower->pid_controller.p_limit = 250;
        //line_follower->default_speed = 90.0;
        line_follower->default_speed = _def_speed;
        line_follower->follow_line();
        delay_update(4);
    } while (bottom_sensor->mean() < 15);
    move_meters(-0.05);
}

void robot::establish_communication()
{
    arm_board_comm->setTransmission(true);
    while (true)
    {
        if (arm_board_comm->checkReceive())
            break;
    }
    while (true)
    {
        if (!(arm_board_comm->checkReceive()))
            break;
    }
    void establish_communication();
    robot::delay_update(40);
}
void robot::line_follow_until_right_ewok()
{
    float min_value = 30.0;
    while (1)
    {
        bottom_sensor->update();
        line_follower->default_speed = 190;
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

void robot::first_ewok_pick_up()
{
    arm_board_comm->setTransmission(false);
    line_follow_until_right_ewok();
    while (1)
    {
        line_follower->default_speed = 150;
        line_follower->follow_line();
        robot::delay_update(4);
        //sensed an ewok?
        if (arm_board_comm->checkReceive())
        {
            break;
        }
    }
    move_meters(-0.01);
    //dropped it off!
    while (1)
    {
        if (!(arm_board_comm->checkReceive()))
            break;
        robot::delay_update(4);
    }

    Serial.println("end 1 main");
}

/**
 *Begin at the position where first ewok was picked up. Turn left until it finds the black line again.
 **/
void robot::second_ewok_pick_up()
{

    //This will find the gap and back up
    //======================= PREVIOUS CODE =======================
    // find_gap_one(130.0);
    //robot::delay_update(500);
    // move_meters(0.40);
    //arm_board_comm->setTransmission(true);
    // robot::delay_update(500);
    // arm_board_comm->setTransmission(false);
    //++++++++++++++++++++++++ END PREVIOUS CODE ========================


    // turn_until_black_line(LEFT); //sweep back to black line after grabbing ewok
    // robot::delay_update(500);
    // move_meters(0.4);


    //======================= PREVIOUS CODE =======================
    //turn_until_black_line(LEFT);
    // turn_degrees(1.0);
    // turn_until_black_line(RIGHT);
    // turn_degrees(-0.1);
    //++++++++++++++++++++++++ END PREVIOUS CODE ========================
    //follow-line until ewok
    find_gap_one(130.0);
    robot::delay_update(500);
    move_meters(0.40);
    arm_board_comm->setTransmission(true);
    robot::delay_update(500);
    arm_board_comm->setTransmission(false);
    robot::delay_update(2000);

    while (1)
    { 
        line_follower->default_speed = 90.0;
        line_follower->follow_line();
        robot::delay_update(4);
        //keep line-following while there is no signal
        if (arm_board_comm->checkReceive())
        {
            break;
        }
    }
    move_meters(-0.01);
    while (1)
    {
        //received a signal! excute and break.
        if (!(arm_board_comm->checkReceive()))
            break;
        robot::delay_update(4);
    }
    Serial.println("end 2 main");
    //both arms are folded here.
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
    // move_meters(-0.1);
    // delay_update(500);
    // turn_until_black_line(LEFT);
    // robot::delay_update(1000);
    // line_follow_until_beacon();
    arm_board_comm->setTransmission(false);
    wait_for_10khz();
    arm_board_comm->setTransmission(false );
    // Serial.println("end archway main");
}

void robot::third_ewok_pick_up()
{
    //Serial.println("start 3 main");
    // delay(2000);
    // arm_board_comm->setTransmission(false);
    // delay(2000);
    //if the turn table detect works well we can use:
    //make left come down after passing turn table
    find_gap_one(100.0); 
    move_meters(-0.3);
    arm_board_comm->setTransmission(true);
    robot::delay_update(500);
    while (1)  
    {
        line_follower->follow_line();
        robot::delay_update(4);
        if (arm_board_comm->checkReceive())
            break;
    }
    move_meters(-0.01);

    while (1)
    {
        if (!(arm_board_comm->checkReceive()))
            break;
        robot::delay_update(4);
    }
    //If the turn table function does not work, we will just have to implement some sort
    //timer to tell us how long it has been and if we can follow the tape.
    Serial.println("end 3 main");
}

void robot::return_home()
{
    robot::delay_update(900);
    turn_degrees(90);
    turn_until_black_line(RIGHT);
    find_gap_one(90.0);

    robot::delay_update(500);
    move_meters(-0.15);
    robot::delay_update(500);
    turn_until_black_line(LEFT); //sweep back to black line after grabbing ewok
    robot::delay_update(500);
    move_meters(0.4);
    turn_until_black_line(RIGHT); 
    find_gap_one(125.0);
    move_meters(-0.05);
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
        bottom_sensor->update();
        line_follower->follow_line();
        delay_update(4);
        //
        if (bottom_sensor->mean() > TURN_TABLE_GAP && flag == 0)
        {
            flag = 1;
            time_flag = millis();
            //if we want to stop after passing one edge of turn table
            if (num == ONCE)
            {
                break;
            }
        }
    } while (flag != 1 || millis() < time_flag + 200 || bottom_sensor->mean() < TURN_TABLE_GAP);
    move_meters(-0.05);
}

/**
 * Max sensor value for IR array is 30. Inverse weighted mean takes current reading and
 * subtract it from 30 and computes the weighted mean from 8 sensor values using sensor indices. 
 */
void robot::sensor_inverse_mean()
{
    robot::delay_update(20);
    bottom_sensor->update();
    Serial.println(bottom_sensor->inverse_weighted_mean());
}

void robot::sensor_mean()
{
    robot::delay_update(20);
    bottom_sensor->update();
    Serial.println(bottom_sensor->mean());
}

void robot::sensor_min()
{
    robot::delay_update(20);
    bottom_sensor->update();
    Serial.println(bottom_sensor->min_distance());
}
