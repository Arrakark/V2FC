#include "surprise_2.h"

bool left = false;
bool right = false;
bool stop = true;
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
int ledState = LOW;
const long interval = 1500;

void surprise_2::run_surprise_2()
{
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        if (ledState == LOW)
        {
            ledState = HIGH;
        }
        else
        {
            ledState = LOW;
        }
    }
    if (stop)
    {
        digitalWrite(PA11, HIGH);
    }
    else
    {
        digitalWrite(PA11, LOW);
    }
    if (left)
    {
        digitalWrite(PA12, ledState);
    }
    else
    {
        digitalWrite(PA12, LOW);
    }
    if (right)
    {
        digitalWrite(PA15, ledState);
    }
    else
    {
        digitalWrite(PA15, LOW);
    }
}

void surprise_2::stop_surprise()
{
    if (stop == true)
    {
        stop == false;
    }
    else
    {
        stop == true;
    }
}
void surprise_2::left_surprise()
{
    if (left == true)
    {
        left == false;
    }
    else
    {
        left == true;
    }
}
void surprise_2::right_surprise()
{
    if (right == true)
    {
        right == false;
    }
    else
    {
        right == true;
    }
}
void surprise_2::init_surprise_2()
{
    pinMode(PA11, OUTPUT);
    pinMode(PA12, OUTPUT);
    pinMode(PA15, OUTPUT);
}