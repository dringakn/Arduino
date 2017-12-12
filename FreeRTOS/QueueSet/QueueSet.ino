/*
Name:		TaskCommunicaiton.ino
Created:	11/19/2017 3:12:55 PM
Author:	Ahmad kamal
*/

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

//Set configUSE_QUEUE_SETS 1 in the configuration
QueueHandle_t queBuffer1 = NULL, queBuffer2 = NULL;
QueueSetHandle_t queSet = NULL;
SemaphoreHandle_t semBinary = NULL;

TaskHandle_t tskhdlSender1 = NULL;
void taskSender1(void* pvParam){
	const char* const str = "Sender1";
	while (true)
	{
		xQueueSend(queBuffer1, &str, 0);	// Add string to queue 1
		vTaskDelay(1000 / portTICK_PERIOD_MS);	// Wait for 100mSec
	}
}

TaskHandle_t tskhdlSender2 = NULL;
void taskSender2(void* pvParam){
	const char* const str = "Sender2";
	while (true)
	{
		xQueueSend(queBuffer2, &str, 0);
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}

TaskHandle_t tskhdlReciever = NULL;
void taskReciever(void* pvParam){
	QueueSetMemberHandle_t queMember;
	char* str;
	while (true)
	{
		queMember = xQueueSelectFromSet(queSet, portMAX_DELAY);
		if (queMember == NULL){
			// Time out occured
			Serial.println("QueSet: Timeout");
		}
		else if (queMember == queBuffer1)
		{
			xQueueReceive(queBuffer1, &str, 0);
			Serial.println(str);
		}
		else if (queMember == queBuffer2)
		{
			xQueueReceive(queBuffer2, &str, 0);
			Serial.println(str);
		}
		else if (queMember == semBinary)
		{
			xSemaphoreTake(semBinary, 0);
			xSemaphoreGive(semBinary);
		}
	}
}

void setup() {
	Serial.begin(115200);
	queBuffer1 = xQueueCreate(1, sizeof(char*));
	queBuffer2 = xQueueCreate(1, sizeof(char*));
	semBinary = xSemaphoreCreateBinary();
	queSet = xQueueCreateSet(2 * 1+1);	// 2 Queues each containing 1 element each and one element Binary semaphore
	xQueueAddToSet(queBuffer1, queSet);	// Add the first queue to the set
	xQueueAddToSet(queBuffer2, queSet);	// Add the second queue to the set
	xQueueAddToSet(semBinary, queSet);	// Add the binary semaphore to the set
	xTaskCreate(taskSender1, "taskSender1", 128, NULL, 1, NULL);
	xTaskCreate(taskSender2, "taskSender2", 128, NULL, 1, NULL);
	xTaskCreate(taskReciever, "taskReciever", 128, NULL, 2, NULL);	// Reciever must have higher priority then sender
}

void loop() {

}
