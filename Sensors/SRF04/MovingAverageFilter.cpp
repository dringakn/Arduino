#include "MovingAverageFilter.h"

void MovingAverageFilter::init(int nSamples)
{
	if (nSamples != winSize) {
		// The previous contents will be preserved after the call to realloc(...)
		array = (filterType*)realloc(array, nSamples * sizeof(filterType));
		for (i = winSize; i < nSamples; i++)
			array[i] = 0;
		winSize = nSamples;
		sum = 0;	// Recalculate the average
		for (i = winSize - 1; i >= 0; i--)
			sum += array[i];
		average = sum / winSize;
	}
}

MovingAverageFilter::MovingAverageFilter(int nSamples = 3)
{
	winSize = nSamples;
	array = (filterType*)malloc(nSamples * sizeof(filterType));
	for (i = 0; i < winSize; i++)
		array[i] = 0;
}

MovingAverageFilter::~MovingAverageFilter()
{
	free(array);
}

filterType MovingAverageFilter::filter(filterType data)
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

void MovingAverageFilter::show()
{
	for (i = 0; i < winSize; i++) {
		Serial.print(String(array[i]) + ' ');
	}
	Serial.println();
	Serial.println(average);
}

