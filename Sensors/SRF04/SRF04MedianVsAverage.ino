/*
 Name:		SRF04MedianVsAverage.ino
 Created:	12/12/2017 10:05:56 AM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 */
#include "MovingAverageFilter.h"
#include "MovingMedianFilter.h"
#include <UltraDistSensor.h>
#include <Arduino_FreeRTOS.h>
#include "MovingMedianFilter.h"
#include "MovingAverageFilter.h"

MovingMedianFilter movMed(20);		// Moving Window Median Filter
MovingAverageFilter movAvg(20);		// Moving Window Average Filter

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
		usDistanceMedian = movMed.filter(usDistance);
		usDistanceAverage = movAvg.filter(usDistance);
		Serial.print(usDistance); Serial.print(',');
		Serial.print(usDistanceMedian); Serial.print(',');
		Serial.print(usDistanceAverage); Serial.println();
		analogWrite(LED_BUILTIN, map(usDistance,0,343,0,255));
		vTaskDelayUntil(&prevTick, 3);		// Fixed delay
	}
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskGetRange, "SRF04", 512, NULL, 1, &tskhdlGetRange);
	//movMed.filter(1); movMed.show();
	//movMed.filter(5); movMed.show();
	//movMed.filter(3); movMed.show();
	//movMed.filter(2); movMed.show();
	//movMed.filter(4); movMed.show();
	//movMed.filter(4); movMed.show();
	//movMed.filter(4); movMed.show();
	//movMed.init(9); movMed.show();
	//movMed.filter(1); movMed.show();
	//movMed.filter(1); movMed.show();
	//movMed.init(5); movMed.show();

	//movAvg.filter(1); movAvg.show();
	//movAvg.filter(5); movAvg.show();
	//movAvg.filter(3); movAvg.show();
	//movAvg.filter(2); movAvg.show();
	//movAvg.filter(4); movAvg.show();
	//movAvg.filter(4); movAvg.show();
	//movAvg.filter(4); movAvg.show();
	//movAvg.init(9); movAvg.show();
	//movAvg.filter(1); movAvg.show();
	//movAvg.filter(1); movAvg.show();
	//movAvg.init(5); movAvg.show();

	//while (1);
}

void loop() {
}
