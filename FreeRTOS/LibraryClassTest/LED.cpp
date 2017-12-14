#include "LED.h"

QueueHandle_t LEDClass::queBuff = NULL;				// Initialize the static class member
EventGroupHandle_t LEDClass::evtgrpEvent = NULL;	// Initialize the static class member
TaskHandle_t LEDClass::tskhdlBlink = NULL;
TaskHandle_t LEDClass::tskhdlFade = NULL;

LEDClass::LEDClass(unsigned int pinNo = LED_BUILTIN, unsigned int delayMS = 250){
	_pinNo = pinNo;
	_delayMS = delayMS / portTICK_PERIOD_MS;
	pinMode(_pinNo, OUTPUT);
	queBuff = xQueueCreate(1, sizeof(unsigned int));
	evtgrpEvent = xEventGroupCreate();
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
	xEventGroupSetBits(evtgrpEvent, EVENT1);
}

void LEDClass::fade(unsigned int delayMS){
	_delayMS = delayMS / portTICK_PERIOD_MS;
	//xQueueSendToBack(queBuff, &_delayMS, 0);
	xQueueSendToBackFromISR(queBuff, &_delayMS, pdFALSE);
	vTaskSuspend(tskhdlBlink);
	vTaskResume(tskhdlFade);
	xEventGroupSetBits(evtgrpEvent, EVENT2);
}

void LEDClass::stop(void){
	vTaskSuspend(tskhdlBlink);
	vTaskSuspend(tskhdlFade);
	xEventGroupSetBits(evtgrpEvent, EVENT3);
}

void LEDClass::taskBlink(void* pvParam){
	const unsigned int pinNo = (unsigned int)pvParam;	// Typecast the input parameter to the desired value
	unsigned int delayMS = 250 / portTICK_PERIOD_MS;
	const EventBits_t eventMASK = EVENT1;// | EVENT2 | EVENT3;
	EventBits_t event;
	while (true)
	{
		event = xEventGroupWaitBits(evtgrpEvent, eventMASK, pdTRUE, pdFALSE, 0);
		//event = xEventGroupGetBits(evtgrpEvent);
		//xEventGroupClearBits(evtgrpEvent, EVENT1);
		if (event != 0){
			if (event&EVENT1)
				Serial.println("EVENT1 Occured");
			if (event&EVENT2)
				Serial.println("EVENT2 Occured");
			if (event&EVENT3)
				Serial.println("EVENT3 Occured");
		}
		if (xQueueReceive(queBuff, &delayMS, 0) == pdTRUE){
			Serial.print("Blink: "); 
			Serial.println(delayMS);
		}
		digitalWrite(pinNo, HIGH);
		vTaskDelay(delayMS);
		digitalWrite(pinNo, LOW);
		vTaskDelay(delayMS);
	}
	vTaskDelete(tskhdlBlink);	// Should not reach here, self destruction
}

void LEDClass::taskFade(void* pvParam){
	const unsigned int pinNo = (unsigned int)pvParam;	// Typecast the input parameter to the desired value
	unsigned int delayMS = 250 / portTICK_PERIOD_MS;
	unsigned int uiIntensity = 0, uiStep = 1;
	const EventBits_t eventMASK = EVENT2;// | EVENT2 | EVENT3;
	EventBits_t event;
	while (true)
	{
		event = xEventGroupWaitBits(evtgrpEvent, eventMASK, pdTRUE, pdFALSE, 0);
		//event = xEventGroupGetBits(evtgrpEvent);
		if (event != 0){
			if (event&EVENT1)
				Serial.println("EVENT1 Occured");
			if (event&EVENT2)
				Serial.println("EVENT2 Occured");
			if (event&EVENT3)
				Serial.println("EVENT3 Occured");
		}
		if (xQueueReceive(queBuff, &delayMS, 0) == pdTRUE){
			Serial.print("Fade: "); 
			Serial.println(delayMS);
		}
		if (uiIntensity == delayMS)uiStep = -1;
		else if (uiIntensity == 0)uiStep = 1;
		uiIntensity += uiStep;
		analogWrite(pinNo, map(uiIntensity, 0, delayMS, 0, 255));
		vTaskDelay(1);
	}
	vTaskDelete(tskhdlFade);	// Should not reach here, self destruction
}
