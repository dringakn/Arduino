/*
 Name:		Roboclaw_Library_Test.ino
 Created:	11/1/2018 6:26:50 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir
 Description:	This program is used to test the roboclaw communicaiton functionality using serial terminal.
				Library requires to install SoftwareSerial Library for serial port communication.
				The following library contains updated functionality of switch functions not present in the
				original library
*/
#include "RoboClaw.h"

RoboClaw roboclaw(&Serial1, 10000);

void setup() {
	Serial.begin(57600);	// Serial terminal baudrate.
	roboclaw.begin(57600);	// Have you alrady changed the roboclaw baudrate through software app?
}

void serialEvent() {
	// Read the serial terminal and forward the data to roboclaw
	while (Serial.available())
	{
		Serial1.write(Serial.read());
	}
}

void serialEvent1() {
	// Read the roboclaw and forward the data to serial terminal
	while (Serial1.available())
	{
		Serial.write(Serial1.read());
	}
}

void loop() {

}
