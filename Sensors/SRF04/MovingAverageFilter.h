/*
Name:		MovingAverageFilter.h
Created:	12/12/2017 10:05:56 AM
Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
*/

#ifndef _MOVINGAVERAGEFILTER_h
#define _MOVINGAVERAGEFILTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

typedef int filterType;

class MovingAverageFilter
{
 protected:
	 unsigned int winSize;				// Numbe of samples in the window
	 filterType* array;					// Array to hold previous contents
	 filterType sum;					// Integration of the window samples
	 filterType average;				// Previous average value
	 int i;								// Loop variable

 public:
	void init(int);
	MovingAverageFilter(int);
	~MovingAverageFilter();
	filterType filter(filterType);
	void show();
};

#endif

