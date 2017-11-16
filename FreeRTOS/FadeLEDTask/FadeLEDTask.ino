/*
 Name:		FadeLEDTask.ino
 Created:	11/16/2017 4:41:24 PM
 Author:	Ahmad kamal
 */

#include <Arduino_FreeRTOS.h>

TaskHandle_t tskhdlFadeLED;
void taskFadeLED(void* pvParam){
	char* str = (char*)pvParam;	// Cast the passed parameter in to required type
	Serial.println(str);		
	pinMode(LED_BUILTIN, OUTPUT);
	unsigned int uiIntensity = 0, uiStep = 1, uiLimit = 250 / portTICK_PERIOD_MS;
	while (true)
	{
		if (uiIntensity == uiLimit)uiStep = -1;
		else if (uiIntensity == 0)uiStep = 1;
		uiIntensity += uiStep;
		analogWrite(LED_BUILTIN, uiIntensity);
		//Serial.println(uiIntensity);
		vTaskDelay(1);
	}
	vTaskDelay(portMAX_DELAY);	// Maximum possible delay
	vTaskDelete(NULL);	// Should not reach here, self destruction
}
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	xTaskCreate(taskFadeLED, "taskFadeLED", 128, "booo", configMAX_PRIORITIES, &tskhdlFadeLED);
	xTaskCreate(taskFadeLED, "taskFadeLED", 128, "hooo", configTIMER_TASK_PRIORITY, &tskhdlFadeLED);
}

// the loop function runs over and over again until power down or reset
void loop() {

}
