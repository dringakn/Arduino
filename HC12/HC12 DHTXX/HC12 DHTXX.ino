/*
 Name:		HC12_DHTXX.ino
 Created:	11/2/2018 8:12:17 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir
 Description: Install Adafruit_Unified_Sensor and Adafruit DHT library.

*/

//#include <SoftwareSerial.h>
//SoftwareSerial HC12(0, 1); // HC-12 TX Pin, HC-12 RX Pin

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            13         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
//#define DHTTYPE           DHT11     // DHT 11
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

const int SET = 4;    // Set pin attached at D4
const unsigned long BAUD = 1200;

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
	pinMode(SET, OUTPUT);
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(80);              // Require 80mSec to change data mode
	Serial.begin(BAUD);      // Terminal Baud
	dht.begin();
	sensor_t sensor;
	dht.temperature().getSensor(&sensor);
	dht.humidity().getSensor(&sensor);
	for (int i = 0; i < 20; i++) {
		pinMode(i, OUTPUT);
	};
	WDTCSR = 24;        // Setup Watchdog timer, Reset and enable WDE
	WDTCSR = 33;        // Set prescaler, eight seconds
	WDTCSR |= (1 << 6); // Enable Watchdog
	SMCR |= (1 << 2);   // Power Down Mode
	SMCR |= 1;          // Enable Sleep Mode
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
							//  HC12.print("AT+SLEEP\r\n");
	Serial.print("AT+SLEEP\r\n");
	Serial.print(Serial.readString());
	delay(500);
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(80);              // Require 80mSec to change data mode, thus enter sleep mode
}

void HC12_Wakeup() {
	digitalWrite(SET, LOW); // Set low to enter command mode
	delay(40);              // Require 40mSec to change command mode
							//  HC12.print("AT\r\n");
	Serial.print("AT\r\n");
	Serial.print(Serial.readString());
	delay(100);
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(80);              // Require 80mSec to change data mode, thus enter sleep mode
}

unsigned long cnt = 0;

void loop() {
	sensors_event_t event;
	dht.temperature().getEvent(&event);
	HC12_Wakeup();
	if (isnan(event.temperature)) {
		Serial.println("Error");
	}
	else {
		Serial.print("T: ");
		Serial.print(event.temperature);
		Serial.println(" *C");
	}
	// Get humidity event and print its value.
	dht.humidity().getEvent(&event);
	if (isnan(event.relative_humidity)) {
		Serial.println("Error");
	}
	else {
		Serial.print("H: ");
		Serial.print(event.relative_humidity);
		Serial.println("%");
	}
	delay(2000);

	HC12_Sleep();
	delay(500);

	// Sleep for the specified time
	for (int i = 0; i < 20; i++) { // nx8Sec approximatly.
		MCUCR |= (3 << 5);  // Set both BODS and BODSE bits at the same time
		MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); // Then set the BODS bit and clear the BODSE bit at same tiem
		__asm__ __volatile__("sleep");
	}
}