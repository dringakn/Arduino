// MovingAverageFilter.h

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

