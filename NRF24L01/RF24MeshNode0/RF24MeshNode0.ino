/*
 Name:		RF24MeshNode0.ino
 Created:	7/8/2018 3:25:49 PM
 Author:	ahmad.kamal
 License:	This Library is licensed under a GPLv3 License
 Purpose:	The purpose of this test program is to implement a basic master mesh node using
			NRF24L01 transciever.
			D1 = CE
			D2 = CS
			DX = IRQ
			D5 = SCK
			D6 = MISO
			D7 = MOSI
 */

#include <RF24Mesh.h>

struct dataPacket {
	float battVolt, temperature, lightIntensity, resistance;
};// 16 Bytes

struct settingsPacket {
	uint32_t txInterval;
};// 4 Bytes

const uint8_t NODEID = 0;		// Current node ID
const uint8_t CE = 7, CS = 8;	// NRF24L01 CE & CS Pins
RF24 radio(CE, CS);				// Harware communicaiton object: CE, CS
RF24Network network(radio);		// Network communicaiton object
RF24Mesh mesh(radio, network);	// Mesh network communication object
uint32_t currTime, prevTime;	// Timer book keeping
dataPacket dataPkt;				// Data Packet recieved from Node
settingsPacket settingsPkt;		// Settings packet recieved from 
uint32_t fails, oks;

void RF24ISR(void) {
	bool txok, txfail, rxready;
	radio.whatHappened(txok, txfail, rxready);
	Serial.println(String(millis()) + ">>> RF24 IRQ" +
		", TX_Ok:" + String(txok) +
		", TX_Fail:" + String(txfail) +
		", RX_Ready:" + String(rxready)
	);
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);		// Initialize serial port
	mesh.setNodeID(NODEID);		// Set current node ID (0-255), 0 for master node
	Serial.println("Master:" + String(mesh.getNodeID()) + "[" + String(mesh.getAddress(NODEID)) + "]");	// Return the nodeID of the provided network address, -1 if not found.
	mesh.begin(97, RF24_1MBPS, 10000);	// Channel, Speed, Address renewel timeout
	//pinMode(D4, HIGH);			// NodeMCU LED
	//pinMode(D3, INPUT_PULLUP);	// Set IRQ pin as input with internal pullup enable
	//attachInterrupt(digitalPinToInterrupt(D3), RF24ISR, FALLING);
	prevTime = millis();
}

void serialEvent(void) {
	while (Serial.available())
	{
		uint8_t nid = tolower(Serial.read());
		switch (nid)
		{
		case 'a':
			nid = Serial.parseInt();
			Serial.println(mesh.write(mesh.getAddress(nid), 0, 'A', 0) ? "Data Request Sent" : "Data Request Failed");
			break;
		case 'b':
			nid = Serial.parseInt();
			settingsPkt.txInterval = Serial.parseFloat();
			Serial.println(mesh.write(mesh.getAddress(nid), &settingsPkt, 'B', sizeof(settingsPkt)) ? "Settings Sent" : "Settings Sent Failed");
			break;
		case 'c':
			break;
		case 'd':
			break;
		case 'e':
			break;
		case 'z':
			nid = Serial.parseInt();
			Serial.println(mesh.write(nid, 0, 'Z', 0) ? "Renew request sent" : "Renew request failed");
			break;
		default:
			break;
		}
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	mesh.update();				// Perodically call to keep the network alive
	mesh.DHCP();				// Automatic assignment of node addresses
	currTime = millis();
	// Process incoming packets
	while (network.available())
	{
		RF24NetworkHeader header;
		network.peek(header);	// Check the available packet
		if (mesh.getNodeID(header.from_node) < 0) {
			network.read(header, 0, 0);
			Serial.println(mesh.write(header.from_node, 0, 'Z', 0) ? "Renew request sent" : "Renew request failed");
		}
		else {
			switch (header.type)	// Packet type: 0-127=user, 128-255=system
			{
			case 'A':	// Data packet
				network.read(header, &dataPkt, sizeof(dataPkt));
				Serial.println(
					String(currTime) + ">>> NodeID:" + String(mesh.getNodeID(header.from_node)) + "[" + String(header.from_node) + "]" +
					", V:" + String(dataPkt.battVolt) +
					", T:" + String(dataPkt.temperature) +
					", L:" + String(dataPkt.lightIntensity) +
					", R:" + String(dataPkt.resistance)
				);
				break;
			default:	// Invalid packet
				network.read(header, 0, 0);
				break;
			}
		}
	}
	if (currTime - prevTime > 8000)
	{
		// One second has been elapsed
		prevTime = currTime;
		//digitalWrite(D4, !digitalRead(D4));
		// Display network nodes
		network.failures(&fails, &oks);
		Serial.println(String(currTime) + ">>> Total Nodes:" + String(mesh.addrListTop) + ", Tx Ok:" + String(oks) + ", Tx Fail:" + String(fails));
		//for (int i = 0; i < mesh.addrListTop; i++)
		//	Serial.println("NodeID:" + String(mesh.addrList[i].nodeID) + "[" + String(mesh.addrList[i].address) + "]");
		//Serial.println("NodeID:" + String(mesh.addrList[i].nodeID) + "[" + String(mesh.getAddress(mesh.addrList[i].address)) + "]");
	}
}
