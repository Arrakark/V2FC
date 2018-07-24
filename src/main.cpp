#include <HBRIDGE.h>

//create tracks
HBRIDGE left_motor = HBRIDGE(PA1, PB0);
HBRIDGE right_motor = HBRIDGE(PA3,PA7);

//The decleration of the HBRIDGE objects here has the correct pin layout
//for each motor

void setup()
{
  Serial.begin(9600); // Start Serial
  left_motor.init();
  right_motor.init();
  delay(5000);
  int pos = 220;
  left_motor.run(pos);
  right_motor.run(pos);
}

void loop()
{
}
