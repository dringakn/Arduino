/*
 Name:		CriticalSection.ino
 Created:	11/19/2017 8:04:49 PM
 Author:	Ahmad kamal
 */

// the setup function runs once when you press reset or power the board
#include <Arduino_FreeRTOS.h>

TaskHandle_t tskhdlTest;
void taskTest(void* pvParam){
	while (true)
	{
		taskENTER_CRITICAL();
		Serial.println("Booo");
		taskEXIT_CRITICAL();
	}
}
void setup() {
	Serial.begin(115200);
	xTaskCreate(taskTest, "taskTest", 128, NULL, 2, &tskhdlTest);
}

// the loop function runs over and over again until power down or reset
void loop() {

}
