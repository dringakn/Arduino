/*
 Name:		BasicTasks.ino
 Created:	11/16/2017 9:15:18 AM
 Author:	Ahmad kamal
*/

#include <Arduino_FreeRTOS.h>

TaskHandle_t tskhdlBlink;
void taskBlink(void*){
	pinMode(LED_BUILTIN, OUTPUT);
	while (true)
	{
		digitalWrite(LED_BUILTIN, HIGH);
		vTaskDelay(250 / portTICK_PERIOD_MS);
		digitalWrite(LED_BUILTIN, LOW);
		vTaskDelay(250 / portTICK_PERIOD_MS);
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	xTaskCreate(taskBlink, "taskBlink", 128, NULL, 2, &tskhdlBlink);
	Serial.begin(11500);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
