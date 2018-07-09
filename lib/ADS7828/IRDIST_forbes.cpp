/*
	IRDIST.cpp
	Library for returning an array of distances sensed by the IR sensors
*/

#include "IRDIST.h"

#define S_LEN 8
#define ROW 20
#define COL 9

IRDIST::IRDIST(int arr[S_LEN], int data[ROW][COL], int sensor[S_LEN])
{

	_arr[S_LEN] = arr;
	_data[ROW][COL] = data;
	_sensor[S_LEN] = sensor;
}

int* IRDIST::readDist(int arr[S_LEN], int sensor[S_LEN], int data[ROW][COL])
{
	int ind; //indices in data array
	int flag; //boolean used for calculating distance

	int i, j;

	//calculating distances measured in sensor array
	for (i = 0; i < S_LEN; i++) {

		flag = 0;
		ind = 0;

		//find corresponding indices in data array
		for (j = 0; j < ROW; j++) {

			if (data[j][i + 1] >= sensor[i]){

				ind = j;
				flag = 1;
				break;
			}
		}

		//calculate distance

		if (!flag) //if sensor measured distance is greater than values in data array, let sensor distance = 100
			arr[i] = 30;

		else {

			//calculating slope and y-intercpet : y = mx + b
			int x2 = data[ind][i + 1];
			int y2 = data[ind][0];

			int x1 = data[ind - 1][i + 1];
			int y1 = data[ind - 1][0];

			float m = ((float)(y2 - y1)) / (x2 - x1);
			float b = y2 - m * x2;

			arr[i] = (int)(m * sensor[i] + b);

			//set negative distances to zero
			if (arr[i] < 0)
				arr[i] = 0;
			else if (arr[i] > 30)
				arr[i] = 30;
		}
	}

	return arr;
}