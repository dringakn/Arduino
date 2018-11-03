/*
Name:		MeshNetworkGateWay.h
Created:	03 Nov 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#ifndef _MESHNETWORKGATEWAY_h
#define _MESHNETWORKGATEWAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Communication.h>

const unsigned long BROADCAST_DELAY = 10000;	// Broadcast delay interval in mSec
const unsigned long NODE_QUERY_DELAY = 2000;	// Node query delay in mSec
const unsigned long NODE_RETRY_DELAY = 2000;	// Node query retray delay in mSec

class MeshNetworkGateWayClass
{
private:
	static void taskManageNetwork(void*);		// Network manager task function handler

public:
	static TaskHandle_t tskManageNetwork;		// Network manager task handle to bes used externally
	CommunicationClass com;						// Communicaiton object, public because process function is used externally in serial event
	void init(unsigned char devID, unsigned char parentID, HardwareSerial* serialPort);	// Initialize gatway node
};

#endif

