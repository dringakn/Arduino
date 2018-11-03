/*
Name:		MeshNetworkNode.h
Created:	03 Nov 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#ifndef _MESHNETWORKNODE_h
#define _MESHNETWORKNODE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Communication.h>
#include <Sensors.h>

class MeshNetworkNodeClass
{
private:
	static void taskManageNode(void*);			// Network manager task function handler

public:
	static TaskHandle_t tskManageNode;			// Network manager task handle to bes used externally
	boolean bJoinedNetwork;						// Flag indicating the network joined status
	CommunicationClass com;						// Communicaiton object, public because process function is used externally in serial event
	void init(unsigned char devID, unsigned char parentID, HardwareSerial* serialPort);	// Initialize gatway node
	void processPacket(struct element node, SensorsClass* sen);	// Incomming packets parser related to communication packets
};

#endif

