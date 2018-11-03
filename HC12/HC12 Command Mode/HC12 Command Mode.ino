/*
 Name:		HC12_Command_Mode.ino
 Created:	11/2/2018 8:26:18 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:

*/

#include <SoftwareSerial.h>
SoftwareSerial HC12(12, 11); // HC-12 TX Pin, HC-12 RX Pin
const int SET = 2;
const unsigned long BAUD = 1200;

void setup() {
	Serial.begin(BAUD);           // Serial port to computer
	HC12.begin(BAUD);             // Serial port to HC12
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(SET, OUTPUT);           // Configure pin as output
	digitalWrite(SET, LOW);         // Set low to enter command mode
	delay(40);                      // Require 40mSec to switch to command mode
	Serial.println("<<< HC12 Comman Mode >>>");
	Serial.println("01- AT = Test Command");
	Serial.println("02- AT+BXXXX = Set baud rate {1200, 2400, 4800, 9600, 19200, 38400, 57600, 11200}");
	Serial.println("03- AT+CXXX = Set channel nummber [001-127] => 433.4MHz + XXX*400Khz");
	Serial.println("04- AT+FUX = Set mode [1-4]");
	Serial.println("05- AT+PX = Set mower level [1(-1dBm)-8(20dBm)]");
	Serial.println("06- AT+Ry = Get settings {B=baud, C=channel, F=mode, P=power, X=all}");
	Serial.println("07- AT+RX = Get all parameters");
	Serial.println("08- AT+UXYZ = Set Databits, Parity bits and Stop bits. {X=8, Y=N/O/E, Z=1(1),2(2),3(1.5)}");
	Serial.println("09- AT+V = Get version");
	Serial.println("10- AT+SLEEP = Enter sleep mode (22uA) after exiting command mode. Wakeup entering command mode");
	Serial.println("11- AT+DEFAULT = Restore factory settings");
}

void loop() {
	while (HC12.available()) {        // If HC-12 has data
		Serial.write(HC12.read());      // Send the data to Serial monitor
	}
	while (Serial.available()) {      // If Serial monitor has data
		HC12.write(Serial.read());      // Send that data to HC-12
	}
}

