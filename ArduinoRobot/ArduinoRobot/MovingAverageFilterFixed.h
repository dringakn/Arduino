/*
Name:		MovingAverageFilterFixed.h
Created:	12/12/2017 10:05:56 AM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
*/

#ifndef _MOVINGAVERAGEFILTERFIXED_h
#define _MOVINGAVERAGEFILTERFIXED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

template<typename T> 
class MovingAverageFilterFixed
{
 protected:
	 static const unsigned int NSAMPLES = 50;	// Control memory size = 8+(N+1)*sizeof(T)
	 T average;					// Previous average value
	 T array[NSAMPLES];			// Array to hold previous elements
	 unsigned int winSize;		// Numbe of samples in the window
	 int i;						// Loop variable, must not be 'unsigned int'
	 double sum;				// Integration of the window samples

 public:
	MovingAverageFilterFixed(unsigned int);
	~MovingAverageFilterFixed();
	void resize(unsigned int);
	unsigned int getWinSize();
	T filter(T);
	void show();
};

template<typename T>
MovingAverageFilterFixed<T>::MovingAverageFilterFixed(unsigned int nSamples = NSAMPLES)
{
	if (nSamples > NSAMPLES)
		nSamples = NSAMPLES;
	winSize = nSamples;
	for (i = 0; i < winSize; i++)
		array[i] = 0;
}

template<typename T>
MovingAverageFilterFixed<T>::~MovingAverageFilterFixed()
{

}

template<typename T>
void MovingAverageFilterFixed<T>::resize(unsigned int newSize)
{
	if (newSize > NSAMPLES)
		newSize = NSAMPLES;
	if (newSize != winSize) {		
		for (i = winSize; i < newSize; i++)
			array[i] = average;	 // Copy recent average to new elements to preserve average in case of increased size
		winSize = newSize;
	}
}

template<typename T>
unsigned int MovingAverageFilterFixed<T>::getWinSize()
{
	return winSize;
}

template<typename T>
T MovingAverageFilterFixed<T>::filter(T data)
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
void MovingAverageFilterFixed<T>::show()
{
	for (i = 0; i < winSize; i++) {
		Serial.print(String(array[i]) + ' ');
	}
	Serial.println();
	Serial.println(average);
}

#endif

