#include <Wire.h>
#include <irsensor.h>

int lookup_table[20][9] = {{1, 131, 125, 134, 120, 116, 122, 120, 148},
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

irsensor main_sensor = irsensor(0x49, lookup_table);

void setup()
{
  Serial.begin(9600); // Start Serial
  Serial.println("Sketch begin");
  Wire.begin();
}

void loop()
{
  main_sensor.update();
  for (int i = 0; i < 8; i++)
  {
    Serial.print(main_sensor.distance_readings[i]);
    Serial.print(",");
  }
  Serial.println();
  Serial.print("Inverse weighted mean:");
  Serial.print(main_sensor.inverse_weighted_mean());
  Serial.println();
  Serial.print("Mean:");
  Serial.print(main_sensor.mean());
  Serial.println();
  Serial.print("Weighted Mean:");
  Serial.print(main_sensor.weighted_mean());
  Serial.println();
  delay(1000); // Wait for 1 second
}
