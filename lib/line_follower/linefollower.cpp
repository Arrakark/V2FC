#include "linefollower.h"

linefollower::linefollower(HBRIDGE*_left_track, HBRIDGE*_right_track, irsensor *_main_sensor)
{
	left_track = _left_track;
	right_track = _right_track;
	main_sensor = _main_sensor;
	pid_controller = pid();
	pid_controller.p_gain = 5.0;
	pid_controller.p_limit = 200.0;
	default_speed = 120;
	debug = false;
}

void linefollower::follow_line()
{
	// Serial.println("8Start line following......");
	//get and calculate the control error
	main_sensor->update();
	//float error = main_sensor->max_position() - 4.5;
	float error = main_sensor->weighted_mean() - 4.5;
	float control = pid_controller.output(error);
	float left_speed = default_speed + control;
	float right_speed = default_speed - control;

	//checks if we are driving off a cliff
	if (main_sensor->mean() < CLIFF_DISTANCE)
	{
		//control the tracks normally (on solid ground)
		
		// Serial.println("No CLIFF!!!");
		left_track->run((int)left_speed);
		right_track->run((int)right_speed);
	}
	else {
		//driving off a cliff, continue to go forward
		Serial.println("CLIFF!!!");
		left_track->run(default_speed);
		right_track->run(default_speed);
	}

	//debug
	if (debug){
		Serial.print("Error: ");
		Serial.print(error);
		Serial.print(" Control: ");
		Serial.print(control);
		Serial.print(" Left Track: ");
		Serial.print(left_speed);
		Serial.print(" Right Track: ");
		Serial.print(right_speed);
		Serial.println();
	}
}