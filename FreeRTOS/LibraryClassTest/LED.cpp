#include "LED.h"

static QueueHandle_t LEDClass::queBuff = NULL;

LEDClass::LEDClass(unsigned int pinNo = LED_BUILTIN, unsigned int delayMS = 250){
	_pinNo = pinNo;
	_delayMS = delayMS / portTICK_PERIOD_MS;
	pinMode(_pinNo, OUTPUT);
	queBuff = xQueueCreate(1, sizeof(unsigned int));
	xTaskCreate(taskBlink, "taskBlink", 128, (void*)_pinNo, 1, &tskhdlBlink);
	xTaskCreate(taskFade, "taskFade", 128, (void*)_pinNo, 1, &tskhdlFade);
}

LEDClass::~LEDClass(){
	vTaskDelete(tskhdlBlink);
	vTaskDelete(tskhdlFade);
}

void LEDClass::blink(unsigned int delayMS){
	_delayMS = delayMS / portTICK_PERIOD_MS;
	//xQueueSendToBack(queBuff, &_delayMS, 0);
	xQueueSendToBackFromISR(queBuff, &_delayMS, pdFALSE);
	vTaskSuspend(tskhdlFade);
	vTaskResume(tskhdlBlink);
}

void LEDClass::fade(unsigned int delayMS){
	_delayMS = delayMS / portTICK_PERIOD_MS;
	//xQueueSendToBack(queBuff, &_delayMS, 0);
	xQueueSendToBackFromISR(queBuff, &_delayMS, pdFALSE);
	vTaskSuspend(tskhdlBlink);
	vTaskResume(tskhdlFade);
}

void LEDClass::stop(void){
	vTaskSuspend(tskhdlBlink);
	vTaskSuspend(tskhdlFade);
}

static void LEDClass::taskBlink(void* pvParam){
	const unsigned int pinNo = (unsigned int)pvParam;	// Typecast the input parameter to the desired value
	unsigned int delayMS = 12;
	while (true)
	{
		if (xQueueReceive(queBuff, &delayMS, 0) == pdTRUE){
			Serial.print("Blink: "); Serial.println(delayMS);
		}
		digitalWrite(pinNo, HIGH);
		vTaskDelay(delayMS);
		digitalWrite(pinNo, LOW);
		vTaskDelay(delayMS);
	}
	vTaskDelete(NULL);	// Should not reach here, self destruction
}

static void LEDClass::taskFade(void* pvParam){
	const unsigned int pinNo = (unsigned int)pvParam;	// Typecast the input parameter to the desired value
	unsigned int delayMS = 12;
	unsigned int uiIntensity = 0, uiStep = 1;
	while (true)
	{
		if (xQueueReceive(queBuff, &delayMS, 0) == pdTRUE){
			Serial.print("Fade: "); Serial.println(delayMS);
		}
		if (uiIntensity == delayMS)uiStep = -1;
		else if (uiIntensity == 0)uiStep = 1;
		uiIntensity += uiStep;
		analogWrite(pinNo, map(uiIntensity, 0, delayMS, 0, 255));
		vTaskDelay(1);
	}
	vTaskDelete(NULL);	// Should not reach here, self destruction
}
