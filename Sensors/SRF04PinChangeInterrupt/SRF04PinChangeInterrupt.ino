/*
 Name:		SRF04PinChangeInterrupt.ino
 Created:	12/12/2017 3:38:07 PM
 Author:	ahmad.kamal
*/

#include <Arduino_FreeRTOS.h>
//#include <PinChangeInterruptSettings.h>
//#include <PinChangeInterruptPins.h>
//#include <PinChangeInterruptBoards.h>
#include <PinChangeInterrupt.h>

const unsigned int ECHO_PIN = 10;
const unsigned int TRIGGER_PIN = 11;
const float soundVel = 270.0 * 100.0 / 2e6; // Define the velocity of sound in cm/uSec
volatile unsigned long trigTime, echoTime, pulseCounts;

void echoISR(void) {
	pulseCounts++;
	echoTime = micros();
}

TaskHandle_t tskhdlGetRange;
void taskGetRange(void*) {
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT_PULLUP); 
	attachPCINT(digitalPinToPCINT(ECHO_PIN), echoISR, FALLING);
	float usDistance;
	while (true)
	{
		digitalWrite(TRIGGER_PIN, HIGH);
		digitalWrite(TRIGGER_PIN, LOW);
		trigTime = micros();
		pulseCounts = 0;
		while (pulseCounts==0)
			vTaskDelay(1);
		usDistance = (echoTime - trigTime)*soundVel;	// Distance in centimeter
		vTaskDelay(1000/portTICK_PERIOD_MS);
		Serial.println(usDistance);
	}
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskGetRange, "SRF04", 128, NULL, 1, &tskhdlGetRange);
}

void loop() {
  
}
