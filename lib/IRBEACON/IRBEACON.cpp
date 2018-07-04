#include "IRBEACON.h"

int IRBEACON::pin;
int IRBEACON::count;
int IRBEACON::readings[NUMBER_OF_SAMPLES];

int IRBEACON::read(int _pin)
{
    pin = _pin;
    count = 0;
    HardwareTimer timer(TIMER);
    timer.pause();
    timer.setPeriod(SAMPLING_TIME);
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1, 1); // Interrupt 1 count after each update
    timer.attachCompare1Interrupt(sample);
    timer.refresh();
    timer.resume();
    //wait to make sure that all of the samples have been taken
    delayMicroseconds(NUMBER_OF_SAMPLES * SAMPLING_TIME + SAMPLING_TIME);
    int crossed = times_crossed();
    if (crossed > 4 && crossed < 8){
        return 1;
    }
    if (crossed > 56 && crossed < 65){
        return 2;
    }
    return 0;
}

void IRBEACON::sample()
{
    if (count < NUMBER_OF_SAMPLES)
    {
        readings[count] = analogRead(pin);
        count++;
    }
    else
    {
        HardwareTimer timer(TIMER);
        timer.pause();
        count = 0;
    }
}

int IRBEACON::times_crossed()
{
    //locate max and min values
    int max = 0;
    int min = 0;
    for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        if (readings[i] > max)
        {
            max = readings[i];
        }
        if (readings[i] < min)
        {
            min = readings[i];
        }
    }
    //if vpp < 100 reject reading and return 0
    if (abs(max - min) < 100)
    {
        return 0;
    }
    int average = min + abs(max - min) / 2;
    int crossed = 0;
    //count number of times crossed
    for (int i = 1; i < NUMBER_OF_SAMPLES - 1; i++)
    {
        if (readings[i] > average && readings[i - 1] < average)
        {
            crossed++;
        }
        if (readings[i] < average && readings[i - 1] > average)
        {
            crossed++;
        }
    }
    return crossed;
}