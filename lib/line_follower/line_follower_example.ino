#include <Wire.h>
#include <irsensor.h>
#include <linefollower.h>

//create ir sensor
int line_lookup[20][9] =
    {{1, 125, 121, 128, 125, 124, 131, 134, 148},
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
irsensor line_sensor = irsensor(0x49, line_lookup);

//create tracks
HTHING left_motor = HTHING(PB0, PB3);
HTHING right_motor = HTHING(PA7, PB5);
track left_track = track(&left_motor); //track will contain functions in the future (closed loop motor control)
track right_track = track(&right_motor);

//create line follower
linefollower line_follower = linefollower(&left_motor, &right_motor, &line_sensor);

void setup()
{
  Serial.begin(9600); // Start Serial
  Wire.begin();
  line_follower.debug = false;
}

void loop()
{
  //follow the damn line
  line_follower.follow_line();

  //tune proportional gain with the potentiometer
  int reading = analogRead(PA6);
  int p_gain = map(reading, 0, 4096, 0, -200);
  line_follower.pid_controller.p_gain = p_gain;

  for (int i = 0; i < 8; i++)
  {
    Serial.print(line_follower.main_sensor->distance_readings[i]);
    Serial.print(",");
  }
  Serial.println();
}
