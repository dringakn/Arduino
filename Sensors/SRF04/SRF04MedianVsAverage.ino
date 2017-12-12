/*
 Name:		SRF04MedianVsAverage.ino
 Created:	12/12/2017 10:05:56 AM
 Author:	ahmad.kamal
*/
#include <UltraDistSensor.h>
#include <Arduino_FreeRTOS.h>

// Swap the two numbers for sorting
void swap(int *x, int *y)
{
	int temp = *x;	// Store the first number
	*x = *y;			// Replace the first number with the second
	*y = temp;			// Replace the second number with the stored copy
}

// Bubble sort algorithm for sorting an floating point array in ascending order
void SortAssending(int *arr, int n)
{
	int i, j;
	int temp;
	for (i = 0; i < n-1; i++)
		for (j = 0; j < n-1-i; j++)
			if (arr[j+1] < arr[j])
				swap(&arr[j + 1], &arr[j]);
}

const unsigned int winSize = 25;	// Numbe of samples in the window

// Moving window Median filtering algorithm
float MovingMedianFilter(float data)
{
	static int array[winSize];		// Static array to hold previous contents
	static unsigned int i;			// Loop variable
	int tempArray[winSize];			// Temporary array for sorting
	for (i = 0; i < winSize - 1; i++) {
		array[i] = array[i + 1];	// Shift the array elements toward start of the array
		tempArray[i] = array[i];	// Copy the array elements for sorting
	}
	array[i] = data;				// Copy the new value as last element of the array	
	tempArray[i] = data;			// Copt the last element into temporrary array for sorting
	SortAssending(tempArray, winSize);
	return tempArray[(int)floor(winSize/2)];// Return the middle element of the sorted array
}

// Moving window Average filtering algorithm
float MovingAverageFilter(float data)
{
	static int array[winSize];		// Static array to hold previous contents
	static unsigned int i;			// Loop variable
	unsigned long sum = 0;			// Moving average counter
	for (i = 0; i < winSize - 1; i++) {
		array[i] = array[i + 1];	// Shift the array elements toward start of the array
		sum += array[i];			// Integrate values
	}
	array[i] = data;				// Copy the new value as last element of the array	
	sum += data;
	return (sum/winSize);			// Return the average of window elements
}

TaskHandle_t tskhdlGetRange;
void taskGetRange(void* parm)
{	
	// Connect the SRF04 Trigger and Echo wires to two of the IOPC pins
	const unsigned int ECHO_PIN = 10;
	const unsigned int TRIGGER_PIN = 11;

	UltraDistSensor us;
	us.attach(TRIGGER_PIN, ECHO_PIN, 20000);
	TickType_t prevTick = xTaskGetTickCount();
	int usDistance, usDistanceMedian, usDistanceAverage;
	while (true)
	{
		usDistance = us.distanceInCm();
		usDistanceMedian = MovingMedianFilter(usDistance);
		usDistanceAverage = MovingAverageFilter(usDistance);
		Serial.print(usDistance); Serial.print(',');
		Serial.print(usDistanceMedian); Serial.print(',');
		Serial.print(usDistanceAverage); Serial.println();
		analogWrite(LED_BUILTIN, map(usDistance,0,343,0,255));
		vTaskDelayUntil(&prevTick, 1);		// Fixed delay
	}
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskGetRange, "SRF04", 512, NULL, 1, &tskhdlGetRange);
}

void loop() {
}
