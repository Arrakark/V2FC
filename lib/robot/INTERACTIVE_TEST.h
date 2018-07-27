#ifndef INTERACTIVE_TEST_H
#define INTERACTIVE_TEST_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <robot.h>
#include <armControl.h>
#include <SLIFT.h>
#include <HBRIDGE.h>
#include <irsensor.h>
#include <IRBEACON.h>

class INTERACTIVE_TEST
{
    public:
        static void init();
        static void mainMenu();

        static void armTests();
        static void sliftTests();
        static void motorTests();
        static void sensorTests();
        static void beaconTests();

        static void armVertical();
        static void armHorzizontal();
        static void armSearch();
        static void armPickup();
        static void armDropoff();
        static void grabberOpen();
        static void grabberHug();

        static void sliftDownSwitch();
        static void sliftUpSwitch();
        static void sliftBasketSwitch();
        static void sliftMoveUp();
        static void sliftMoveDown();
        static void sliftStay();

        static void motorsForward();
        static void motorsReverse();
        static void motorsOpposite1();
        static void motorsOpposite2();
        static void rightMotorForward();
        static void rightMotorReverse();
        static void leftMotorForward();
        static void leftMotorReverse();
        static void motorsStop();

        static void lineSensor();
        static void ewokSensor();
        static void edgeSensorLeft();
        static void edgeSensorRight();

        static void irBeacon();

    private:
        INTERACTIVE_TEST() {}
        static Adafruit_SSD1306 display;
        static SLIFT scissorLift;
        static HBRIDGE leftMotor;
        static HBRIDGE rightMotor;

        static int menuPosition;

        static int leftButton;
        static int rightButton;
        static int middleButton;

        static char* menuStrings[];
        static char* armStrings[];
        static char* sliftStrings[];
        static char* motorStrings[];
        static char* sensorStrings[];
        static char* beaconStrings[];

};

#endif