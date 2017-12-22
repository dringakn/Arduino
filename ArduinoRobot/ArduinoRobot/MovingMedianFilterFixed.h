/*
Name:		MovingMedianFilterFixed.h
Created:	12/12/2017 10:05:56 AM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
*/

#ifndef _MOVINGMEDIANFILTERFIXED_h
#define _MOVINGMEDIANFILTERFIXED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

template<typename T> 
class MovingMedianFilterFixed
{
 protected:
	 static const unsigned int NSAMPLES = 10;	// Control memory size = 8+(2N+2)*sizeof(T)
	 T median;					// Previous median value
	 T array[NSAMPLES];			// Array to hold previous contents
	 T tempArray[NSAMPLES];		// Temporary array for sorting
	 T temp;					// Intermediate variable for swaping
	 unsigned int winSize;		// Numbe of samples in the window
	 unsigned int i, j;			// Loop variables

 public:
	 MovingMedianFilterFixed(int);
	 ~MovingMedianFilterFixed();
	 unsigned int getWinSize();
	void resize(int);
	T filter(T);
	void show();
};

template<typename T>
MovingMedianFilterFixed<T>::MovingMedianFilterFixed(int nSamples = NSAMPLES)
{
	if (nSamples > NSAMPLES)
		nSamples = NSAMPLES;
	winSize = nSamples;
	for (i = 0; i < winSize; i++)
		array[i] = tempArray[i] = 0;
}

template<typename T>
MovingMedianFilterFixed<T>::~MovingMedianFilterFixed()
{

}

template<typename T>
unsigned int MovingMedianFilterFixed<T>::getWinSize()
{
	return winSize;
}

template<typename T>
void MovingMedianFilterFixed<T>::resize(int newSize)
{
	if (newSize > NSAMPLES)
		newSize = NSAMPLES;
	if (newSize != winSize) {
		for (i = winSize; i < newSize; i++)
			array[i] = tempArray[i] = median;	// Copy recent median to new elements to preserve median
		winSize = newSize;
		median = tempArray[(int)floor(winSize / 2)];	// Update the median
	}
}

// Moving window Median filtering algorithm
template<typename T>
T MovingMedianFilterFixed<T>::filter(T data)
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

	// If the sorted array is the same as original array then the calculated median is not correct
	//for (i = 0; i < winSize; i++)	// 1 5 3 2 4 4 4
	//	array[i] = tempArray[i];

	median = tempArray[(int)floor(winSize / 2)];	// Return the middle element of the sorted array
	return median;
}

template<typename T>
void MovingMedianFilterFixed<T>::show()
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

