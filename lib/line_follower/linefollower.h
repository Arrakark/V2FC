#pragma once
#include <Arduino.h>
#include <track.h>

class linefollower
{
public:
	//consturctor
	linefollower(track * _left_track, track * right_track);
	//member functions
	void setup();
	void follow_line();
	void evaluate_commands();
private:
	track * left_track;
	track * right_track;
	static void setgain();
	static void setlimit();
	static void setsensor();
	static void setspeed();
	static void setdebug();
	static void returnPID();
	static void toggledebug();
	static void OnUnknownCommand();
	int trim;
	unsigned long time;
};
