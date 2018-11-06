/*
 Name:		RF24Mesh_BasicGatewayNode.ino
 Created:	11/3/2018 5:59:32 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:
 */


#include <RF24Network.h>
#include <RF24.h>
#include <RF24Mesh.h>
#include <SPI.h>

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
uint8_t nodeID;					// NodeID
uint32_t ctr = 0;				// Command counter
int check = 0;
int queryNode = 1;
int j = 0;
int timeout[100];
int t = 0;
uint32_t displayTimer = 0;
uint32_t delayTimer = 0;
uint32_t delayTimer1 = 0;

void setup() {
	Serial.begin(9600);			// Set serial port baud rate
	mesh.setNodeID(0);			// Set the nodeID to 0 for the master node
	Serial.println(mesh.getNodeID()); // Get and print the current node ID
	mesh.begin();				// Connect to the mesh
}

void loop() {
	mesh.update();				// Update the mesh packet
	mesh.DHCP();				// Update the automatic network addressing
	nodeDATA nd;				// Node data packet

	if (network.available()) {	// Check available packet
		RF24NetworkHeader header;	// Header of recieved packet
		network.peek(header);		// Peek the recieved packet header
		switch (header.type) {
		case 'M':
			network.read(header, &nd, sizeof(nd));
			Serial.print("Received ");
			Serial.print("Voltage : ");
			Serial.print(nd.voltage);
			Serial.print(",  Temperature : ");
			Serial.print(nd.temperature);
			Serial.print(",  Light Senstivity : ");
			Serial.print(nd.lightsenstivity);
			Serial.print(",  Resistance : ");
			Serial.print(nd.resistanceRod);
			Serial.print("  from Node :    ");
			Serial.println(mesh.getNodeID(header.from_node));

			break;
		default:
			network.read(header, 0, 0);
			Serial.println(header.type);
			break;
		}
	}


	if (millis() - delayTimer > 1000)
	{
		delayTimer = millis();
		ctr++;
		nodeCMD cmd = { 999, ctr };
		for (int i = 0; i < mesh.addrListTop; i++)
		{
			if (mesh.addrList[i].nodeID == queryNode)
			{
				Serial.println(queryNode);

				RF24NetworkHeader header(mesh.addrList[i].address, OCT);

				if (network.write(header, &cmd, sizeof(cmd)))
				{
					Serial.println("Send OK");
					timeout[i] = 0;

				}
				else
				{

					Serial.println("Send Fail");
					timeout[i]++;
				}
				if (timeout[i] == 10)
				{
					Serial.print("Timeout for Node :");
					Serial.print(mesh.addrList[i].nodeID);
					Serial.println("   Removed!");
					timeout[i] = 0;
					t = i;
					while (t < mesh.addrListTop - 1)
					{
						mesh.addrList[t] = mesh.addrList[t + 1];
						t++;
					}
					mesh.addrListTop--;
					i--;
				}

			}


		}

	}

	if (millis() - displayTimer > 5000) {
		displayTimer = millis();
		Serial.println(" ");
		Serial.println(F("********Assigned Addresses********"));
		for (int i = 0; i < mesh.addrListTop; i++) {
			Serial.print("NodeID: ");
			Serial.print(mesh.addrList[i].nodeID);
			Serial.print(" RF24Network Address: 0");
			Serial.println(mesh.addrList[i].address, OCT);
		}
		Serial.println(F("**********************************"));

		queryNode = mesh.addrList[j].nodeID;
		j = (j + 1) % mesh.addrListTop;
	}
}