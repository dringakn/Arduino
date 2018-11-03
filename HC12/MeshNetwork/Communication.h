/*
Name:		Communication.h
Created:	03 Nov 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#ifndef _COMMUNICATION_h
#define _COMMUNICATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Arduino_FreeRTOS.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "List.h"
#include <HardwareSerial.h>

// RTOS Utilities
#ifndef TIME_MS
#define TIME_MS(mSec) ((TickType_t)(mSec/portTICK_PERIOD_MS))
#endif
#ifndef ULONG_MAX
#define ULONG_MAX 0xFFFFFFFF
#endif

// System Constants
const unsigned char SET = 4;					// HC-12 SET Pin
const unsigned long BAUD = 2400;				// Communication baud rate
const unsigned int HC12_CMD_DELAY = 80;			// Command/Data mode switch delay
const unsigned char MAX_RETRIES = 5;			// Maximum number of retries for a query packet
const unsigned char HEADERSIZE = 14;			// Header frame size
const unsigned char DATASIZE = 16;				// Payload size
const unsigned char PACKETSIZE = HEADERSIZE + DATASIZE;	// Packet size
const unsigned char MAX_CHILDS = DATASIZE;		// Maximum number of node's childrens
const unsigned char MAX_PARENTS = DATASIZE;		// Maximum number of node's parent candidates
const unsigned char HEADER[2] = { '\r', '\n' };	// Packet header
const unsigned char FOOTER[2] = { '\r', '\n' };	// Packet footer
const unsigned long PARENT_TTL = 1 * 60 * 1000;	// Parent time to live checking

// Communicaiton packet types
enum PacketType{
	PACKET_TYPE_JOIN_REQUEST = 0,			// 0
	PACKET_TYPE_JOIN_ACK,					// 1
	PACKET_TYPE_DATA_REQUEST,				// 2
	PACKET_TYPE_DATA_ACK,					// 3
	PACKET_TYPE_SET_SAMPLE_TIME_REQUEST,	// 4
	PACKET_TYPE_SET_SAMPLE_TIME_ACK,		// 5
	PACKET_TYPE_SET_PARENT_REQUEST,			// 6
	PACKET_TYPE_SET_PARENT_ACK,				// 7
	PACKET_TYPE_PARENTS_ID,					// 8
	PACKET_TYPE_PARENTS_ID_ACK,				// 9
	PACKET_TYPE_PARENTS_HOPS,				// 10
	PACKET_TYPE_PARENTS_HOPS_ACK,			// 11
	PACKET_TYPE_CHILDS_ID,					// 12
	PACKET_TYPE_CHILDS_ID_ACK,				// 13
	PACKET_TYPE_CHILDS_HOPS,				// 14
	PACKET_TYPE_CHILDS_HOPS_ACK,			// 15
	PACKET_TYPE_BROADCAST = 255				// 255
};

#define UNPACKET
union unPacket {
	struct {
		unsigned char header1;
		unsigned char header2;
		unsigned char dstAddress;
		unsigned char srcAddress;
		unsigned char parent;
		unsigned char hops;
		unsigned char pktType;
		unsigned char pktID;
		unsigned long timeStamp;
		char data[DATASIZE];
		unsigned char footer1;
		unsigned char footer2;
	} frame;
	char data[PACKETSIZE];
};

class CommunicationClass
{
 protected:
	 struct element childNodes[MAX_CHILDS];				// List containg child node information
	 struct element parentNodes[MAX_PARENTS];			// List containing parents node information
	 HardwareSerial* serialPort;						// Serial port to be used

public:
	unsigned char devAddress;							// Current node address
	unsigned char devParent;							// Current node's parent
	unsigned char pktID;								// Packet ID [0-255]
	ListClass childs, parents;
	union unPacket txPkt, rxPkt;
	void init(unsigned char devID, unsigned char parentID, HardwareSerial* serialPort);
	void send(unsigned char dstID, unsigned char pktType, char data[]);
	void relayPacket(boolean bIncrementHops=true);
	void sendChildsID(unsigned char dstID);
	void sendChildsHOPS(unsigned char dstID);
	void sendParentsID(unsigned char dstID);
	void sendParentsHOPS(unsigned char dstID);
	boolean process(unsigned char data);
	void sleep(void);
};

#endif

