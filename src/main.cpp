// #include <Wire.h>
// #include <irsensor.h>
// #include <linefollower.h>

// //create ir sensor
// int line_lookup[20][9] =
//     {{1, 125, 121, 128, 125, 124, 131, 134, 148},
//      {3, 132, 128, 143, 134, 132, 140, 142, 157},
//      {5, 145, 140, 151, 144, 142, 151, 153, 171},
//      {7, 155, 149, 158, 152, 150, 159, 163, 185},
//      {10, 170, 164, 171, 165, 162, 173, 180, 231},
//      {12, 181, 175, 182, 174, 170, 183, 193, 586},
//      {15, 202, 194, 207, 191, 183, 201, 227, 1272},
//      {17, 232, 212, 252, 207, 194, 221, 369, 1615},
//      {20, 493, 350, 733, 326, 220, 436, 902, 1966},
//      {23, 772, 671, 1107, 739, 318, 826, 1240, 2171},
//      {25, 932, 856, 1321, 985, 549, 1058, 1436, 2284},
//      {28, 1102, 1047, 1546, 1245, 808, 1310, 1645, 2406},
//      {30, 1254, 1208, 1725, 1440, 1006, 1500, 1806, 2515},
//      {33, 1311, 1269, 1809, 1538, 1105, 1595, 1878, 2545},
//      {36, 1422, 1387, 1944, 1689, 1261, 1743, 2001, 2622},
//      {39, 1433, 1403, 1974, 1724, 1300, 1778, 2023, 2625},
//      {42, 1572, 1548, 2130, 1895, 1473, 1947, 2166, 2727},
//      {44, 1614, 1587, 2171, 1939, 1521, 1990, 2203, 2750},
//      {46, 1658, 1630, 2223, 1992, 1579, 2045, 2245, 2775},
//      {50, 1660, 1640, 2240, 1999, 1590, 2055, 2255, 2780}};

// irsensor line_sensor = irsensor(0x49, line_lookup);

// //create tracks
// HTHING left_motor = HTHING(PB0, PB3);
// HTHING right_motor = HTHING(PA7, PB5);
// track left_track = track(&left_motor); //track will contain functions in the future (closed loop motor control)
// track right_track = track(&right_motor);

// //create line follower
// linefollower line_follower = linefollower(&left_track, &right_track, &line_sensor);

// void setup()
// {
//   Serial.begin(9600); // Start Serial
//   Wire.begin();
//   line_follower.debug = false;
// }

// void loop()
// {
//   //follow the damn line
//   line_follower.follow_line();

//   //tune proportional gain with the potentiometer
//   int reading = analogRead(PA6);
//   int p_gain = map(reading, 0, 4096, 0, -500);
//   line_follower.pid_controller.p_gain = p_gain;

//   // delay(50);

//picking up ewoks
#include <Wire.h>
#include <irsensor.h>

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

irsensor ewok_sensor = irsensor(0x48, lookup_table_1);

void setup()
{
  Serial.begin(9600); // Start Serial
  Serial.println("Sketch begin");
  Wire.begin();
}

void loop()
{
  ewok_sensor.update();
  for (int i = 0; i < 8; i++)
  {
    Serial.print(ewok_sensor.distance_readings[i]);
    Serial.print(",");
  }
  Serial.println();
  Serial.print("Inverse weighted mean:");
  Serial.print(ewok_sensor.inverse_weighted_mean());
  Serial.println();
  Serial.print("Mean:");
  Serial.print(ewok_sensor.mean());
  Serial.println();
  Serial.print("Weighted Mean:");
  Serial.print(ewok_sensor.weighted_mean());
  Serial.println();
  delay(1000); // Wait for 1 second
}


// void ewok_pickup(irsensor ewok_sensor, Arm arm)
