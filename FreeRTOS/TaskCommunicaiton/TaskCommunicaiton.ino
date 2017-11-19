/*
 Name:		TaskCommunicaiton.ino
 Created:	11/19/2017 3:12:55 PM
 Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>
#include <queue.h>
//Set configUSE_QUEUE_SETS 1 in the configuration
QueueHandle_t queBuffer1 = NULL, queBuffer2 = NULL;
QueueSetHandle_t queSet = NULL;

TaskHandle_t tskhdlSender1 = NULL;
void taskSender1(void* pvParam){
	const char* const str = "Sender1";
	while (true)
	{
		xQueueSend(queBuffer1, &str, 0);	// Add string to queue 1
		vTaskDelay(100 / portTICK_PERIOD_MS);	// Wait for 100mSec
	}
}

TaskHandle_t tskhdlSender2 = NULL;
void taskSender2(void* pvParam){
	const char* const str = "Sender2";
	while (true)
	{
		xQueueSend(queBuffer2, &str,0);	
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}

TaskHandle_t tskhdlReciever = NULL;
void taskReciever(void* pvParam){
	QueueHandle_t queBuffer;
	char* str;
	while (true)
	{
		queBuffer = (QueueHandle_t)xQueueSelectFromSet(queSet, portMAX_DELAY);
		xQueueReceive(queBuffer, &str, 0);
		Serial.println(str);
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	queBuffer1 = xQueueCreate(1, sizeof(char*));
	queBuffer2 = xQueueCreate(1, sizeof(char*));
	queSet = xQueueCreateSet(2 * 1);	// 2 Queues each containing 1 element each
	xQueueAddToSet(queBuffer1, queSet);	// Add the first queue to the set
	xQueueAddToSet(queBuffer2, queSet);	// Add the second queue to the set
	xTaskCreate(taskSender1, "taskSender1", 128, NULL, 1, NULL);
	xTaskCreate(taskSender2, "taskSender2", 128, NULL, 1, NULL);
	xTaskCreate(taskReciever, "taskReciever", 128, NULL, 2, NULL);	// Reciever must have higher priority then sender
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
