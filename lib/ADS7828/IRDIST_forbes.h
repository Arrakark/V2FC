/*
	IRDIST.h
	Returns an array of distances sensed by the IR sensors
*/

#ifndef IRDIST_h
#define IRDIST_h

#define S_LEN 8
#define ROW 20
#define COL 9

class IRDIST
{

public:

	IRDIST(int arr[S_LEN], int data[ROW][COL],  int sensor[S_LEN]);
	int *readDist(int arr[S_LEN], int sensor[S_LEN], int data[ROW][COL]);

private:
	int _arr[S_LEN];
	int _data[ROW][COL];
	int _sensor[S_LEN];
};

#endif