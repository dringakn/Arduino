/*
Name:		Sensors.h
Created:	03 Nov 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#ifndef _SENSORS_h
#define _SENSORS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Communication.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Connection information
const int MSEN_PWR = A3;					// Moisture Sensor VCC pin
const int MSEN1 = A0;						// Moisture Sensor Elctrode-1 pin
const int MSEN2 = A1;						// Moisture Sensor Elctrode-2 pin
const int MSEN3 = A2;						// Moisture Sensor Elctrode-3 pin
const int LIGHT = A4;						// LDR VCC pin
const int LIGHT_PWR = 2;					// LDR VCC pin
const int TEMP_PWR = 10;					// DS18B20 VCC pin
const int TEMP = 9;							// DS18B20 data pin

// Senosr data packet
const unsigned char SENSOR_DATA_SIZE = 16;	// 8x2 = 16 Bytes
union unSensors {
	struct {
		unsigned int moistSensor[3];		// Moisture sensor resistance
		unsigned int pH;					// pH value x1000
		unsigned int internalTemperature;	// Internal temperature in milli degrees Celcius
		unsigned int externalTemperature;	// External temperature in milli degrees Celcius
		unsigned int light;					// LDR value in lux
		unsigned int batteryVoltage;		// Battery voltage in millivolts
	}sensor;
	unsigned char data[SENSOR_DATA_SIZE];
};

class SensorsClass
{
protected:
	static void taskSensors(void*);		// Sensors data acquisition task function handler

public:
	static TaskHandle_t tskSensors;		// Sensor task handle
	unsigned long sampleTime;			// Sensors sample delay
	unSensors sensors;					// Sensors values
	void init(unsigned long sampleTime);
};

#endif

