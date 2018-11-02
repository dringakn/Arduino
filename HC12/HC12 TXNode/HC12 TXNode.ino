/*
 Name:		HC12_TXNode.ino
 Created:	11/2/2018 8:29:07 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir
 Description:
*/

#include <SoftwareSerial.h>
SoftwareSerial HC12(12, 11); // HC-12 TX Pin, HC-12 RX Pin
const int SET = 2;
const unsigned long BAUD = 1200;

void setup() {
	pinMode(SET, OUTPUT);
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(80);              // Require 80mSec to change data mode
	HC12.begin(BAUD);        // Serial port to HC12
	Serial.begin(BAUD);      // Terminal Baud
	Serial.println("HC12 TXNode[" + String(BAUD) + " 8-N-1]");
	pinMode(LED_BUILTIN, OUTPUT);
}

void LED_Blink() {
	digitalWrite(LED_BUILTIN, HIGH);
	delay(125);
	digitalWrite(LED_BUILTIN, LOW);
	delay(125);
}
void HC12_Sleep() {
	digitalWrite(SET, LOW); // Set low to enter command mode
	delay(40);              // Require 40mSec to change command mode
	HC12.print("AT+SLEEP\r\n");
	Serial.print(HC12.readString());
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(80);              // Require 80mSec to change data mode, thus enter sleep mode
}

void HC12_Wakeup() {
	digitalWrite(SET, LOW); // Set low to enter command mode
	delay(40);              // Require 40mSec to change command mode
	HC12.print("AT\r\n");
	Serial.print(HC12.readString());
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(80);              // Require 80mSec to change data mode, thus enter sleep mode
}

char ch = 'A';

void loop() {
	HC12_Wakeup();
	while (HC12.available()) {        // If HC-12 has data
		Serial.write(HC12.read());      // Send the data to Serial monitor
	}
	while (Serial.available()) {      // If Serial monitor has data
		HC12.write(Serial.read());      // Send that data to HC-12
	}
	HC12.write(ch);                   // Send data automatically after a while
	Serial.write(ch);
	if (++ch > 'Z') {
		ch = 'A';
		HC12.println();
		Serial.println();
	}
	LED_Blink();
	HC12_Sleep();
	delay(1000);
}