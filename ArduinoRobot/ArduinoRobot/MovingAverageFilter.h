/*
Name:		MovingAverageFilter.h
Created:	12/12/2017 10:05:56 AM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
*/

#ifndef _MOVINGAVERAGEFILTER_h
#define _MOVINGAVERAGEFILTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

template<typename T> 
class MovingAverageFilter
{
 protected:
	 unsigned int winSize;				// Numbe of samples in the window
	 T* array;					// Array to hold previous contents
	 T sum;					// Integration of the window samples
	 T average;				// Previous average value
	 int i;								// Loop variable

 public:
	void init(int);
	MovingAverageFilter(int);
	~MovingAverageFilter();
	unsigned int getWinSize();
	T filter(T);
	void show();
};

template<typename T>
void MovingAverageFilter<T>::init(int nSamples)
{
	if (nSamples != winSize) {
		// The previous contents will be preserved after the call to realloc(...)
		array = (T*)realloc(array, nSamples * sizeof(T));
		for (i = winSize; i < nSamples; i++)
			array[i] = array[0];				// Copy recent value to new elements instead of 0
		winSize = nSamples;
		sum = 0;								// Recalculate the average
		for (i = winSize - 1; i >= 0; i--)
			sum += array[i];
		average = sum / winSize;
	}
}

template<typename T>
MovingAverageFilter<T>::MovingAverageFilter(int nSamples = 3)
{
	winSize = nSamples;
	array = (T*)malloc(nSamples * sizeof(T));
	for (i = 0; i < winSize; i++)
		array[i] = 0;
}

template<typename T>
MovingAverageFilter<T>::~MovingAverageFilter()
{
	free(array);
}

template<typename T>
unsigned int MovingAverageFilter<T>::getWinSize()
{
	return winSize;
}

template<typename T>
T MovingAverageFilter<T>::filter(T data)
{
	// Instead of moving the array elements toward start of the array, shift them toward
	// the end becuase when using realloc to increase the size, previous values have to 
	// be re arranged.
	sum = 0;						// Reset the integration
	for (i = winSize - 1; i > 0; i--) {
		array[i] = array[i - 1];	// Shift the array elements toward end of the array
		sum += array[i];			// Integrate samples
	}
	array[0] = data;				// Copy the new value as first element of the array	
	sum += data;
	average = sum / winSize;
	return average;
}

template<typename T>
void MovingAverageFilter<T>::show()
{
	for (i = 0; i < winSize; i++) {
		Serial.print(String(array[i]) + ' ');
	}
	Serial.println();
	Serial.println(average);
}

#endif

