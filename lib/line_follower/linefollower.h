#pragma once
#include <Arduino.h>
#include <HBRIDGE.h>
#include <pid.h>
#include <irsensor.h>

#define CLIFF_DISTANCE 8

class linefollower
{
public:
	//consturctor
	linefollower(HBRIDGE* left_track, HBRIDGE* right_track, irsensor * _main_sensor);
	//member functions
	void follow_line();
	bool debug;
	pid pid_controller;
	HBRIDGE* left_track;
	HBRIDGE* right_track;
	irsensor * main_sensor;
	int default_speed;
	bool cross_gap;
private:
};
