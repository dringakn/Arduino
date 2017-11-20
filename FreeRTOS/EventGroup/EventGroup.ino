/*
 Name:		EventGroup.ino
 Created:	11/19/2017 3:12:19 PM
 Author:	Ahmad kamal
 */
#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#define EVENT1 (1<<0)
#define EVENT2 (1<<1)
#define EVENT3 (1<<2)

EventGroupHandle_t evtgrpEvent = NULL;

TaskHandle_t tskhdlEvent1;
void taskEvent1(void* pvParam){
	while (true)
	{
		xEventGroupSetBits(evtgrpEvent, EVENT1);
		vTaskDelay((1 + (rand() % 10000)) / portTICK_PERIOD_MS);
	}
}

TaskHandle_t tskhdlEvent2;
void taskEvent2(void* pvParam){
	while (true)
	{
		xEventGroupSetBits(evtgrpEvent, EVENT2);
		vTaskDelay((1 + (rand() % 10000)) / portTICK_PERIOD_MS);
	}
}

TaskHandle_t tskhdlEvent3;
void taskEvent3(void* pvParam){
	while (true)
	{
		xEventGroupSetBits(evtgrpEvent, EVENT3);
		vTaskDelay((1 + (rand() % 10000)) / portTICK_PERIOD_MS);
	}
}

TaskHandle_t tskhdlProcess;
void taskProcess(void* pvParam){
	EventBits_t event;
	const EventBits_t eventMASK = EVENT1 | EVENT2 | EVENT3;
	while (true)
	{
		event = xEventGroupWaitBits(evtgrpEvent, eventMASK, pdTRUE, pdTRUE, portMAX_DELAY);
		if (event != 0){
			if (event&EVENT1)
				Serial.println("EVENT1 Occured");
			if (event&EVENT2)
				Serial.println("EVENT2 Occured");
			if (event&EVENT3)
				Serial.println("EVENT3 Occured");
		}
		else{
			Serial.println("Event Timout occured (No Event Occured)");
		}

	}
}
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	evtgrpEvent = xEventGroupCreate();
	xTaskCreate(taskEvent1, "taskEvent1", 128, NULL, 1, &tskhdlEvent1);
	xTaskCreate(taskEvent2, "taskEvent2", 128, NULL, 1, &tskhdlEvent2);
	xTaskCreate(taskEvent3, "taskEvent3", 128, NULL, 1, &tskhdlEvent3);
	xTaskCreate(taskProcess, "taskProcess", 128, NULL, 2, &tskhdlProcess);
}

// the loop function runs over and over again until power down or reset
void loop() {

}
