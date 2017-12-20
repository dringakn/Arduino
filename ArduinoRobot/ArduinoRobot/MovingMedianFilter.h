/*
Name:		MovingMedianFilter.h
Created:	12/12/2017 10:05:56 AM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
*/

#ifndef _MOVINGMEDIANFILTER_h
#define _MOVINGMEDIANFILTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

typedef double filterType;

class MovingMedianFilter
{
 protected:
	 unsigned int winSize;				// Numbe of samples in the window
	 filterType* array;					// Array to hold previous contents
	 filterType* tempArray;				// Temporary array for sorting
	 filterType temp;					// Intermediate variable for swaping
	 filterType median;					// Previous median value
	 int i, j;							// Loop variables

 public:
	 MovingMedianFilter(int);
	 ~MovingMedianFilter();
	 unsigned int getWinSize();
	void init(int);
	filterType filter(filterType);
	void show();
};

#endif

