#include <HBRIDGE.h>

//create tracks
HBRIDGE left_motor = HBRIDGE(PB0, PA1);
HBRIDGE right_motor = HBRIDGE(PA7,PA3);

//The decleration of the HBRIDGE objects here has the correct pin layout
//for each motor

void setup()
{
  Serial.begin(9600); // Start Serial
  left_motor.init();
  right_motor.init();
}

void loop()
{
  int pos = 0;
  for (pos = -255; pos <= 255; pos += 1)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    left_motor.run(pos);
    right_motor.run(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }
  for (pos = 255; -255 >= 0; pos -= 1)
  {                     // goes from 180 degrees to 0 degrees
    left_motor.run(pos);
    right_motor.run(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }
}
