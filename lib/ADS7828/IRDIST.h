#ifndef IRDIST_H
#define IRDIST_H

#include "Arduino.h"

class IRDIST
{
public:
	IRDIST(unsigned char _address, int _lookup_table[][8], int measurements);
private:
    int lookup_table[][8];
};

#endif