/*
Name:		MeshNetworkNode.cpp
Created:	11/2/2018 9:08:29 PM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#include <MeshNetworkNode.h>

TaskHandle_t MeshNetworkNodeClass::tskManageNode = NULL;		// Initialize task handler

void MeshNetworkNodeClass::init(unsigned char devID, unsigned char parentID, HardwareSerial* serialPort)
{
	bJoinedNetwork = false;
	com.init(devID, parentID, serialPort);
	xTaskCreate(taskManageNode, "TaskManageNode", 128, this, 1, &tskManageNode);
}

void MeshNetworkNodeClass::taskManageNode(void *param)
{
	TickType_t prevCtr = xTaskGetTickCount();
	MeshNetworkNodeClass* mn = (MeshNetworkNodeClass*)param;	// Pointer to communicaiton object
	while (true)
	{
		// Wait for the notificaiton from seriaEvent function.
		while (xTaskNotifyWait(0x0, 0x0, NULL, TIME_MS(PARENT_TTL)) == pdFALSE)
		{
			// No message has been arrrived from the parent node before the specified time, 
			// therefore, remove it from the parent list
			mn->com.parents.remove(mn->com.parents.list[0]);
			if (mn->com.parents.counts > 0)
			{
				// If there are more parents in the list, get the next one
				mn->com.devParent = mn->com.parents.list[0].id;
			}
			else
			{
				// Otherwise, clear the bJoinedNetwork flag
				mn->com.devParent = 0;
				mn->bJoinedNetwork = false;
			}
		}
	}
	vTaskDelete(tskManageNode);
}

void MeshNetworkNodeClass::processPacket(struct element node, SensorsClass* sen)
{
	if (!bJoinedNetwork)
	{
		// The node has not yet joined a network
		if (com.rxPkt.frame.dstAddress == com.devAddress)
		{
			if (com.rxPkt.frame.pktType == PACKET_TYPE_JOIN_ACK)
			{
				// The node got acknowledgement from parent
				if (com.parents.add(node)) {
					// Parent is added successfully, therefore, set the flag indicating network joined
					com.devParent = com.parents.list[0].id;
					bJoinedNetwork = true;
				}
			}
			xTaskNotifyGive(tskManageNode);	// Send a notificaiton to the network manager task to resume without further delay
		}
		else
		{
			// The recieved packet is for some other destination, send the source node the JOIN request
			com.send(node.id, PACKET_TYPE_JOIN_REQUEST, com.txPkt.frame.data);
		}
	}
	else
	{
		// The node has already joined a network
		if (com.rxPkt.frame.pktType == PACKET_TYPE_JOIN_REQUEST)
		{
			// The node has recieved a JOIN request from another
			if (com.parents.find(node) == 255) {
				// It is not present in the parents list, therefore, add it as child
				if (com.childs.add(node))
				{
					// Notify parent if successfully added as child
					com.send(com.devParent, PACKET_TYPE_JOIN_REQUEST, com.rxPkt.frame.data);
				}
			}
		}
		else if (com.rxPkt.frame.dstAddress == com.devAddress)
		{
			// The packet is destined for the current node
			switch (com.rxPkt.frame.pktType)
			{
			case PACKET_TYPE_PARENTS_ID:
				com.sendParentsID(com.devParent);
				break;
			case PACKET_TYPE_PARENTS_HOPS:
				com.sendParentsHOPS(com.devParent);
				break;
			case PACKET_TYPE_CHILDS_ID:
				com.sendChildsID(com.devParent);
				break;
			case PACKET_TYPE_CHILDS_HOPS:
				com.sendChildsHOPS(com.devParent);
				break;
			case PACKET_TYPE_DATA_REQUEST:
				com.send(com.devParent, PACKET_TYPE_DATA_ACK, sen->sensors.data);
				break;
			case PACKET_TYPE_SET_PARENT_REQUEST:
				com.send(com.devParent, PACKET_TYPE_SET_PARENT_ACK, com.rxPkt.frame.data);
				com.parents.list[0].id = com.rxPkt.frame.parent;
				com.parents.list[0].hops = 0;
				com.devParent = com.parents.list[0].id;
				if (com.parents.counts == 0)com.parents.counts++;
				bJoinedNetwork = true;
				break;
			case PACKET_TYPE_SET_SAMPLE_TIME_REQUEST:
				com.send(com.devParent, PACKET_TYPE_SET_SAMPLE_TIME_ACK, com.rxPkt.frame.data);
				break;
			default:
				break;
			}
			xTaskNotifyGive(tskManageNode);	// Send a notificaiton to the network manager task to resume without further delay
		}
		else
		{
			// The packet is destined for some other node in the network, 
			// check if it exist in the child/parent list
			struct element n = { com.rxPkt.frame.dstAddress, com.rxPkt.frame.hops };
			if (com.childs.find(n) != 255 || com.parents.find(n) != 255)
			{
				// Forward the packet to the destination node
				com.relayPacket();
			}
		}

	}

}