/*
 Name:		BasicTasks.ino
 Created:	11/16/2017 9:15:18 AM
 Author:	Ahmad kamal
*/

#include <UltraDistSensor.h>
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

TaskHandle_t tskhdlReadUS;
void taskReadUS(void*){
	UltraDistSensor us;
	unsigned int uiDistance;
	us.attach(11, 10, 20000);
	vTaskSuspend(tskhdlBlink);
	while (true)
	{
		uiDistance = us.distanceInCm();
		Serial.println(uiDistance);
		analogWrite(LED_BUILTIN, constrain(uiDistance,0,250));
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

void setup() {
	xTaskCreate(taskBlink, "taskBlink", 128, NULL, 2, &tskhdlBlink);
	xTaskCreate(taskReadUS, "taskReadUS", 128, NULL, 2, &tskhdlReadUS);
	Serial.begin(115200);
}

void loop() {
  
}
