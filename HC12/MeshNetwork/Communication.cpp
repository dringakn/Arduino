/*
Name:		Communication.cpp
Created:	03 Nov 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#include "Communication.h"

void CommunicationClass::init(unsigned char devID, unsigned char parentID, HardwareSerial* sp)
{
	devAddress = devID;					// Store current node ID
	devParent = parentID;				// Store current node parent
	pktID = 0;							// Packet ID
	pinMode(SET, OUTPUT);				// Configure the mode pin of HC-12
	digitalWrite(SET, HIGH);			// Enter data mode to send data, HIGH=Data, LOW=Commands
	serialPort = sp;
	//vTaskDelay(TIME_MS(HC12_CMD_DELAY));// Wait for the data mode to be enabled
	serialPort->begin(BAUD);					// Configure the baud rate
	childs.init(childNodes, MAX_CHILDS);// Initialize the child nodes list
	parents.init(parentNodes, MAX_PARENTS);// Initialize the child nodes list
}

void CommunicationClass::send(unsigned char dstID, unsigned char pktType, char data[])
{
	txPkt.frame.header1 = HEADER[0];
	txPkt.frame.header2 = HEADER[1];
	txPkt.frame.dstAddress = dstID;			// The packet destination
	txPkt.frame.srcAddress = devAddress;	// The packet source
	txPkt.frame.parent = devParent;			// The parent of the current node
	txPkt.frame.hops = rxPkt.frame.hops;	// Recieve packet hops
	txPkt.frame.pktType = pktType;			// Packet command identifiar
	txPkt.frame.pktID = (devAddress == 0) ? pktID++ : rxPkt.frame.pktID;	// Send the recieve packet id
	txPkt.frame.timeStamp = xTaskGetTickCount() * portTICK_PERIOD_MS; // Recieving node time
	//memset(data, ' ', DATASIZE);	// Initilize the memory
	//sprintf(data, "%d-%d-%d-%d-%d-%d-%ul", txPkt.frame.dstAddress, txPkt.frame.srcAddress, txPkt.frame.parent, txPkt.frame.hops, txPkt.frame.pktType, txPkt.frame.pktID, txPkt.frame.timeStamp);
	//sprintf(data, "%d-%d-%d-%d", txPkt.frame.dstAddress, txPkt.frame.srcAddress, txPkt.frame.pktType, txPkt.frame.pktID);
	for (size_t i = 0; i < DATASIZE; i++)
		txPkt.frame.data[i] = data[i];
	txPkt.frame.footer1 = FOOTER[0];
	txPkt.frame.footer2 = FOOTER[1];
	serialPort->write(txPkt.data, PACKETSIZE);
}

void CommunicationClass::relayPacket(boolean bIncrementHops = true)
{
	if (bIncrementHops)
		rxPkt.frame.hops++;
	serialPort->write(rxPkt.data, PACKETSIZE);
}

void CommunicationClass::sendChildsID(unsigned char dstID)
{
	txPkt.frame.header1 = HEADER[0];
	txPkt.frame.header2 = HEADER[1];
	txPkt.frame.dstAddress = dstID;			// The packet destination
	txPkt.frame.srcAddress = devAddress;	// The packet source
	txPkt.frame.parent = devParent;			// The parent of the current node
	txPkt.frame.hops = rxPkt.frame.hops;	// Recieve packet hops
	txPkt.frame.pktType = PACKET_TYPE_CHILDS_ID_ACK;// Packet command identifiar
	txPkt.frame.pktID = (devAddress == 0) ? pktID++ : rxPkt.frame.pktID;// Send the recieve packet id
	txPkt.frame.timeStamp = xTaskGetTickCount() * portTICK_PERIOD_MS; // Recieving node time
	for (size_t i = 0; i < DATASIZE; i++)
		txPkt.frame.data[i] = childNodes[i].id;
	txPkt.frame.footer1 = FOOTER[0];
	txPkt.frame.footer2 = FOOTER[1];
	serialPort->write(txPkt.data, PACKETSIZE);
}

void CommunicationClass::sendChildsHOPS(unsigned char dstID)
{
	txPkt.frame.header1 = HEADER[0];
	txPkt.frame.header2 = HEADER[1];
	txPkt.frame.dstAddress = dstID;			// The packet destination
	txPkt.frame.srcAddress = devAddress;	// The packet source
	txPkt.frame.parent = devParent;			// The parent of the current node
	txPkt.frame.hops = rxPkt.frame.hops;	// Recieve packet hops
	txPkt.frame.pktType = PACKET_TYPE_CHILDS_HOPS_ACK;// Packet command identifiar
	txPkt.frame.pktID = (devAddress == 0) ? pktID++ : rxPkt.frame.pktID;// Send the recieve packet id
	txPkt.frame.timeStamp = xTaskGetTickCount() * portTICK_PERIOD_MS; // Recieving node time
	for (size_t i = 0; i < DATASIZE; i++)
		txPkt.frame.data[i] = childNodes[i].hops;
	txPkt.frame.footer1 = FOOTER[0];
	txPkt.frame.footer2 = FOOTER[1];
	serialPort->write(txPkt.data, PACKETSIZE);
}

void CommunicationClass::sendParentsID(unsigned char dstID)
{
	txPkt.frame.header1 = HEADER[0];
	txPkt.frame.header2 = HEADER[1];
	txPkt.frame.dstAddress = dstID;			// The packet destination
	txPkt.frame.srcAddress = devAddress;	// The packet source
	txPkt.frame.parent = devParent;			// The parent of the current node
	txPkt.frame.hops = rxPkt.frame.hops;	// Recieve packet hops
	txPkt.frame.pktType = PACKET_TYPE_PARENTS_ID_ACK;// Packet command identifiar
	txPkt.frame.pktID = (devAddress == 0) ? pktID++ : rxPkt.frame.pktID;// Send the recieve packet id
	txPkt.frame.timeStamp = xTaskGetTickCount() * portTICK_PERIOD_MS; // Recieving node time
	for (size_t i = 0; i < DATASIZE; i++)
		txPkt.frame.data[i] = parentNodes[i].id;
	txPkt.frame.footer1 = FOOTER[0];
	txPkt.frame.footer2 = FOOTER[1];
	serialPort->write(txPkt.data, PACKETSIZE);
}

void CommunicationClass::sendParentsHOPS(unsigned char dstID)
{
	txPkt.frame.header1 = HEADER[0];
	txPkt.frame.header2 = HEADER[1];
	txPkt.frame.dstAddress = dstID;			// The packet destination
	txPkt.frame.srcAddress = devAddress;	// The packet source
	txPkt.frame.parent = devParent;			// The parent of the current node
	txPkt.frame.hops = rxPkt.frame.hops;	// Recieve packet hops
	txPkt.frame.pktType = PACKET_TYPE_PARENTS_HOPS_ACK;// Packet command identifiar
	txPkt.frame.pktID = (devAddress == 0) ? pktID++ : rxPkt.frame.pktID;// Send the recieve packet id
	txPkt.frame.timeStamp = xTaskGetTickCount() * portTICK_PERIOD_MS; // Recieving node time
	for (size_t i = 0; i < DATASIZE; i++)
		txPkt.frame.data[i] = parentNodes[i].hops;
	txPkt.frame.footer1 = FOOTER[0];
	txPkt.frame.footer2 = FOOTER[1];
	serialPort->write(txPkt.data, PACKETSIZE);
}

boolean CommunicationClass::process(unsigned char data)
{
	for (size_t i = 1; i <= PACKETSIZE - 1; i++)
		rxPkt.data[i - 1] = rxPkt.data[i];
	rxPkt.data[PACKETSIZE - 1] = data;
	if (rxPkt.frame.header1 == HEADER[0] && rxPkt.frame.header2 == HEADER[1] &&
		rxPkt.frame.footer1 == FOOTER[0] && rxPkt.frame.footer2 == FOOTER[1])
	{
		return true;
	}
	return false;
}

void CommunicationClass::sleep(void)
{
	//Serial.flush();
	// SLEEP_MODE_IDLE, SLEEP_MODE_ADC, SLEEP_MODE_PWR_DOWN, SLEEP_MODE_PWR_SAVE, SLEEP_MODE_STANDBY, SLEEP_MODE_EXT_STANDBY
	set_sleep_mode(SLEEP_MODE_IDLE);
	power_all_disable();
	power_usart0_enable();
	portENTER_CRITICAL();
	sleep_enable();
	portEXIT_CRITICAL();
	sleep_cpu();	// Good night.
	sleep_reset();	// At wakeup. Reset the sleep_mode() faster than sleep_disable();
}
