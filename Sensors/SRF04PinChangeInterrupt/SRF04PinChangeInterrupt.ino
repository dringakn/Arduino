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

/* 
Interrupt on Pin Change (Arduino Mega 2560)
Pins: 10, 11, 12, 13, 50, 51, 52, 53, A8(62), A9(63), A10(64), A11(65), A12(66), A13(67), A14(68), A15(69)
*/
volatile unsigned long trigTime, echoTime;		// Trigger time and echoed time in uSec
volatile boolean bEchoRecieved = false;			// Set when echo is recieved

void echoISR(void) {
	echoTime = micros();						// Current time when echo is recieved
	bEchoRecieved = true;						// Echo is recieved
}

TaskHandle_t tskhdlGetRange;
void taskGetRange(void* param) {
	const unsigned int ECHO_PIN = 10;
	const unsigned int TRIGGER_PIN = 11;
	const double soundVel = 270.0f * 100.0f / 2e6f; // Define the velocity of sound in cm/uSec
	pinMode(TRIGGER_PIN, OUTPUT);				
	pinMode(ECHO_PIN, INPUT_PULLUP);			
	attachPCINT(digitalPinToPCINT(ECHO_PIN), echoISR, FALLING);
	float usDistance;							// Calculated distance
	while (true)
	{
		digitalWrite(TRIGGER_PIN, HIGH);		// High to Low pulse on trigger pin will emitt the 
		digitalWrite(TRIGGER_PIN, LOW);			// brust (8) of ultrasound wave
		trigTime = micros();					// Record the current time when echo is triggered
		bEchoRecieved = false;					// Reset the echo recieved flag
		while (!bEchoRecieved)					// Wait until flag is set
			vTaskDelay(1);
		usDistance = (echoTime - trigTime)*soundVel;	// Distance in centimeter
		vTaskDelay(1);	
		Serial.println(usDistance);				// Print the calculated distance
	}
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskGetRange, "SRF04", 128, NULL, 1, &tskhdlGetRange);
}

void loop() {
  
}
