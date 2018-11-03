/*
Name:		MeshNetworkGateWay.cpp
Created:	11/2/2018 9:08:29 PM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#include <MeshNetworkGateWay.h>

TaskHandle_t MeshNetworkGateWayClass::tskManageNetwork = NULL;		// Initialize task handler

void MeshNetworkGateWayClass::init(unsigned char devID, unsigned char parentID, HardwareSerial* serialPort)
{
	com.init(devID, parentID, serialPort);
	xTaskCreate(taskManageNetwork, "TaskManageNetwork", 128, this, 1, &tskManageNetwork);
}

void MeshNetworkGateWayClass::taskManageNetwork(void *param)
{
	TickType_t prevCtr = xTaskGetTickCount();
	MeshNetworkGateWayClass* gw = (MeshNetworkGateWayClass*)param;	// Pointer to current object
	unsigned char ucRetries = 0;							// Packet query retries counter
	struct element node;									// Node to be quried

	while (true)
	{
		if (gw->com.childs.counts == 0)
		{
			// There is no child in the network, start broadcasting join network packet
			do
			{
				// (Re)Send every BROADCAST_DELAY until JOIN request recieves.
				gw->com.send(PACKET_TYPE_BROADCAST, PACKET_TYPE_JOIN_REQUEST, gw->com.txPkt.frame.data);
			} while (xTaskNotifyWait(0x0, 0x0, NULL, TIME_MS(BROADCAST_DELAY)) == pdFALSE);// Check weather join response arrives before timeout
		}
		else{
			// At-least a child is present in the list, start managing the network
			for (int i = 0; i < gw->com.childs.counts; i++)
			{
				// Start query the childerns
				node = gw->com.childs.list[i];							// Send packet to destination address
				ucRetries = MAX_RETRIES;
				do
				{
					if (ucRetries-- == 0) {
						// Maximum number of retries reached before node response arrives, remove the node from child list
						gw->com.childs.remove(node);
						break;
					}
					// (Re)Send until packet response notification doesn't arrives or maximum retires reached.
					gw->com.send(node.id, PACKET_TYPE_DATA_REQUEST, gw->com.txPkt.frame.data);	// Get the address of the node
				} while (xTaskNotifyWait(0x0, 0x0, NULL, TIME_MS(NODE_RETRY_DELAY)) == pdFALSE);	// Check weather recieve notificaiton arrives before timeout
				vTaskDelayUntil(&prevCtr, TIME_MS(NODE_QUERY_DELAY));// Wait for node turn
			}
		}
	}
	vTaskDelete(tskManageNetwork);		// Delete the task, should never reach here
}


