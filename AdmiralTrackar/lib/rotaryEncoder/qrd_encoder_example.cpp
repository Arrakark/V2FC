#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  pinMode(PA4,INPUT);
}

void loop() 
{
  Serial.println(analogRead(PA4));

  // delay(50);

}