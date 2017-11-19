/*
 Name:		Mutex.ino
 Created:	11/19/2017 5:44:57 PM
 Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t mtxSerial;

TaskHandle_t tskhdlTest;
void taskTest(void* pvParam){
	while (true)
	{
		if (xSemaphoreTake(mtxSerial, pdMS_TO_TICKS(1000)) == pdTRUE){
			Serial.println("Semaphore acquired");
			//xSemaphoreGive(mtxSerial);
		}
		else
		{
			Serial.println("Semaphore was not acquired");
		}
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	mtxSerial = xSemaphoreCreateMutex();
	if (mtxSerial != NULL)
	if (xSemaphoreGive(mtxSerial) == pdFALSE){
		Serial.println("Semaphore has not been already taken!");
	}
	xTaskCreate(taskTest, "taskTest", 128, NULL, 2, &tskhdlTest);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
