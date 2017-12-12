/*
 Name:		SRF04PinChangeInterrupt.ino
 Created:	12/12/2017 3:38:07 PM
 Author:	ahmad.kamal
			Interrupt on Pin Change (Arduino Mega 2560)
			Pins: 10, 11, 12, 13, 50, 51, 52, 53,
			A8(62), A9(63), A10(64), A11(65), A12(66), A13(67), A14(68), A15(69)
 */

#include "MovingMedianFilter.h"
#include "MovingMedianFilter.h"
#include <Arduino_FreeRTOS.h>		// Schedular
#include <event_groups.h>			// Event groups
#include <PinChangeInterrupt.h>		// Pin Change Interrupt

volatile unsigned long trigTime, echoTime;		// Trigger time and echoed time in uSec
const unsigned int ECHO1 = (1 << 0);			// Set when echo is recieved

EventGroupHandle_t evtgrpUltrasonic = NULL;		// Event group 
/*
Patch:
Add the following two lines in the "FreeRTOSConfig.h"
#define INCLUDE_xEventGroupSetBitFromISR 1
#define INCLUDE_xTimerPendFunctionCall 1
*/
void echoISR(void) {
	BaseType_t xStatus = pdFALSE;
	echoTime = micros();						// Current time when echo is recieved
	xEventGroupSetBitsFromISR(evtgrpUltrasonic, ECHO1, NULL);// Echo is recieved
}

TaskHandle_t tskhdlGetRange;
void taskGetRange(void* param) {
	const unsigned int ECHO_PIN = 10;
	const unsigned int TRIGGER_PIN = 11;
	const double soundVel = 270.0f * 100.0f / 2e6f; // Define the velocity of sound in cm/uSec
	const EventBits_t BITMASK = ECHO1;				// Create Bit Mask for the event
	EventBits_t eventUS;							// Recieved event bits
	float usDistance;								// Calculated distance
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT_PULLUP);
	attachPCINT(digitalPinToPCINT(ECHO_PIN), echoISR, FALLING);
	while (true)
	{
		digitalWrite(TRIGGER_PIN, HIGH);		// High to Low pulse on trigger pin will emitt the 
		digitalWrite(TRIGGER_PIN, LOW);			// brust (8) of ultrasound wave
		trigTime = micros();					// Record the current time when echo is triggered												
		eventUS = xEventGroupWaitBits(evtgrpUltrasonic, BITMASK, pdTRUE, pdFALSE, 3);// Wait 3x17mSec until before timeout
												// Reset the event flag after reading
		if (eventUS != 0) {						// Event(s) occured	
			if (eventUS&ECHO1)					// Echo1 has recieved
				usDistance = (echoTime - trigTime)*soundVel;	// Distance in centimeter
		}
		else {									// Timeout occured before pulse recieved
			usDistance = 555;					// Maximum value from the sensor
		}
		Serial.print(usDistance);			// Print the calculated distance
		Serial.print(' ');
		Serial.println(eventUS);			// Print the calculated distance
	}
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskGetRange, "SRF04", 128, NULL, 1, &tskhdlGetRange);
	evtgrpUltrasonic = xEventGroupCreate();
}

void loop() {

}
