/*
 Name:		Roboclaw_Library_Test.ino
 Created:	11/1/2018 6:26:50 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir
 Description:	This program is used to test the roboclaw communicaiton functionality using serial terminal.
				Roboclaw library requires SoftwareSerial library to be installed for serial port communication.
				The library version contains updated functionality of switch functions which isnot present in the
				original roboclaw library. This examples uses Serial1 of arduino mega, Pins TX1(18) and RX1(19), 
				for roboclaw communication while Serial is used for terminal communication.
Important Node: The S1 pin of the roboclaw is the recieve pin, therefore, to be connected to the TX pin of the 
				arduino. The S2 pin of the roboclaw is the transmit pin, therfore, must be connected
				to the RX pin of thr arduino. A pull-up resistor (1k) is required at the S2 pin of roboclaw.
*/
#include "RoboClaw.h"

RoboClaw roboclaw(&Serial1, 10000);

void setup() {
	Serial.begin(38400);	// Have you changed the terminal baudrate?
	roboclaw.begin(38400);	// Have you changed the roboclaw baudrate through software app?
	pinMode(LED_BUILTIN, OUTPUT);	// Initialize on-board LED
}

void loop() {
	while (Serial1.available())
	{
		// Read the roboclaw and forward the data to serial terminal
		Serial.write(Serial1.read());
	}
	while (Serial.available())
	{
		// Read the serial terminal and forward the data to roboclaw
		Serial1.write(Serial.read());
	}
	toggleLED(100);
}

void blinkLED(unsigned int ms) {
	digitalWrite(LED_BUILTIN, HIGH);
	delay(ms);
	digitalWrite(LED_BUILTIN, LOW);
	delay(ms);
}

void toggleLED(unsigned int ms) {
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
	delay(ms);
}