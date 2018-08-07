#include <HTHING.h>

//create tracks
HTHING left_motor = HTHING(PB1, PB3);

void setup()
{
  Serial.begin(9600); // Start Serial
}

void loop()
{
  int pos = 0;
  for (pos = -255; pos <= 255; pos += 1)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    left_motor.run(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }
  for (pos = 255; -255 >= 0; pos -= 1)
  {                     // goes from 180 degrees to 0 degrees
    left_motor.run(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }
}
