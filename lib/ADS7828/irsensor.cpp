#include "irsensor.h"

irsensor::irsensor(unsigned char _adress, int _lookup_table[ROW][COL]) : adc(_adress)
{
    adc.init();
    lookup_table = _lookup_table;
}

void irsensor::update()
{
    for (int x = 0; x < 8; x++)
    {
        adc_readings[x] = adc.read(x, SD);
    }
    get_distance();
}

int irsensor::max_position()
{
    float max_value = 0;
    int max_position = 0;
    for (int x = 0; x < 8; x++)
    {
        if (distance_readings[x] > max_value)
        {
            max_value = distance_readings[x];
            max_position = x;
        }
    }
    return max_position;
}

int irsensor::min_position()
{
    float min_value = 0;
    int min_position = 0;
    for (int x = 0; x < 8; x++)
    {
        if (distance_readings[x] < min_value)
        {
            min_value = distance_readings[x];
            min_position = x;
        }
    }
    return min_position;
}

float irsensor::max_distance()
{
    float max = 0;
    for (int x = 0; x < 8; x++)
    {
        if (distance_readings[x] > max)
        {
            max = distance_readings[x];
        }
    }
    return max;
}

float irsensor::min_distance()
{
    float min = MAX_VALUE;
    for (int x = 0; x < 8; x++)
    {
        if (distance_readings[x] < min)
        {
            min = distance_readings[x];
        }
    }
    return min;
}

float irsensor::weighted_mean()
{
    float t_sum = 0;
    float b_sum = 0;
    for (int x = 0; x < 8; x++)
    {
        t_sum = t_sum + distance_readings[x] * (x + 1);
        b_sum = b_sum + distance_readings[x];
    }
    return t_sum / b_sum;
}

float irsensor::inverse_weighted_mean()
{
    float t_sum = 0;
    float b_sum = 0;
    for (int x = 0; x < 8; x++)
    {
        t_sum = t_sum + (MAX_VALUE - distance_readings[x]) * (x + 1);
        b_sum = b_sum + (MAX_VALUE - distance_readings[x]);
    }
    return t_sum / b_sum;
}

float irsensor::mean()
{
    float t_sum = 0;
    for (int x = 0; x < 8; x++)
    {
        t_sum += distance_readings[x];
    }
    return t_sum / 8;
}

void irsensor::get_distance()
{
    int ind;  //indices in data array
    int flag; //boolean used for calculating distance

    int i, j;

    //calculating distances measured in sensor array
    for (i = 0; i < 8; i++)
    {

        flag = 0;
        ind = 0;

        //find corresponding indices in data array
        for (j = 0; j < ROW; j++)
        {

            if (lookup_table[j][i + 1] >= adc_readings[i])
            {

                ind = j;
                flag = 1;
                break;
            }
        }

        //calculate distance

        if (!flag) //if sensor measured distance is greater than values in data array, let sensor distance = 100
            distance_readings[i] = MAX_VALUE;

        else
        {

            //calculating slope and y-intercpet : y = mx + b
            int x2 = lookup_table[ind][i + 1];
            int y2 = lookup_table[ind][0];

            int x1 = lookup_table[ind - 1][i + 1];
            int y1 = lookup_table[ind - 1][0];

            float m = ((float)(y2 - y1)) / (x2 - x1);
            float b = y2 - m * x2;

            distance_readings[i] = (int)(m * adc_readings[i] + b);

            //set negative distances to zero
            if (distance_readings[i] < MIN_VALUE)
                distance_readings[i] = MIN_VALUE;
            else if (distance_readings[i] > MAX_VALUE)
                distance_readings[i] = MAX_VALUE;
        }
    }
}