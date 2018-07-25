#include <Arduino.h>
#include <ir_encoder.h>

void encoder_function2();

ir_encoder encoder = ir_encoder(PA4, 8);
// void (ir_encoder::* ptfptr) (void) = &ir_encoder::encoder_function;

void setup()
{
	Serial.begin(9600);
	encoder.init();
	// attachInterrupt(digitalPinToInterrupt(encoder.inputPin), (encoder.*ptfptr)(void), CHANGE);
	// attachInterrupt(digitalPinToInterrupt(encoder.inputPin), &encoder.encoder_function, CHANGE);
	attachInterrupt(digitalPinToInterrupt(encoder.inputPin), &encoder_function2, FALLING);

	Serial.println("Serial Begin");
}

void loop()
{


	// delay(100);
}

void encoder_function2()
{
	// encoder.encoder_count ++;
	// if(digitalRead(encoder.inputPin) == encoder.prev_state) 
	// {

	for (int i = 0; i < 5000; i++)
	{
		if (digitalRead(encoder.inputPin) != 0)
		{
			return;
		}
	}
	encoder.encoder_count =+ 2;
	// encoder.prev_state = !encoder.prev_state;
	Serial.println(encoder.encoder_count);
	// }

	// Serial.print("Encoder Count: ");

	// Serial.println();

	// Serial.print("Encoder Distance: ");
	// Serial.print(encoder.getDistance());
	// Serial.println();
}