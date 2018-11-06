/*
 Name:		RF24Mesh_BasicNode.ino
 Created:	11/3/2018 5:51:19 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:
 */


#include <RF24.h>
#include <RF24Network.h>
#include <RF24Mesh.h>
#include <SPI.h>
//#include <LowPower.h>
#include <string.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#define nodeID 1
#define ONE_WIRE_BUS 7


RF24 radio(9, 10);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

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

struct nodeDATA {
	float voltage;
	float lightsenstivity;
	float resistanceRod;
	float temperature;
};

struct payload_t {
	unsigned long ms;
	unsigned long counter;
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
	while (l<100)
	{
		newVCC = double(readVcc()) / 1000;

		ldrValue = analogRead(ldrPin);
		Serial.println(ldrValue);
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
	while (r<100)
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
void data() {
	newVCC = double(readVcc()) / 1000;
	GetLUX();
	GetRodRes();
	GetTemp();
}


void setup() {
	pinMode(TEMP_PWR, OUTPUT);
	pinMode(LIGHT_PWR, OUTPUT);
	pinMode(MSEN_PWR, OUTPUT);

	digitalWrite(TEMP_PWR, HIGH);
	digitalWrite(LIGHT_PWR, HIGH);
	digitalWrite(MSEN_PWR, HIGH);

	temp_sensor.begin();

	Serial.begin(9600);

	mesh.setNodeID(nodeID);
	// Connect to the mesh
	Serial.println(F("Connecting to the mesh..."));

	mesh.begin();
	Serial.println("Connection");
	//network.setup_watchdog(wdt_1s);  
}


bool timeout = false;
void loop() {

	payload_t payload = { 0,0 };
	nodeDATA nd = { 0,0,0,0 };
	mesh.update();
	data();
	nd.voltage = newVCC;
	nd.resistanceRod = resistance;
	nd.lightsenstivity = lux;
	nd.temperature = RodTemp;

	while (network.available())
	{
		timeout = false;
		RF24NetworkHeader header;

		network.read(header, &payload, sizeof(payload));
		Serial.print("Received packet #");
		Serial.print(payload.counter);
		Serial.print(" at ");
		Serial.println(payload.ms);

		// 999 represents query sent by the MASTER
		if (payload.ms == 999)
		{
			if (!mesh.write(&nd, 'M', sizeof(nd)))
			{
				if (!mesh.checkConnection())
				{

					Serial.println("Renewing Address");
					mesh.releaseAddress();
					mesh.renewAddress();
				}
				else
				{
					Serial.println("Send fail, Test OK");
				}
			}
			else
			{
				Serial.print("Send OK: ");
				Serial.print(nd.voltage); Serial.print("  ");
				Serial.print(nd.resistanceRod); Serial.print("  ");
				Serial.print(nd.lightsenstivity); Serial.print("  ");
				Serial.println(nd.temperature);
			}

		}
	}

	if (!mesh.checkConnection())
	{
		Serial.println("Renew");
		Serial.println(mesh.getAddress(nodeID));
		mesh.renewAddress();
	}
}





