/*
 Name:		TaskCommunicaiton.ino
 Created:	11/19/2017 3:12:55 PM
 Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>

TaskHandle_t tskhdlReciever = NULL;
void taskReciever(void* pvParam){
	while (true)
	{
		uint32_t notification = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		Serial.println(notification);
		vTaskDelay(5000 / portTICK_PERIOD_MS);	// Wait for 100mSec
	}
}

TaskHandle_t tskhdlSender = NULL;
void taskSender(void* pvParam){
	uint32_t prevNotfication, currNotificaiton = 5;
	while (true)
	{
		// eSetValueWithOverwrite, eNoAction, eIncrement, eSetValueWithoutOverwrite, eSetBits
		xTaskGenericNotify(tskhdlReciever, currNotificaiton, eIncrement, &prevNotfication);
		Serial.print("Prev:"); Serial.println(prevNotfication);
		vTaskDelay(1000 / portTICK_PERIOD_MS);	// Wait for 100mSec
	}
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskSender, "taskSender", 128, NULL, 1, &tskhdlSender);
	xTaskCreate(taskReciever, "taskReciever", 128, NULL, 1, &tskhdlReciever);	// Reciever must have higher priority then sender
}

void loop() {
  
}
