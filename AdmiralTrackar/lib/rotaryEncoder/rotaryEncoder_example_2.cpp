#include <Arduino.h>
#include <HTHING.h>

//create tracks
// HTHING left_motor = HTHING(PB0, PB3);

//use encoder 1 for now

// Used for generating interrupts using CLK signal
int ENC_CLK = PA2; //encoder 1 is PA4; encoder 2 is PA2

// Used for reading DT signal
int ENC_DATA = PA1;//encoder 1 is PA3; encoder 2 is PA1

// Updated by encoder1_read (Interrupt Service Routine)
volatile int encoder_count = 0;

// ------------------------------------------------------------------
// Interrupt Service Routine
// ------------------------------------------------------------------
// void encoder1_read(void) 
// {
//   volatile static const signed char encoder_states[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
//   volatile static unsigned char ABs=0x00; //AB key read out, Previous in the high 2 bits and current in the low two bits;

//   ABs = (ABs << 2) & 0x0f; //left 2 bits now contain the previous AB key read-out;

//   if (digitalRead(ENC_CLK)) 
//   {
//     ABs |= 0x02; //set the 1st bit if A is high now;
//   }

//   if (digitalRead(ENC_DATA)) 
//   {
//     ABs |= 0x01; //set the 0th bit if B is high;
//   }

//   encoder_count += encoder_states[ABs]; 
// }

void encoder1_read(void)
{
  volatile static uint8_t ABs = 0;
  ABs = (ABs << 2) & 0x0f; //left 2 bits now contain the previous AB key read-out;
  ABs |= (digitalRead(ENC_CLK) << 1) | digitalRead(ENC_DATA);
  switch (ABs)
  {
    case 0x0d:
      encoder_count++;
      break;
    case 0x0e:
      encoder_count--;
      break;
  }
}

// ------------------------------------------------------------------
// SETUP 
// ------------------------------------------------------------------
void setup() {

  // Just whilst we debug, view output on serial monitor
  Serial.begin(9600);

  // Rotary pulses are INPUTs
  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(ENC_DATA, INPUT_PULLUP);

  // Attach the routine to service the interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_CLK), encoder1_read, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_DATA), encoder1_read, CHANGE);
  //can no '&' for encoder1_read function and no need 'digitalPinToInterrupt' for Encoder Pins

  // Ready to go!
  Serial.println("Start");
}

// ------------------------------------------------------------------
// MAIN LOOP
// ------------------------------------------------------------------
void loop() {

  //prints rotary encoder counter value

  // encoder1_read();

  Serial.print("Virtual Position: ");
  Serial.print(encoder_count);
  Serial.println();

  // int max = 80;
  // int pos = 0;

  // left_motor.run(max); // tell servo to go to position in variable 'pos'
  // delay(15000);        // waits 15ms for the servo to reach the position

  // left_motor.run(-max); // tell servo to go to position in variable 'pos'
  // delay(15000); 

  // delay(1000);


}