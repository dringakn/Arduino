/*
 Name:		HC12_MeshNetwork_TXNode.ino
 Created:	11/3/2018 10:52:31 AM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:
*/

#include "MeshNetwork.h"
#include <OneWire.h>
#include <DallasTemperature.h>

void setup() {
	devAddress = 1; // Current Node Address
	pinMode(SET, OUTPUT);
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(HC12_DATA_MODE_DELAY);// Require mSec to change data mode
	Serial.begin(BAUD);
	SP.begin(BAUD);      // Terminal Baud
	Serial.println("HC12 TXNode(" + String(devAddress) + ")[" + String(BAUD) + " 8-N-1]");
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
	currTime = millis();
	if ((currTime - prevTime) >= 4096) {
		prevTime = currTime;
		txPacket(0, '0' + devAddress, (unsigned char*)"Hello           ");
	}
	if (rxPacket()) {
		Serial.write(rxPkt.data, packetSize);
	}
}