#pragma once
#include <Arduino.h>
#include <track.h>
#include <pid.h>
#include <irsensor.h>

#define CLIFF_DISTANCE 15

class linefollower
{
public:
	//consturctor
	linefollower(track * left_track, track * right_track, irsensor * _main_sensor);
	//member functions
	void follow_line();
	bool debug;
	pid pid_controller;
	track * left_track;
	track * right_track;
	irsensor * main_sensor;
	int default_speed;
private:
};
