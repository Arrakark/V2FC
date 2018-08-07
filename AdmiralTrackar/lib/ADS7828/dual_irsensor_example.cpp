
// dual irsensor example 
// (along with single irsensor outputs for comparison and verification)

#include <Wire.h>
#include <irsensor.h>
#include <dual_irsensor.h>
#include <Arduino.h>

int lookup_table_1[20][9] = {{1, 131, 125, 134, 120, 116, 122, 120, 148},
                           {3, 140, 134, 145, 137, 136, 139, 143, 157},
                           {5, 150, 145, 155, 147, 144, 150, 155, 171},
                           {7, 160, 156, 163, 156, 152, 158, 163, 185},
                           {10, 174, 169, 176, 169, 165, 171, 177, 231},
                           {12, 182, 177, 183, 179, 174, 180, 189, 1272},
                           {15, 196, 188, 196, 198, 189, 197, 513, 1615},
                           {17, 207, 195, 205, 217, 201, 211, 240, 1966},
                           {20, 227, 207, 222, 441, 240, 275, 576, 2171},
                           {23, 373, 229, 277, 876, 520, 655, 940, 2284},
                           {25, 417, 237, 337, 1115, 761, 896, 1143, 2406},
                           {28, 629, 305, 613, 1400, 1057, 1193, 1406, 2515},
                           {30, 768, 429, 764, 1587, 1251, 1387, 1580, 2545},
                           {33, 856, 540, 900, 1688, 1363, 1499, 1673, 2622},
                           {36, 960, 659, 1970, 1850, 1531, 1669, 1833, 1809},
                           {39, 1029, 736, 2085, 1984, 1670, 1812, 1966, 1944},
                           {42, 1081, 785, 2183, 2094, 1783, 1927, 2077, 2058},
                           {44, 1097, 809, 2233, 2157, 1847, 1990, 2140, 2123},
                           {46, 1098, 810, 2283, 2211, 1908, 2051, 2202, 2187},
                           {50, 1159, 889, 2382, 2321, 2020, 2168, 2318, 2303}}; // Include ADS7828.h for TI ADS7828 functions

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

irsensor left_sensor = irsensor(0x48, lookup_table_1);
irsensor right_sensor = irsensor(0x4A, lookup_table_3);
dual_irsensor front_sensor = dual_irsensor(&left_sensor, &right_sensor);

void setup()
{
  Serial.begin(9600); // Start Serial
  Serial.println("Sketch begin");
  Wire.begin();
}

void loop()
{
  front_sensor.update();
  Serial.println("Dual Sensor Readings");

  for (int i = 0; i < 16; i++)
  {
    Serial.print(front_sensor.distance_readings[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("Inverse weighted mean:");
  Serial.print(front_sensor.inverse_weighted_mean());
  Serial.println();
  Serial.print("Mean:");
  Serial.print(front_sensor.mean());
  Serial.println();
  Serial.print("Weighted Mean:");
  Serial.print(front_sensor.weighted_mean());
  Serial.println();
  Serial.print("Max Distance: ");
  Serial.print(front_sensor.max_distance());
  Serial.println();
  Serial.print("Min Distance: ");
  Serial.print(front_sensor.min_distance());
  Serial.println();
  Serial.print("Max Position: ");
  Serial.print(front_sensor.max_position());
  Serial.println();
  Serial.print("Min Position: ");
  Serial.print(front_sensor.min_position());
  Serial.println(); 
  Serial.println();


  left_sensor.update();
  Serial.println("Left Sensor(1) Readings");
  for (int i = 0; i < 8; i++)
  {
    
    Serial.print(left_sensor.distance_readings[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("Inverse weighted mean:");
  Serial.print(left_sensor.inverse_weighted_mean());
  Serial.println();
  Serial.print("Mean:");
  Serial.print(left_sensor.mean());
  Serial.println();
  Serial.print("Weighted Mean:");
  Serial.print(left_sensor.weighted_mean());
  Serial.println();
  Serial.print("Max Distance: ");
  Serial.print(left_sensor.max_distance());
  Serial.println();
  Serial.print("Min Distance: ");
  Serial.print(left_sensor.min_distance());
  Serial.println();
  Serial.print("Max Position: ");
  Serial.print(left_sensor.max_position());
  Serial.println();
  Serial.print("Min Position: ");
  Serial.print(left_sensor.min_position());
  Serial.println(); 
  Serial.println();


  right_sensor.update();
  Serial.println("Right Sensor(3) Readings");
  for (int i = 0; i < 8; i++)
  {
    Serial.print(right_sensor.distance_readings[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("Inverse weighted mean:");
  Serial.print(right_sensor.inverse_weighted_mean());
  Serial.println();
  Serial.print("Mean:");
  Serial.print(right_sensor.mean());
  Serial.println();
  Serial.print("Weighted Mean:");
  Serial.print(right_sensor.weighted_mean());
  Serial.println();
  Serial.print("Max Distance: ");
  Serial.print(right_sensor.max_distance());
  Serial.println();
  Serial.print("Min Distance: ");
  Serial.print(right_sensor.min_distance());
  Serial.println();
  Serial.print("Max Position: ");
  Serial.print(right_sensor.max_position());
  Serial.println();
  Serial.print("Min Position: ");
  Serial.print(right_sensor.min_position());
  Serial.println(); 
  Serial.println();

  delay(1000); // Wait for 1 second

}