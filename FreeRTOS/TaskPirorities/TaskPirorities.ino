/*
Name:		TaskPirorities.ino
Created:	11/16/2017 11:17:32 PM
Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>
#define configUSE_QUEUE_SETS 1

TaskHandle_t tskhdlHighPriorityTask;
void taskHighPriority(void* pvParam){
	static unsigned long ulCtr = 0;
	while (true)
	{
		Serial.print("H:"); Serial.println(ulCtr++);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

TaskHandle_t tskhdlMediumPriorityTask;
void taskMediumPriority(void* pvParam){
	static unsigned long ulCtr = 0;
	while (true)
	{
		Serial.print("M:"); Serial.println(ulCtr++);
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}

TaskHandle_t tskhdlLowPriorityTask;
void taskLowPriority(void* pvParam){
	static unsigned long ulCtr = 0;
	while (true)
	{
		Serial.print("L:"); Serial.println(ulCtr++);
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}

/* Idle hook functions MUST be called vApplicationIdleHook(), take no parameters,
and return void. */
void vApplicationIdleHook(void)
{
	static unsigned long ulCtr = 0;
	/* This hook function does nothing but increment a counter. */
	Serial.println(ulCtr++);
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	xTaskCreate(taskHighPriority, "taskHighPriority", 128, NULL, 2, &tskhdlHighPriorityTask);		//Priority = 2
	xTaskCreate(taskMediumPriority, "taskMediumPriority", 128, NULL, 2, &tskhdlMediumPriorityTask);	//Priority = 1
	xTaskCreate(taskLowPriority, "taskLowPriority", 128, NULL, 1, &tskhdlLowPriorityTask);			//Priority = 0
}

// the loop function runs over and over again until power down or reset
void loop() {
	
}
