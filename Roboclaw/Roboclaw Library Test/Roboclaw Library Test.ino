/*
 Name:		Roboclaw_Library_Test.ino
 Created:	11/1/2018 6:26:50 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
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

RoboClaw rc(&Serial1, 10000);
const unsigned char RCADD = 0x80;

void setup() {
	Serial.begin(38400);	// Have you changed the terminal baudrate?
	rc.begin(38400);		// Have you changed the roboclaw baudrate through software app?
	pinMode(LED_BUILTIN, OUTPUT);	// Initialize on-board LED
	WritePinFunction(RCADD, DEFAULTS_S3, DISABLED, DISABLED);
	//rc.WriteNVM(RCADD);
}

void loop() {
	ReadVersion(RCADD);
	ReadVoltageCurrentTemperature(RCADD);
	ReadPinFunction(RCADD);
	ReadEncoders(RCADD);
	Serial.println();
	//toggleLED(2500);
}

void ReadVersion(unsigned char address) {
	char buff[48];
	if (rc.ReadVersion(address, buff))
		Serial.print("Time:" + String(millis() / 1000.0) + "->" + String(buff));
	else
		Serial.println("ReadVersion failed.");
}

void ReadVoltageCurrentTemperature(unsigned char address) {
	uint16_t temp;
	int16_t temp1, temp2;
	bool valid;
	
	temp = rc.ReadLogicBatteryVoltage(address, &valid);
	if (valid)
		Serial.println("Time:" + String(millis() / 1000.0) + "->Logic Bat. Vol.:" + String(temp / 10.0));
	else
		Serial.println("ReadLogicBatteryVoltage failed.");
	
	temp = rc.ReadMainBatteryVoltage(address, &valid);
	if (valid)
		Serial.println("Time:" + String(millis() / 1000.0) + "->Main Bat. Vol.:" + String(temp / 10.0));
	else
		Serial.println("ReadMainBatteryVoltage failed.");
	
	if (rc.ReadCurrents(address, temp1, temp2))
		Serial.println("Time:" + String(millis() / 1000.0) + "->I1:" + String(temp1 / 100.0) + "\tI2:" + String(temp2 / 100.0));
	else
		Serial.println("ReadCurrents failed.");

	if (rc.ReadTemp(address, temp))
		Serial.println("Time:" + String(millis() / 1000.0) + "->Temperature:" + String(temp / 10.0));
	else
		Serial.println("ReadTemp failed.");
}

void ReadPinFunction(unsigned char address) {
	uint8_t temp1, temp2, temp3;
	if (rc.GetPinFunctions(address, temp1,temp2, temp3))
		Serial.println("Time:" + String(millis() / 1000.0) + "->S3Mode:" + String(temp1,HEX) + "\tS4Mode:" + String(temp2, HEX) + "\tS5Mode:" + String(temp3, HEX));
	else
		Serial.println("GetPinFunctions failed.");
}

void WritePinFunction(unsigned char address, uint8_t s3, uint8_t s4, uint8_t s5) {
	if (rc.SetPinFunctions(address, s3, s4, s5))
		Serial.println("Time:" + String(millis() / 1000.0) + "->S3Mode:" + String(s3, HEX) + "\tS4Mode:" + String(s4, HEX) + "\tS5Mode:" + String(s5, HEX));
	else
		Serial.println("SetPinFunction failed.");
}

void ReadEncoders(unsigned char address) {
	uint32_t temp1, temp2;
	if (rc.ReadEncoders(address, temp1, temp2))
		Serial.println("Time:" + String(millis() / 1000.0) + "->ENC1:" + String(temp1) + "\tENC2:" + String(temp2));
	else
		Serial.println("ReadEncoders failed.");
}

void toggleLED(unsigned int ms) {
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
	delay(ms);
}

void blinkLED(unsigned int ms) {
	toggleLED(ms);
	toggleLED(ms);
}

