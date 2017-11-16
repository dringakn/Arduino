/*
Name:		TaskPirorities.ino
Created:	11/16/2017 11:17:32 PM
Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>

TaskHandle_t tskhdlHighPriorityTask;
void taskHighPriority(void* pvParam){
	while (true)
	{
		Serial.println("H");
	}
}

TaskHandle_t tskhdlMediumPriorityTask;
void taskMediumPriority(void* pvParam){
	while (true)
	{
		Serial.println("M");
	}
}

TaskHandle_t tskhdlLowPriorityTask;
void taskLowPriority(void* pvParam){
	while (true)
	{
		Serial.println("L");
	}
}
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	xTaskCreate(taskHighPriority, "taskHighPriority", 128, NULL, configMAX_PRIORITIES, &tskhdlHighPriorityTask);	//Priority = 4
	xTaskCreate(taskMediumPriority, "taskMediumPriority", 128, NULL, configTIMER_TASK_PRIORITY, &tskhdlMediumPriorityTask);//Priority = 3
	xTaskCreate(taskLowPriority, "taskLowPriority", 128, NULL, configMAX_CO_ROUTINE_PRIORITIES, &tskhdlLowPriorityTask);//Priority = 2
}

// the loop function runs over and over again until power down or reset
void loop() {

}
