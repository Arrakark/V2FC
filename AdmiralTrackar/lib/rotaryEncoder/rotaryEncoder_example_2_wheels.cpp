#include <Arduino.h>
#include <HTHING.h>

//create tracks
HTHING left_motor = HTHING(PB0, PB3);

//use encoder 1 for now

// Used for generating interrupts using CLK signal
const int ENC_CLK = PA4; //encoder 1 is PA4; encoder 2 is PA2

// Used for reading DT signal
const int ENC_DATA = PA3;//encoder 1 is PA3; encoder 2 is PA1

// Keep track of last rotary value
int lastCount = 0;

// Updated by the ISR (Interrupt Service Routine)
volatile int virtualPosition = 0;

volatile int encoderCount = 0;

// float encoder_reading_rate = 0;

// ------------------------------------------------------------------
// INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT 
// ------------------------------------------------------------------
void encoder1_read() 
{
  volatile static const signed char encoder_states[]={0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
  volatile static unsigned char ABs=0x00; //AB key read out, Previous in the high 2 bits and current in the low two bits;

  ABs = (ABs << 2) & 0x0f; //left 2 bits now contain the previous AB key read-out;
  if (digitalRead(ENC_CLK)) ABs |= 0x02; //set the 1st bit if A is high now;
  if (digitalRead(ENC_DATA)) ABs |= 0x01; //set the 0th bit if B is high;
  encoderCount += encoder_states[ABs]; 
}

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    
// ------------------------------------------------------------------
void setup() {

  // Just whilst we debug, view output on serial monitor
  Serial.begin(9600);

  // Rotary pulses are INPUTs
  pinMode(ENC_CLK, INPUT);
  pinMode(ENC_DATA, INPUT);

  // Attach the routine to service the interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_CLK), encoder1_read(), FALLING);

  // Ready to go!
  Serial.println("Start");
}

// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {

//   // If the current rotary switch position has changed then update everything
//   if (virtualPosition != lastCount) {

//     // Write out to serial monitor the value and direction
//     Serial.print(virtualPosition > lastCount ? "Up  :" : "Down:");
//     Serial.println(virtualPosition);

//     // Keep track of this new value
//     lastCount = virtualPosition ;
//   }

  Serial.print("Virtual Position: ");
  Serial.print(encoderCount);
  Serial.println();

  int max = 80;
  int pos = 0;

  left_motor.run(max); // tell servo to go to position in variable 'pos'
  delay(15000);        // waits 15ms for the servo to reach the position

  left_motor.run(-max); // tell servo to go to position in variable 'pos'
  delay(15000); 

  //delay(1000);
}