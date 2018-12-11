/*
 Name:		RF24Mesh_BasicNode.ino
 Created:	11/3/2018 5:51:19 PM
 Modified:	20 November 2018 12:37
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:
 */


#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
//#include "LowPower.h"
#include <string.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#define nodeID 1
#define CHANNEL 120
#define BAUD 115200
#define ONE_WIRE_BUS 7

RF24 radio(9, 10);				// Configure the chosen SPI CE,CS pins of NRF24L01
RF24Network network(radio);		// Configure the RF24 network
RF24Mesh mesh(radio, network);	// Configure the RF24 based mesh network
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temp_sensor(&oneWire);

typedef enum { wdt_16ms = 0, wdt_32ms, wdt_64ms, wdt_128ms, wdt_250ms, wdt_500ms, wdt_1s, wdt_2s, wdt_4s, wdt_8s } wdt_prescalar_e;

unsigned long awakeTime = 1500;
unsigned long sleepTimer = 0;
uint32_t networkTimer = 0;

double averageRodRes = 0;
double averageLDR = 0;

int ldrPin = A4;
float ldrValue = 0;
float resLDR = 0;
float resistanceLDR = 0;
float lux = 0;

int RodResPin = A2;
float RodResValue = 0;
float res = 0;
float resistance = 0;

int l = 0;
int r = 0;

float newVCC = 0;
float RodTemp = 0;

int TEMP_PWR = 8;
int LIGHT_PWR = 2;
int MSEN_PWR = A3;

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

long readVcc()
{
	long result;
	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	delay(2);
	ADCSRA |= _BV(ADSC);
	while (bit_is_set(ADCSRA, ADSC));
	result = ADCL;
	result |= ADCH << 8;
	result = 1126400L / result;
	return result;
}

void GetTemp(void)
{
	temp_sensor.requestTemperatures();
	RodTemp = temp_sensor.getTempCByIndex(0);
}

void GetLUX()
{
	averageLDR = 0;
	while (l < 100)
	{
		newVCC = double(readVcc()) / 1000;

		ldrValue = analogRead(ldrPin);
		ldrValue = (ldrValue / 1024)*newVCC;
		resLDR = ((newVCC - ldrValue) * 10000) / ldrValue;
		averageLDR = resLDR + averageLDR;
		l++;
	}
	l = 0;
	resistanceLDR = averageLDR / 100;
	lux = 134700 * exp(resistanceLDR*(-0.008881)) + 3517 * exp(resistanceLDR*(-0.001119));
}

void GetRodRes()
{
	averageRodRes = 0;
	while (r < 100)
	{
		newVCC = double(readVcc()) / 1000;

		RodResValue = analogRead(RodResPin);
		RodResValue = (RodResValue / 1024)*newVCC;
		res = (RodResValue * 10000) / (newVCC - RodResValue);
		averageRodRes = res + averageRodRes;
		r++;
	}
	r = 0;
	resistance = averageRodRes / 100;
}

void setup() {
	pinMode(TEMP_PWR, OUTPUT);
	pinMode(LIGHT_PWR, OUTPUT);
	pinMode(MSEN_PWR, OUTPUT);
	digitalWrite(TEMP_PWR, HIGH);
	digitalWrite(LIGHT_PWR, HIGH);
	digitalWrite(MSEN_PWR, HIGH);
	temp_sensor.begin();
	Serial.begin(BAUD);				// Set serial port baud rate
	mesh.setNodeID(nodeID);			// Set the nodeID to 0 for the master node
	Serial.println(F("Connecting to the mesh..."));
	mesh.begin(CHANNEL);			// Connect to the mesh (Frequency channel #)
	Serial.println(F("Connected"));
	//network.setup_watchdog(wdt_1s);  
	Serial.flush();
}

void loop() {
	//newVCC = double(readVcc()) / 1000;	// Read battery voltage
	//GetLUX();					// Read light intensity
	//GetRodRes();				// Read resistance of the sensor
	//GetTemp();					// Read temperture of the sensor
	mesh.update();				// Update the mesh packet
	while (network.available())	// Check available packet
	{
		RF24NetworkHeader header;	// Header of recieved packet
		nodeCMD cmd = { 0, 0 };		// Store recieved command packet
		network.read(header, &cmd, sizeof(cmd));// Read the recieved packet
		Serial.print("Received cmdID:" + String(cmd.cmdID) + ", cmdCounter:" + String(cmd.cmdCounter) + " from NodeID:" + String(header.from_node));

		if (cmd.cmdID == 999)	// If the recieved command id is as expected
		{
			nodeDATA nd = { 0, 0, 0, 0 };
			nd.voltage = newVCC;	// Load current sensor readings
			nd.resistanceRod = resistance;
			nd.lightsenstivity = lux;
			nd.temperature = RodTemp;
			if (!mesh.write(&nd, 'M', sizeof(nd)))
			{
				if (!mesh.checkConnection()) // Check the connection of the current node with the mesh network
				{
					Serial.println("Send failed and mesh connection broken. Releasing and renewing node address.");
					mesh.releaseAddress();
					mesh.renewAddress();
				}
				else
				{
					Serial.println("Send failed but Connection OK!!!");
				}
			}// Data packet sending failed
			else
			{
				Serial.print("Sent: ");
				Serial.println(String(nd.voltage) + " " + String(nd.resistanceRod) + " " + String(nd.lightsenstivity) + " " + String(nd.temperature));
			}// Data packet sent successfully
		}
	}// Process recieved packet

	if (!mesh.checkConnection())	// Check the connection of the current node with the mesh network
	{
		Serial.println("Connection broken, renewing address:" + String(mesh.getAddress(nodeID)));
		//mesh.releaseAddress();
		mesh.renewAddress(10000);
	}

}

