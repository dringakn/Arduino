/*
Name:		Sensors.cpp
Created:	11/2/2018 9:08:29 PM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#include <Sensors.h>

TaskHandle_t SensorsClass::tskSensors = NULL;		// Initialize task handler

void SensorsClass::init(unsigned long sampleTime)
{
	this->sampleTime = sampleTime;					// Set the sample time
	xTaskCreate(taskSensors, "TaskSensors", 128, this, 1, &tskSensors);
}

void SensorsClass::taskSensors(void* param) {

	TickType_t prevCtr = xTaskGetTickCount();
	OneWire oneWire(TEMP);					// One wire library communicaiton
	DallasTemperature sensors(&oneWire);	// Pass our oneWire library reference to Dallas Temperature.
	SensorsClass* s = (SensorsClass*)param;	// Handle to the sensor class

	const int NSAMPLES = 100;
	const float K = (1023.0 * 1100);	// For calculations in volts
	unsigned char low, high;
	unsigned char ucRetries = 0;
	float result[3];

	pinMode(MSEN_PWR, OUTPUT);
	pinMode(LIGHT_PWR, OUTPUT);
	pinMode(TEMP_PWR, OUTPUT);

	sensors.begin();

	power_spi_disable();	// SPI is not used 
	power_timer2_disable();	// Timer0: millis(), Timer1: analogRead(), Timer2: tone()
	power_twi_disable();	// TWI is not used

	while (true)
	{
		power_adc_enable();
		// Read sensor resitance
		result[0] = 0;					// Reset the register for reuse
		result[1] = 0;					// Reset the register for reuse
		result[2] = 0;					// Reset the register for reuse
		digitalWrite(MSEN_PWR, HIGH);	// Enable power to the sensor
										//vTaskDelay(100);
		for (int i = 0; i < NSAMPLES; i++) {

			result[0] += analogRead(MSEN1);
			result[1] += analogRead(MSEN2);
			result[2] += analogRead(MSEN3);
		}
		digitalWrite(MSEN_PWR, LOW);	// Disable power to the sensor
		s->sensors.sensor.moistSensor[0] = result[0] / NSAMPLES;
		s->sensors.sensor.moistSensor[1] = result[1] / NSAMPLES;
		s->sensors.sensor.moistSensor[2] = result[2] / NSAMPLES;

		// Read pH sensor
		s->sensors.sensor.pH = s->sensors.sensor.moistSensor[0];	// Convert to pH Values

										// Read ambient light in lux
		result[0] = 0;					// Reset the register for reuse
		digitalWrite(LIGHT_PWR, HIGH);	// Enable power to the sensor
		for (int i = 0; i < NSAMPLES; i++)
			result[0] += analogRead(LIGHT);
		digitalWrite(LIGHT_PWR, LOW);	// Disable power to the sensor
		result[0] = 0.8 * (result[0] / NSAMPLES) - 40;
		s->sensors.sensor.light = (result[0] < 0) ? 0 : result[0];

		// Read internal battery voltage, Read temperature sensor against 1.1V reference 
		result[0] = 0;					// Reset the register for reuse
		ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
		for (int i = 0; i < NSAMPLES; i++) {
			ADCSRA |= _BV(ADSC); // Start conversion
			while (bit_is_set(ADCSRA, ADSC)); // measuring
			low = ADCL; // must read ADCL first - it then locks ADCH  
			high = ADCH; // unlocks both
			result[0] += ((high << 8) | low);// Calculate Vcc
		}
		s->sensors.sensor.batteryVoltage = K / (result[0] / NSAMPLES);

		// Read internal temperature
		result[0] = 0;					// Reset the register for reuse
		ADMUX = _BV(REFS0) | _BV(REFS1) | _BV(MUX3);
		for (int i = 0; i < NSAMPLES; i++) {
			ADCSRA |= _BV(ADSC); // Start conversion
			while (bit_is_set(ADCSRA, ADSC)); // measuring
			low = ADCL; // must read ADCL first - it then locks ADCH  
			high = ADCH; // unlocks both
			result[0] += ((high << 8) | low);
		}
		s->sensors.sensor.internalTemperature = ((1.0 * (result[0] / NSAMPLES)) + 6.0) * 1000.0;

		power_adc_disable();

		// Read external temperature
		digitalWrite(TEMP_PWR, HIGH);	// Enable power to the sensor
		sensors.requestTemperatures(); // Send the command to get temperatures		
		vTaskDelay(TIME_MS(1000));     // Allow power to be stablized
		s->sensors.sensor.externalTemperature = sensors.getTempCByIndex(0) * 1000.0;
		digitalWrite(TEMP_PWR, LOW);	// Disable power to the sensor
		vTaskDelayUntil(&prevCtr, TIME_MS(s->sampleTime));		// Wait for next sample
	}
	vTaskDelete(tskSensors);
}

SensorsClass Sensors;

