/*
 Name:		RF24MeshNode1.ino
 Created:	7/8/2018 3:26:15 PM
 Author:	ahmad.kamal
 License:	This Library is licensed under a GPLv3 License
 Purpose:	The purpose of this test program is to implement a mesh network device node using
			NRF24L01 transciever.
			D1 = CE
			D2 = CS
			DX = IRQ
			D5 = SCK
			D6 = MISO
			D7 = MOSI
*/

#include <RF24Mesh.h>
#include <EEPROMEx.h>
#include <EEPROMVar.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define MESH_NOMASTER

struct dataPacket {
	float battVolt, temperature, lightIntensity, resistance;
};// 16 Bytes

struct settingsPacket {
	uint32_t txInterval;
};// 4 Bytes

const uint16_t ADDRESS_SETTINGS_INTERVAL = 1;	// EEPROM address of txInterval Settings
const uint8_t NODEID = 1;		// Current node ID
const uint8_t CE = 7, CS = 8;	// NRF24L01 CE & CS Pins
const uint8_t LDR = A4, RES = A2, TEMP = 3;// LDR, Electrode and Temperture Sensor Pins
const uint8_t LDR_PWR = A3, RES_PWR = 2, TEMP_PWR = 8;// LDR, Electrode and Temperture Sensor Pins
OneWire oneWire(TEMP);			// One wire library interface
DallasTemperature tempSensor(&oneWire);// Dallas DS1820 Temperature Sensor library interface
RF24 radio(CE, CS);				// Harware communicaiton object: CE, CS
RF24Network network(radio);		// Network communicaiton object
RF24Mesh mesh(radio, network);	// Mesh network communication object
dataPacket dataPkt;				// Data Packet recieved from Node0
settingsPacket settingsPkt;		// Settings packet recieved from Node0

// the setup function runs once when you press reset or power the board
void setup() {
	settingsPkt.txInterval = EEPROM.readInt(ADDRESS_SETTINGS_INTERVAL);
	if (settingsPkt.txInterval == 0XFFFF) {
		settingsPkt.txInterval = 1;
		EEPROM.writeInt(ADDRESS_SETTINGS_INTERVAL, settingsPkt.txInterval);
	}
	pinMode(TEMP_PWR, OUTPUT);
	pinMode(LDR_PWR, OUTPUT);
	//pinMode(RES_PWR, OUTPUT);	// TODO: pin needs to be remapped
	tempSensor.begin();
	Serial.begin(9600);			// Initialize serial port
	Serial.println("Connecting to mesh...");
	Serial.flush();
	mesh.setNodeID(NODEID);		// Set current node ID (0-255), 0 for master node
	network.setup_watchdog(9);	// 0=16MSEC, 9=8SEC
	mesh.begin(97, RF24_1MBPS, 60000);	// Channel, Speed, Address renewel timeout
	Serial.println("My NodeID:" + String(mesh.getNodeID()) + "[" + String(mesh.getAddress(NODEID)) + "]" +
		", Tx Interval:" + String(settingsPkt.txInterval * 8) + "Sec"
	);	// Return the nodeID of the provided network address, -1 if not found.
}

void serialEvent(void) {
	while (Serial.available())
	{
		char ch1 = tolower(Serial.read());
		switch (ch1)
		{
		case 'a':
			break;
		case 's':
			break;
		case 'd':
			mesh.renewAddress();
			break;
		case 'f':
			break;
		default:
			break;
		}
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	mesh.update();				// Perodically call to keep the network alive
	if (!mesh.checkConnection()) {	// Check connection
		// If the master becomes unavailable, reacquire new address
		mesh.releaseAddress();
		mesh.renewAddress(60000);
	}
	// Process incoming packets		
	while (network.available())
	{
		RF24NetworkHeader header;
		network.peek(header);	// Check the available packet
		switch (header.type)	// Packet type: 0-127=user, 128-255=system
		{
		case 'A': // Data request
			network.read(header, 0, 0);
			sendSensorData();	// Send Sensor data
			break;
		case 'B': // Node settings
			network.read(header, &settingsPkt, sizeof(settingsPkt));
			Serial.println(
				String(millis()) + ">>> NodeID:" + String(mesh.getNodeID(header.from_node)) + "[" + String(header.from_node) + "]" +
				", T:" + String(settingsPkt.txInterval * 8) + " Sec"
			);
			EEPROM.writeInt(ADDRESS_SETTINGS_INTERVAL, settingsPkt.txInterval);
			break;
		case 'Z': // Renew address request
			network.read(header, 0, 0);
			mesh.releaseAddress();
			mesh.renewAddress(60000);
			break;
		default: // Invalid packet
			network.read(header, 0, 0);
			break;
		}
	}
	// Display network nodes
	Serial.println(String(millis()) + ">>>" + ", Conn. Status:" + String(mesh.checkConnection()) +
		", NodeID:" + String(mesh._nodeID) + "[" + String(mesh.mesh_address) + "]"
	);
	// Send Sensor data
	sendSensorData();
}

void sendSensorData(void) {
	dataPkt.battVolt = readVCC();
	dataPkt.lightIntensity = readLightIntensity();
	dataPkt.resistance = readResistance();
	dataPkt.temperature = readTemperature();
	if (mesh.write(0, &dataPkt, 'A', sizeof(dataPkt))) {
		Serial.println("Send Ok");
		Serial.flush();
		network.sleepNode(settingsPkt.txInterval, 0);
	}
	else {
		Serial.println("Send Fail");
		mesh.releaseAddress();
		mesh.renewAddress(60000);
	}
}

uint32_t readVCC(void) {
	uint32_t result, sum = 0;
	for (int i = 0; i < 10; i++)
	{
		ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
		delay(2);
		ADCSRA |= _BV(ADSC);
		while (bit_is_set(ADCSRA, ADSC));
		result = ADCL;
		result |= ADCH << 8;
		sum += (1126400L / result);
	}
	return sum / 10;
}

uint32_t readLightIntensity(void) {
	uint32_t sum = 0, r;
	for (int i = 0; i < 10; i++)
	{
		r = analogRead(LDR);
		sum += (10000.0*r / (1024.0 - r));
	}
	r = sum / 10;
	return (228400 * exp(-0.0207*r) + 4262 * exp(-0.002338*r));
}

uint32_t readResistance(void) {
	uint32_t sum = 0, r;
	for (int i = 0; i < 10; i++)
	{
		r = analogRead(RES);
		sum += (10000.0*r / (1024.0 - r));
	}
	return sum / 10;
}

uint32_t readTemperature(void) {
	tempSensor.requestTemperatures();
	return tempSensor.getTempCByIndex(0);
}