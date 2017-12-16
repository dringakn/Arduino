/*
 Name:		CriticalSection.ino
 Created:	11/19/2017 8:04:49 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 */

#include <Arduino_FreeRTOS.h>

TaskHandle_t tskhdlTest = NULL;
void taskTest(void* pvParam){
	while (true)
	{
		taskENTER_CRITICAL();
		Serial.println("Booo");
		taskEXIT_CRITICAL();
	}
	vTaskDelete(tskhdlTest);	// Shouldn't reach here!
}
void setup() {
	Serial.begin(115200);
	xTaskCreate(taskTest, "taskTest", 128, NULL, 2, &tskhdlTest);
}

void loop() {

}
