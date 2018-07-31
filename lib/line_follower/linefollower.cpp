#include "linefollower.h"

linefollower::linefollower(HBRIDGE *_left_track, HBRIDGE *_right_track, irsensor *_main_sensor)
{
	left_track = _left_track;
	right_track = _right_track;
	main_sensor = _main_sensor;
	pid_controller = pid();
	pid_controller.p_gain = 600.0;
	pid_controller.p_limit = 250.0;
	pid_controller.d_gain = 2.0;
	pid_controller.d_limit = 100.0;
	default_speed = 120;
	debug = false;
	cross_gap = true;
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
		left_track->run((int)left_speed);
		right_track->run((int)right_speed);
	}
	else
	{
		if (cross_gap)
		{
			left_track->run(default_speed);
			right_track->run(default_speed);
		}
		else
		{
			left_track->run(0);
			right_track->run(0);
		}
	}

	//debug
	if (debug)
	{
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