/*
 Name:		EventGroup.ino
 Created:	11/19/2017 3:12:19 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Purpose:	This example demostrate the use of event group. Event groups can also be used to synchronise tasks,
			creating what is often referred to as a task 'rendezvous'. A task synchronisation point is a place 
			in application code at which a task will wait in the Blocked state (not consuming any CPU time) 
			until all the other tasks taking part in the synchronisation also reached their synchronisation 
			point.
			As an alternative to the event group, one can use task notificaiton value as a light weight 
			event passing mechanism. It uses xTaskNotify(...) and xTaskNotifyWait(...) for implementaiton. 
			It's one limitaiton is that only one task can get the event messages. The second limitation is
			that reciever task can't specify the customized bit setting notificaiton.
*/
#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#define EVENT1 (1<<0)
#define EVENT2 (1<<1)
#define EVENT3 (1<<2)

EventGroupHandle_t evtgrpEvent = NULL;

TaskHandle_t tskhdlEvent1 = NULL;
void taskEvent1(void* pvParam){
	while (true)
	{
		xEventGroupSetBits(evtgrpEvent, EVENT1);
		vTaskDelay((1 + (rand() % 10000)) / portTICK_PERIOD_MS);
	}
	vTaskDelete(tskhdlEvent1);	// Shouldn't reach here!
}

TaskHandle_t tskhdlEvent2 = NULL;
void taskEvent2(void* pvParam){
	while (true)
	{
		xEventGroupSetBits(evtgrpEvent, EVENT2);
		vTaskDelay((1 + (rand() % 10000)) / portTICK_PERIOD_MS);
	}
	vTaskDelete(tskhdlEvent2);	// Shouldn't reach here!
}

TaskHandle_t tskhdlEvent3 = NULL;
void taskEvent3(void* pvParam){
	while (true)
	{
		xEventGroupSetBits(evtgrpEvent, EVENT3);
		vTaskDelay((1 + (rand() % 10000)) / portTICK_PERIOD_MS);
	}
	vTaskDelete(tskhdlEvent3);	// Shouldn't reach here!
}

TaskHandle_t tskhdlProcess = NULL;
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
	vTaskDelete(tskhdlProcess);	// Shouldn't reach here!
}
void setup() {
	Serial.begin(115200);
	evtgrpEvent = xEventGroupCreate();
	xTaskCreate(taskEvent1, "taskEvent1", 128, NULL, 1, &tskhdlEvent1);
	xTaskCreate(taskEvent2, "taskEvent2", 128, NULL, 1, &tskhdlEvent2);
	xTaskCreate(taskEvent3, "taskEvent3", 128, NULL, 1, &tskhdlEvent3);
	xTaskCreate(taskProcess, "taskProcess", 128, NULL, 2, &tskhdlProcess);
}

void loop() {

}
