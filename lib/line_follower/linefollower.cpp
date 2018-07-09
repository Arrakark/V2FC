#include "linefollower.h"

bool debug = false;

CmdMessenger cmdMessenger = CmdMessenger(Serial);

enum
{
	GAIN = 1,		 //GAIN,
	LIMIT = 2,		 //LIMIT,
	SENSOR = 3,		 //SENSOR,
	speed = 4,		 //speed,
	getPID = 5,		 //getPID,
	enabledebug = 6, //enabledebug,
	kError = 7,		 //kError,
};

float NORMAL_SPEED = 255;

linefollower::linefollower(LiquidCrystal *passed_crystal, motorClass *passed_motor)
{
	LCD = passed_crystal;
	motor = passed_motor;

	cmdMessenger.attach(OnUnknownCommand);
	cmdMessenger.attach(GAIN, setgain);
	cmdMessenger.attach(LIMIT, setlimit);
	cmdMessenger.attach(SENSOR, setsensor);
	cmdMessenger.attach(speed, setspeed);
	cmdMessenger.attach(getPID, returnPID);
	cmdMessenger.attach(enabledebug, toggledebug);
	time = 0;
}

void linefollower::setup()
{

	float right_read = analogRead(RIGHT_SENSOR);
	float left_read = analogRead(LEFT_SENSOR);
	if (debug)
	{
		Serial.print("RIGHT_SENSOR: " + String(right_read));
		Serial.println(" LEFT_SENSOR: " + String(left_read));
	}
}


void linefollower::follow_line()
{
	
}

void linefollower::evaluate_commands(){
	cmdMessenger.feedinSerialData();
}


void linefollower::setgain()
{
	char type = cmdMessenger.readCharArg();
	if (type == 'P')
	{
		P_GAIN = cmdMessenger.readFloatArg();
	}
	if (type == 'I')
	{
		I_GAIN = cmdMessenger.readFloatArg();
	}
	if (type == 'D')
	{
		D_GAIN = cmdMessenger.readFloatArg();
	}
}

void linefollower::setlimit()
{
	char type = cmdMessenger.readCharArg();
	if (type == 'P')
	{
		P_LIMIT = cmdMessenger.readFloatArg();
	}
	if (type == 'I')
	{
		I_LIMIT = cmdMessenger.readFloatArg();
	}
	if (type == 'D')
	{
		D_LIMIT = cmdMessenger.readFloatArg();
	}
}
void linefollower::setsensor()
{
	char dir = cmdMessenger.readCharArg();
	if (dir == 'R')
	{
		char maxmin = cmdMessenger.readCharArg();
		if (maxmin == 'X')
		{
			RIGHT_MAX = cmdMessenger.readInt16Arg();
		}
		if (maxmin == 'N')
		{
			RIGHT_MIN = cmdMessenger.readInt16Arg();
		}
	}
	if (dir == 'L')
	{
		char maxmin = cmdMessenger.readCharArg();
		if (maxmin == 'X')
		{
			LEFT_MAX = cmdMessenger.readInt16Arg();
		}
		if (maxmin == 'N')
		{
			LEFT_MIN = cmdMessenger.readInt16Arg();
		}
	}
}
void linefollower::setspeed()
{
	NORMAL_SPEED = cmdMessenger.readInt16Arg();
}
void linefollower::OnUnknownCommand()
{
	cmdMessenger.sendCmd(kError, "Command without attached callback");
}
void linefollower::toggledebug()
{
	debug = !debug;
}
void linefollower::returnPID()
{
	Serial.print("PGAIN: ");
	Serial.print(P_GAIN);
	Serial.print(" IGAIN: ");
	Serial.print(I_GAIN);
	Serial.print(" DGAIN: ");
	Serial.print(D_GAIN);
	Serial.print(" PLIMIT: ");
	Serial.print(P_LIMIT);
	Serial.print(" ILIMIT: ");
	Serial.print(I_LIMIT);
	Serial.print(" DLIMIT: ");
	Serial.println(D_LIMIT);
}