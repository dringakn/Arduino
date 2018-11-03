/*
 Name:		HC12_MeshNetwork_RLYNode.ino
 Created:	11/3/2018 11:27:04 AM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:
 */

#include "MeshNetwork.h"
#include <OneWire.h>
#include <DallasTemperature.h>

void setup() {
	//initializeMeshNetwork(3,1); // Current Node Address: COM42
	initializeMeshNetwork(2, 1); // Current Node Address: COM40
	//initializeMeshNetwork(1,1); // Current Node Address: COM39
	//initializeMeshNetwork(0,1); // Current Node Address: COM41
	Serial.begin(BAUD);
	Serial.println("HC12 TXNode(" + String(devAddress) + ")[" + String(BAUD) + " 8-N-1]");
}

void loop() {
	nodeTimeSlot();
	rxPacket();
}