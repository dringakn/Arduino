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

template<typename T> 
class MovingMedianFilter
{
 protected:
	 unsigned int winSize;		// Numbe of samples in the window
	 T* array;					// Array to hold previous contents
	 T* tempArray;				// Temporary array for sorting
	 T temp;					// Intermediate variable for swaping
	 T median;					// Previous median value
	 int i, j;					// Loop variables

 public:
	 MovingMedianFilter(int);
	 ~MovingMedianFilter();
	 unsigned int getWinSize();
	void init(int);
	T filter(T);
	void show();
};

template<typename T>
MovingMedianFilter<T>::MovingMedianFilter(int nSamples = 3)
{
	winSize = nSamples;
	array = (T*)malloc(nSamples * sizeof(T));
	tempArray = (T*)malloc(nSamples * sizeof(T));
	for (i = 0; i < winSize; i++)
		array[i] = tempArray[i] = 0;
}

template<typename T>
MovingMedianFilter<T>::~MovingMedianFilter()
{
	free(array);
	free(tempArray);
}

template<typename T>
unsigned int MovingMedianFilter<T>::getWinSize()
{
	return winSize;
}

template<typename T>
void MovingMedianFilter<T>::init(int nSamples)
{
	if (nSamples != winSize) {
		// The previous contents will be preserved after the call to realloc(...)
		array = (T*)realloc(array, nSamples * sizeof(T));
		tempArray = (T*)realloc(tempArray, nSamples * sizeof(T));
		for (i = winSize; i < nSamples; i++)
			array[i] = tempArray[i] = array[0];			// Copy recent value to new elements instead of 0
		winSize = nSamples;
		median = tempArray[(int)floor(winSize / 2)];	// Update the median
	}
}

// Moving window Median filtering algorithm
template<typename T>
T MovingMedianFilter<T>::filter(T data)
{
	// Instead of moving the array elements toward start of the array, shift them toward
	// the end becuase when using realloc to increase the size, previous values have to 
	// be re arranged.
	for (i = winSize - 1; i > 0; i--) {
		array[i] = array[i - 1];	// Shift the array elements toward end of the array
		tempArray[i] = array[i];	// Copy the array elements for sorting
	}
	array[0] = data;				// Copy the new value as first element of the array	
	tempArray[0] = data;			// Copy the recent data into temporrary array for sorting

									// Bubble sort algorithm for sorting an floating point array in ascending order
	for (i = 0; i < winSize - 1; i++)
		for (j = 0; j < winSize - 1 - i; j++)
			if (tempArray[j + 1] < tempArray[j]) {	// Swap the two numbers for sorting (Ascending)
				temp = tempArray[j];				// Store the first number
				tempArray[j] = tempArray[j + 1];	// Replace the first number with the second
				tempArray[j + 1] = temp;			// Replace the second number with the stored copy
			}
	// If the sorted array is the same as original array then the result is not correct
	//for (i = 0; i < winSize; i++)	// 1 5 3 2 4 4 4
	//	array[i] = tempArray[i];

	median = tempArray[(int)floor(winSize / 2)];	// Return the middle element of the sorted array
	return median;
}

template<typename T>
void MovingMedianFilter<T>::show()
{
	for (i = 0; i < winSize; i++) {
		Serial.print(String(array[i]) + ' ');
	}
	Serial.println();
	for (i = 0; i < winSize; i++) {
		Serial.print(String(tempArray[i]) + ' ');
	}
	Serial.println();
	Serial.println(median);
}


#endif

