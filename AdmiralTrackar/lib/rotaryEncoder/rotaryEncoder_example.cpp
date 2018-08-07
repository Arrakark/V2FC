#include <Arduino.h>

//use encoder 1 for now

// Used for generating interrupts using CLK signal
const int PinA = PA4; //encoder 1 is PA4; encoder 2 is PA2

// Used for reading DT signal
const int PinB = PA3;//encoder 1 is PA3; encoder 2 is PA1

// Keep track of last rotary value
int lastCount = 0;

// Updated by the ISR (Interrupt Service Routine)
volatile int virtualPosition = 0;

// float encoder_reading_rate = 0;

// ------------------------------------------------------------------
// INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT 
// ------------------------------------------------------------------
void isr ()  {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // If interrupts come faster than 5ms, assume it's a bounce and ignore
  if (interruptTime - lastInterruptTime > 2) {
    if (digitalRead(PinB) == LOW)
    {
      virtualPosition-- ; // Could be -5 or -10; more negative when CCW
    }
    else 
    {
      virtualPosition++ ; // Could be +5 or +10; more positive when CW
    }

    // Restrict value from 0 to +100
    //virtualPosition = min(100, max(0, virtualPosition));

    // Keep track of when we were here last (no more than every 5ms)
    lastInterruptTime = interruptTime;
  }
}

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    
// ------------------------------------------------------------------
void setup() {
  // Just whilst we debug, view output on serial monitor
  Serial.begin(9600);

  // Rotary pulses are INPUTs
  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);

  // Attach the routine to service the interrupts
  attachInterrupt(digitalPinToInterrupt(PinA), isr, FALLING);

  // Ready to go!
  Serial.println("Start");
}

// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {

  // If the current rotary switch position has changed then update everything
  if (virtualPosition != lastCount) {

    // Write out to serial monitor the value and direction
    Serial.print(virtualPosition > lastCount ? "Up  :" : "Down:");
    Serial.println(virtualPosition);

    // Keep track of this new value
    lastCount = virtualPosition ;
  }

  Serial.print("Virtual Position: ");
  Serial.print(virtualPosition);
  Serial.println();

  // Serial.print("Last Count: ");
  // Serial.print(lastCount);
  // Serial.println();

  // Serial.print("PinB Status: ");
  // Serial.print(digitalRead(PinB));
  // Serial.println();

  // Serial.print("PinA Status: ");
  // Serial.print(digitalRead(PinA));
  // Serial.println();

  //delay(1000);
}