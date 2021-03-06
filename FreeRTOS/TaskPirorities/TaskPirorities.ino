/*
Name:		TaskPirorities.ino
Created:	11/16/2017 11:17:32 PM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
*/
#include <Arduino_FreeRTOS.h>

/* Idle hook functions MUST be called vApplicationIdleHook(), take no parameters, and return void. */
void vApplicationIdleHook(void)
{
	static unsigned long ulCtr = 0;
	Serial.println(ulCtr++);/* This hook function does nothing but increment a counter. */
}

TaskHandle_t tskhdlHighPriorityTask = NULL;
void taskHighPriority(void* pvParam){
	static unsigned long ulCtr = 0;
	while (true)
	{
		Serial.print("H:"); Serial.println(ulCtr++);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
	vTaskDelete(tskhdlHighPriorityTask);	// Shouldn't reach here!
}

TaskHandle_t tskhdlMediumPriorityTask = NULL;
void taskMediumPriority(void* pvParam){
	static unsigned long ulCtr = 0;
	while (true)
	{
		Serial.print("M:"); Serial.println(ulCtr++);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(tskhdlMediumPriorityTask);	// Shouldn't reach here!
}

TaskHandle_t tskhdlLowPriorityTask = NULL;
void taskLowPriority(void* pvParam){
	static unsigned long ulCtr = 0;
	while (true)
	{
		Serial.print("L:"); Serial.println(ulCtr++);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(tskhdlLowPriorityTask);	// Shouldn't reach here!
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskHighPriority, "taskHighPriority", 128, NULL, 2, &tskhdlHighPriorityTask);		//Priority = 2
	xTaskCreate(taskMediumPriority, "taskMediumPriority", 128, NULL, 2, &tskhdlMediumPriorityTask);	//Priority = 2, 1
	xTaskCreate(taskLowPriority, "taskLowPriority", 128, NULL, 1, &tskhdlLowPriorityTask);			//Priority = 1
}

void loop() {
	
}
