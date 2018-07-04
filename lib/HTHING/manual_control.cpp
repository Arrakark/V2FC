#include <Arduino.h>
#include <HTHING.h>

HTHING leftm = HTHING(PA3,PA2);
HTHING rightm = HTHING(PA1,PA0);

void setup()
{
  Serial.begin(9600);
  leftm.stop();
  rightm.stop();
}

//throttle PB0, min: 1116 max: 1973
//steering PB1, min: 1006 max: 1967

void loop()
{
  int throttle_raw = pulseIn(PB0, HIGH);
  int steering_raw = pulseIn(PB1, HIGH);
  int throttle = map(throttle_raw, 1116, 1973, -255, 255);
  int steering = map(steering_raw, 1006, 1967, -255, 255);
  int left_motor = throttle + steering;
  int right_motor = throttle - steering;

  leftm.run(-left_motor);
  rightm.run(right_motor);

  Serial.print("Throttle raw: ");
  Serial.print(throttle_raw);
  Serial.print(" Steering raw: ");
  Serial.print(steering_raw);
  Serial.print(" Left Motor: ");
  Serial.print(left_motor);
  Serial.print(" Right Motor: ");
  Serial.println(right_motor);
  delay(100);
}
