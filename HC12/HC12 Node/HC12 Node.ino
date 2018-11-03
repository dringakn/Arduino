/*
 Name:		HC12_Node.ino
 Created:	11/2/2018 8:09:32 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:

*/

//#include <SoftwareSerial.h>
//SoftwareSerial HC12(0, 1); // HC-12 TX Pin, HC-12 RX Pin
const int SET = 4;    // Set pin attached at D4
const unsigned long BAUD = 1200;

const int MSEN_PWR = A3;
const int MSEN1 = A0;
const int MSEN2 = A1;
const int MSEN3 = A2;
const int LIGHT = A4;
const int LIGHT_PWR = 2;

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
	pinMode(SET, OUTPUT);
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(80);              // Require 80mSec to change data mode
	Serial.begin(BAUD);      // Terminal Baud
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(LIGHT_PWR, OUTPUT);
	pinMode(MSEN_PWR, OUTPUT);
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
	delay(100);
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
	digitalWrite(MSEN_PWR, HIGH);
	delay(5);  // Sensor power stablized
	ADCSRA |= (1 << 7); // Enable ADC
	float moist1_Val = fmap(analogRead(MSEN1), 1023, 0, 0, 100.0);
	float moist2_Val = fmap(analogRead(MSEN2), 1023, 0, 0, 100.0);
	float moist3_Val = fmap(analogRead(MSEN3), 1023, 0, 0, 100.0);
	ADCSRA &= ~(1 << 7); // Disable ADC
	digitalWrite(MSEN_PWR, LOW);

	digitalWrite(LIGHT_PWR, HIGH);
	delay(5);  // Sensor power stablized
	ADCSRA |= (1 << 7); // Enable ADC
	float light_Val = fmap(analogRead(LIGHT), 0, 1023, 0, 100);
	ADCSRA &= ~(1 << 7); // Disable ADC
	digitalWrite(LIGHT_PWR, LOW);

	HC12_Wakeup();

	Serial.println(String(cnt++) + " " + String(moist1_Val) + "% ," + String(moist2_Val) + "% ," + String(moist3_Val) + "% ," + String(light_Val) + "%");
	delay(2000); // Transmission to finish

	HC12_Sleep();
	delay(50);

	// Sleep for the specified time
	for (int i = 0; i < 20; i++) { // nx8Sec approximatly.
		MCUCR |= (3 << 5);  // Set both BODS and BODSE bits at the same time
		MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); // Then set the BODS bit and clear the BODSE bit at same tiem
		__asm__ __volatile__("sleep");
	}
}