/*
Name:		MeshNetwork.h
Created:	03 Nov 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#ifndef MESHNETWORK_H

#include <AltSoftSerial.h>
#define SP HC12

const int SET = 10;			// HC-12 SET Pin
AltSoftSerial HC12;			//UNO: TXPin=9, RXPin=8, Connect HC-12 RXPin with Uno TXPin and vice versa

const unsigned long BAUD = 2400;				// HC-12 Baud Rate (bps)
const int LED_BLINK_DELAY = 250;				// milliseconds
const unsigned int HC12_CMD_MODE_DELAY = 80;	// milliseconds
const unsigned int HC12_DATA_MODE_DELAY = 80;	// milliseconds

const unsigned int NUMBER_OF_NODES = 0x07; 		// 0x03=4, 0x07=8, 0x0F=16
const unsigned int TIME_WINDOW_LENGTH = 11;     // 2^10=1024mSec, 2^11=2048mSec, 2^12=4096mSec

const unsigned char headerSize = 13;			// Header frame size
const unsigned char dataSize = 16;				// Payload size
const unsigned char packetSize = headerSize + dataSize;	// Packet size

volatile static unsigned char devAddress;		// Node address 
volatile static unsigned char channelID;		// Hardware Channel
volatile static unsigned char pktID; 			// Each packet gets an ID between 0-255
volatile static unsigned char syncNodeID;		// Reset value is 255, sync current node with another node with minimum id
volatile static bool bRelayPacket;				// Flag indicating status of packet to be relayed.
volatile static bool bSync;						// Flag to indicate the status of sync 

unsigned long prevTime, currTime;				// Time measurement
extern unsigned long timer0_millis; 			// millisecond counter
volatile static unsigned char NodePrevCmdID[NUMBER_OF_NODES];
#define UNPACKET
union unPacket {
	struct {
		unsigned char header1;
		unsigned char header2;
		unsigned char dstAddress;
		unsigned char srcAddress;
		unsigned char channelID;
		unsigned char cmdID;
		unsigned char pktID;
		unsigned long timeStamp;
		unsigned char data[dataSize];
		unsigned char footer1;
		unsigned char footer2;
	} frame;
	unsigned char data[packetSize];
} txPkt, rxPkt, rlyPkt;

unsigned int getTimeSlot() {
	// Divide the time in to 16(0xF) equal size windows and determine currently in which time
	// window we our progrom is based upon current time in milliseconds. It returns a time
	// slot number between 0-F. Each time slot window is 2^12mSec in length. When the time
	// slot window reaches to the maximum number (0xF) it rolls back to 0.
	return (unsigned int)((millis() >> TIME_WINDOW_LENGTH) & NUMBER_OF_NODES);
}

unsigned int getElapsedTimeWithinSlot() {
	// Calculate the time elapsed in milliseconds within each time window.
	unsigned long x = millis();
	return (unsigned int)(x - ((x >> TIME_WINDOW_LENGTH) << TIME_WINDOW_LENGTH));
}

void LED_Blink(unsigned char blinks) {
	for (int i = 0; i < blinks; i++) {
		digitalWrite(LED_BUILTIN, HIGH);
		delay(LED_BLINK_DELAY);
		digitalWrite(LED_BUILTIN, LOW);
		delay(LED_BLINK_DELAY);
	}
}

void displayPacket(union unPacket pkt, const char * str) {
	Serial.print("Node-" + String(devAddress) + " " + String(str) + " [" + String(millis()) + "]:");
	Serial.print(String(pkt.frame.dstAddress) + "-");
	Serial.print(String(pkt.frame.srcAddress) + "-");
	Serial.print(String(pkt.frame.channelID) + "-");
	Serial.print(String(pkt.frame.cmdID) + "-");
	Serial.print(String(pkt.frame.pktID) + "-");
	Serial.print(String(pkt.frame.timeStamp) + " > ");
	Serial.write(pkt.frame.data, dataSize);
	Serial.println();
}

void initializeMeshNetwork(unsigned char myNodeAddress, unsigned char chID) {
	devAddress = myNodeAddress; // Current Node Address
	channelID = chID;
	if (myNodeAddress == 0) {
		syncNodeID = 0;
		bSync = true;
	}
	else {
		syncNodeID = 255;
		bSync = false;
	}
	pktID = 0;
	bRelayPacket = false;
	for (int i = 0; i < NUMBER_OF_NODES; i++)
		NodePrevCmdID[i] = 0;
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(SET, OUTPUT);
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(HC12_DATA_MODE_DELAY);// Require mSec to change data mode
	SP.begin(BAUD);      // Terminal Baud
	prevTime = millis();
}

void txPacket(unsigned char dstID, unsigned char cmdID, unsigned char data[16]) {
	txPkt.frame.header1 = '\r';
	txPkt.frame.header2 = '\n';
	txPkt.frame.dstAddress = dstID;
	txPkt.frame.srcAddress = devAddress;
	txPkt.frame.channelID = channelID;
	txPkt.frame.cmdID = cmdID;
	txPkt.frame.pktID = pktID++;
	txPkt.frame.timeStamp = millis();
	for (size_t i = 0; i < dataSize; i++)
		txPkt.frame.data[i] = data[i];
	txPkt.frame.footer1 = '\r';
	txPkt.frame.footer2 = '\n';
	SP.write(txPkt.data, packetSize);
	displayPacket(txPkt, "TX");
	LED_Blink(3);
}
/*
	Check if the current time slot is equal to device address and the device sync flags
	is set. Furthermore sent the packet only if the sent flag is clear (i.e. send only once).
	Reset the sent flag when the timeslot changes.
*/
void nodeTimeSlot() {
	static bool bSent = false;
	if ((getTimeSlot() == devAddress) && bSync) {
		if (!bSent) {
			bSent = true;
			char buff[dataSize];
			sprintf(buff, "%03d-%03d-%08lu", devAddress, pktID, millis());
			if (devAddress == 0)
				txPacket(255, 255, buff);
			else
				txPacket(0, 0, buff);
		}
		if (bRelayPacket) {
			bRelayPacket = false;
			SP.write(rlyPkt.data, packetSize);
			LED_Blink(3);
		}
	}
	else {
		bSent = false;
	}
}
/*
	Parse the incoming data to filter out messages. Fetch the incoming data byte and shift left the buffer.
	If the two header bytes and two footer bytes matches then further process the recieved packet.
	All the nodes ultimately sync with the node 0. At the start each device is sync with device 255 except node 0.
	First the device checks wether the source ID of the recieved packet is smaller then or equal to the previous
	sync node ID and the recieved packet hasn't been generated by the node itself. Then the current node sync it's
	clock with the recieve node's time by calculating the node time slot and sets it sync flag to true.
*/
bool rxPacket() {
	bool bRecieved = false;
	while (SP.available()) {
		for (int i = 1; i <= packetSize - 1; i++)
			rxPkt.data[i - 1] = rxPkt.data[i];
		rxPkt.data[packetSize - 1] = SP.read();
		if (rxPkt.frame.header1 == '\r' && rxPkt.frame.header2 == '\n' &&
			rxPkt.frame.footer1 == '\r' && rxPkt.frame.footer2 == '\n') {
			if (rxPkt.frame.srcAddress <= syncNodeID && rxPkt.frame.srcAddress != devAddress) {
				// Sync time with the smallest node ID
				syncNodeID = rxPkt.frame.srcAddress;
				displayPacket(rxPkt, "SYN");	// Display before setting the timer
				timer0_millis = rxPkt.frame.timeStamp - (rxPkt.frame.srcAddress*(1 << TIME_WINDOW_LENGTH)); // Aproximated value
				bSync = true;
			}
			if (rxPkt.frame.srcAddress == devAddress) {
				// Discard loop packet
			}
			else if (rxPkt.frame.pktID > NodePrevCmdID[rxPkt.frame.srcAddress] || rxPkt.frame.pktID == 0) {
				// If the packet is not previously recieved
				NodePrevCmdID[rxPkt.frame.srcAddress] = rxPkt.frame.pktID;
				if (rxPkt.frame.dstAddress == devAddress) {
					// If the packet is destined to the current node
					bRecieved = true;
					displayPacket(rxPkt, "RX");
					LED_Blink(1);
				}
				else {
					// Packet should be relayed
					for (int i = 0; i <= packetSize; i++)
						rlyPkt.data[i] = rxPkt.data[i];
					bRelayPacket = true;
					displayPacket(rxPkt, "RLY");
					LED_Blink(2);
				}
			}// Process recieved packet 
		}// Packet recieved
	}// Available bytes
	return bRecieved;
}

void HC12_Sleep() {
	digitalWrite(SET, LOW); // Set low to enter command mode
	delay(HC12_CMD_MODE_DELAY);// Require mSec to change command mode
	SP.print("AT+SLEEP\r\n");
	SP.print(SP.readString());
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(HC12_DATA_MODE_DELAY);// Require mSec to change data mode, thus enter sleep mode
}

void HC12_Wakeup() {
	digitalWrite(SET, LOW); // Set low to enter command mode
	delay(HC12_CMD_MODE_DELAY);// Require mSec to change command mode
	SP.print("AT\r\n");
	SP.print(SP.readString());
	digitalWrite(SET, HIGH); // Set high to enter data mode
	delay(HC12_DATA_MODE_DELAY);// Require mSec to change data mode, thus enter sleep mode
}

#endif // !MESHNETWORK_H
