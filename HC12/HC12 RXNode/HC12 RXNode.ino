/*
 Name:		HC12_RXNode.ino
 Created:	11/2/2018 8:27:57 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir
 Descirption:
*/

#include <SoftwareSerial.h>
SoftwareSerial HC12(12, 11); // HC-12 TX Pin, HC-12 RX Pin
const int SET = 2;
const unsigned long BAUD = 1200;

void setup() {
	pinMode(SET, OUTPUT);
	digitalWrite(SET, HIGH); // Set high to enter data mode
	HC12.begin(BAUD);        // Serial port to HC12
	Serial.begin(BAUD);      // Terminal Baud
	Serial.println("HC12 RXNode[" + String(BAUD) + " 8-N-1]");
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
	while (HC12.available()) {        // If HC-12 has data
		char ch = HC12.read();
		Serial.write(ch);      // Send the data to Serial monitor
		HC12.write(ch);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(125);
		digitalWrite(LED_BUILTIN, LOW);
		delay(125);
	}
	while (Serial.available()) {      // If Serial monitor has data
		HC12.write(Serial.read());      // Send that data to HC-12
	}
}