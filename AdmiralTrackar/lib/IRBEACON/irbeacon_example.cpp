#include <Arduino.h>
#include <IRBEACON.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int value = IRBEACON::read(PA5);
  if (value == 0)
  {
    Serial.println("No Beacon Detected!");
  }
  if (value == 1)
  {
    Serial.println("1khz Beacon detected!");
  }
  if (value == 2)
  {
    Serial.println("10khz Beacon detected!");
  }
  delay(50);
}
