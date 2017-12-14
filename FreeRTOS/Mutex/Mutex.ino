/*
 Name:		Mutex.ino
 Created:	11/19/2017 5:44:57 PM
 Author:	Ahmad kamal
 */
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t mtxSerial;	// Declare a mutex for serial port access
void vPrintString(const char* str){
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE){
		Serial.print(pcTaskGetName(NULL)); Serial.print(" ("); Serial.print(millis()); Serial.print(") :");
		Serial.println(str);
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
	else{
		Serial.println("SerialPort: Semaphore was not acquired");
	}
}

void vPrintData(int a, int b, float c, double d){
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE){
		Serial.print(pcTaskGetName(NULL)); Serial.print(" ("); Serial.print(millis()); Serial.print(") :");
		Serial.print(a); Serial.print(' ');
		Serial.print(b); Serial.print(' ');
		Serial.print(c); Serial.print(' ');
		Serial.println(d); 
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
	else{
		Serial.println("SerialPort: Semaphore was not acquired");
	}
}

TaskHandle_t tskhdlTest = NULL;
void taskTest(void* pvParam){
	while (true)
	{
		vPrintString(pcTaskGetName(NULL));
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
	vTaskDelete(tskhdlTest);	// Shouldn't reach here!
}

void setup() {
	Serial.begin(115200);
	mtxSerial = xSemaphoreCreateMutex();
	if (mtxSerial != NULL)
	if (xSemaphoreGive(mtxSerial) == pdFALSE){
		Serial.println("Semaphore has not been already taken!");
	}
	xTaskCreate(taskTest, "taskTest", 128, NULL, 2, &tskhdlTest);
}

void loop() {
	vPrintString(pcTaskGetName(NULL));
	vPrintData(2, 3, PI, M_PI_2);
}
