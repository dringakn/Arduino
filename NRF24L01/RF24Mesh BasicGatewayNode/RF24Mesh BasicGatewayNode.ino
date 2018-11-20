/*
 Name:		RF24Mesh_BasicGatewayNode.ino
 Created:	11/3/2018 5:59:32 PM
 Modified:	20 Nov 2018 12:33
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:
 */


#include "RF24Network.h"
#include "RF24.h"
#include "RF24Mesh.h"
#include <SPI.h>

#define CHANNEL 120
#define BAUD 115200

struct nodeCMD {				// Communication command packet
	unsigned long cmdID;
	unsigned long cmdCounter;
};

struct nodeDATA {				// Communication data packet
	float voltage;
	float lightsenstivity;
	float resistanceRod;
	float temperature;
};

RF24 radio(7, 8);				// Configure the chosen SPI CE,CS pins of NRF24L01
RF24Network network(radio);		// Configure the RF24 network
RF24Mesh mesh(radio, network);	// Configure the RF24 based mesh network
uint32_t cmdCounter = 0;		// Command counter
int queryNodeIdx = 0;			// Index of the next node in the network address list to be queried
int queryNode = 1;				// ID of the next node to be queried at queryNodeIdx 
int queryFailCounter[100];		// Array to count query failure for address range 1-100
uint32_t prevTimeDisplay = 0;	// Previous time stamp in millisecond for network address display loop
uint32_t prevTimeQuery = 0;		// Previous time stamp in millisecond for command query loop

void setup() {
	Serial.begin(BAUD);		// Set serial port baud rate
	mesh.setNodeID(0);			// Set the nodeID to 0 for the master node
	Serial.println(mesh.getNodeID()); // Get and print the current node ID
	mesh.begin(CHANNEL);			// Connect to the mesh (Frequency channel #)
}

void loop() {
	mesh.update();				// Update the mesh packet
	mesh.DHCP();				// Update the automatic network addressing

	if (network.available()) {	// Check available packet
		RF24NetworkHeader header;	// Header of recieved packet
		nodeDATA nd;				// Node data packet
		network.peek(header);		// Peek the recieved packet header
		switch (header.type) {
		case 'M':					// Recieved packet type
			network.read(header, &nd, sizeof(nd));	// Read the recieved packet
			Serial.print("Voltage : " + String(nd.voltage));
			Serial.print(",  Temperature : " + String(nd.temperature));
			Serial.print(",  Light Senstivity : " + String(nd.lightsenstivity));
			Serial.print(",  Resistance : " + String(nd.resistanceRod));
			Serial.print("  from NodeID :    " + String(mesh.getNodeID(header.from_node)));
			break;
		default:
			Serial.println("Invalid Packet Type:" + header.type);
			network.read(header, 0, 0);		// Discard the recieved packet 
			break;
		}
	}

	if (millis() - prevTimeQuery > 1000)	// Execute the following code after each elapsed second
	{
		prevTimeQuery = millis();
		nodeCMD cmd = { 999, cmdCounter++ };	// Create node command
		queryNode = mesh.addrList[queryNodeIdx].nodeID;	// The address of the node in the network address list to be queried
		for (int i = 0; i < mesh.addrListTop; i++)	// Search query node from the available network address list
		{
			if (mesh.addrList[i].nodeID == queryNode)	// If the node ID of a node in the network address list matches with node ID to be queried 
			{
				Serial.println("Query NodeID:" + String(queryNode));	// Print query node ID
				RF24NetworkHeader header(mesh.addrList[i].address, OCT);// Create header for the command packet
				if (network.write(header, &cmd, sizeof(cmd)))			// If the command packet is successfully sent
				{
					Serial.println("Query sent successfully.");
					queryFailCounter[i] = 0;							// Reset the query fail counter for current node
				}
				else
				{
					Serial.println("Query sent failed.");
					if (queryFailCounter[i]++ >= 10)					// If a certain number of quries fails for the current node
					{
						Serial.print("Removing NodeID:" + String(mesh.addrList[i].nodeID) + " after 10 failed queries");
						queryFailCounter[i] = 0;						// Reseting it's query failures counter value 
						for (int t = i; t < mesh.addrListTop - 1; t++)	// Manually remove the current node from the network address list
							mesh.addrList[t] = mesh.addrList[t + 1];	// Down shift the other nodes in the list  
						mesh.addrListTop--;								// Decrease the available number of nodes in the network address list
						i--;											// Check the new node at current address after resizing
					} // Certain number of queries failed
				}// Query failed
				break;													// Exit the query node address search
			}// Query node found
		}// Loop network addresses to find query node address
	}// One second interval

	if (millis() - prevTimeDisplay > 5000) {	// Execute the following code after every five elapsed seconds
		prevTimeDisplay = millis();
		Serial.println();
		Serial.println(F("********Assigned Addresses********"));
		for (int i = 0; i < mesh.addrListTop; i++) {
			Serial.print("NodeID: " + String(mesh.addrList[i].nodeID) + "Address: 0" + String(mesh.addrList[i].address, OCT));
		}
		Serial.println(F("**********************************"));
		if (mesh.addrListTop)
			queryNodeIdx = (queryNodeIdx + 1) % mesh.addrListTop;	// Increment the index of the next node to be queried in the network address list
	}
}
