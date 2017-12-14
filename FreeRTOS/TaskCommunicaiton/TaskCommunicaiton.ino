/*
 Name:		TaskCommunicaiton.ino
 Created:	11/19/2017 3:12:55 PM
 Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>

TaskHandle_t tskhdlReciever = NULL;
void taskReciever(void* pvParam){
	uint32_t ulValue;
	while (true)
	{
		/*
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY):
			// Wait for the notification value to be non-zero
			// Block until notificaiton recieve from taskRx
			// if pdTRUE then decrement notificaiton value otherwise set to zero
		xTaskNotifyWait(ulBitsToClearOnEntry, ulBitsToClearOnExit, &ulValue, pdMS_TO_TICKS(x)): 
			// Wait for the pending notification
			// returns true if notification value is recieved, false if timeout occures
		*/
		ulValue = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	// 
		Serial.print("Rx:"); Serial.println(ulValue);
		vTaskDelay(5000 / portTICK_PERIOD_MS);	// Wait for 5000mSec
	}
	vTaskDelete(tskhdlReciever);	// Shouldn't reach here!
}

TaskHandle_t tskhdlSender = NULL;
void taskSender(void* pvParam){
	uint32_t ulPrevValue, ulValue = 5;
	while (true)
	{
		/*
		eNoAction: Notification is generated without using specified ulValue
		eSetBits:  Tasks Notification value is ored with the specifeid ulValue
		eIncrement: Increment the task's notification value
		eSetValueWithOverwrite: Set the task's notification value with ulValue
		eSetValueWithoutOverwrite: Task's notification value updated only if there is no pending event otherwise
		pdFALSE is returend.
		*/
		if (xTaskGenericNotify(tskhdlReciever, ulValue, eIncrement, &ulPrevValue) == pdTRUE) {
			Serial.print("Prev:"); Serial.println(ulPrevValue);
		}
		else {
			// The target task's notification value hasn't been updated because
			// a notification has been already pending
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);	// Wait for 1000mSec
	}
	vTaskDelete(tskhdlSender);	// Shouldn't reach here!
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskSender, "taskSender", 128, NULL, 1, &tskhdlSender);
	xTaskCreate(taskReciever, "taskReciever", 128, NULL, 1, &tskhdlReciever);	// Reciever must have higher priority then sender
}

void loop() {
  
}
