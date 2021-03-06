/*
 Name:		BinarySemaphore.ino
 Created:	11/19/2017 11:32:32 AM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 */
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t semSerial;

TaskHandle_t tskhdlTest = NULL;
void taskTest(void* pvParam){
	while (true)
	{
		if (xSemaphoreTake(semSerial, pdMS_TO_TICKS(1000)) == pdTRUE){
			Serial.println("Semaphore acquired");
			xSemaphoreGive(semSerial);
		}
		else
		{
			Serial.println("Semaphore was not acquired");
		}
	}
	vTaskDelete(tskhdlTest);	// Shouldn't reach here!
}

void setup() {
	Serial.begin(115200);
	semSerial = xSemaphoreCreateBinary();
	if (semSerial != NULL)
	if (xSemaphoreGive(semSerial) == pdFALSE){
		Serial.println("Semaphore has not been already taken!");
	}
	xTaskCreate(taskTest, "taskTest", 128, NULL, 2, &tskhdlTest);
}

void loop() {

}
