/*
Name:		MovingMedianFilter.cpp
Created:	12/12/2017 10:05:56 AM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
*/

#include "MovingMedianFilter.h"

MovingMedianFilter::MovingMedianFilter(int nSamples=3)
{
	winSize = nSamples;
	array = (filterType*)malloc(nSamples * sizeof(filterType));
	tempArray = (filterType*)malloc(nSamples * sizeof(filterType));
	for (i = 0; i < winSize; i++)
		array[i] = tempArray[i] = 0;
}

MovingMedianFilter::~MovingMedianFilter()
{
	free(array);
	free(tempArray);
}

unsigned int MovingMedianFilter::getWinSize()
{
	return winSize;
}

void MovingMedianFilter::init(int nSamples)
{
	if (nSamples != winSize) {
		// The previous contents will be preserved after the call to realloc(...)
		array = (filterType*)realloc(array, nSamples * sizeof(filterType));
		tempArray = (filterType*)realloc(tempArray, nSamples * sizeof(filterType));
		for (i = winSize; i < nSamples; i++)
			array[i] = tempArray[i] = array[0];			// Copy recent value to new elements instead of 0
		winSize = nSamples;
		median = tempArray[(int)floor(winSize / 2)];	// Update the median
	}
}

// Moving window Median filtering algorithm
filterType MovingMedianFilter::filter(filterType data)
{
	// Instead of moving the array elements toward start of the array, shift them toward
	// the end becuase when using realloc to increase the size, previous values have to 
	// be re arranged.
	for (i = winSize-1; i > 0; i--) {
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

void MovingMedianFilter::show()
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

