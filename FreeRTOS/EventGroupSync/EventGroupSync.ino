/*
 Name:		EventGroupSync.ino
 Created:	12/14/2017 9:04:53 AM
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

const unsigned int EVENT1 = (1 << 0);
const unsigned int EVENT2 = (1 << 1);
const unsigned int EVENT3 = (1 << 2);
const EventBits_t ALL_EVENTS = EVENT1 | EVENT2 | EVENT3;

EventGroupHandle_t evtgrpEvent = NULL;

TaskHandle_t tskhdlEvent1 = NULL;
void taskEvent1(void* pvParam) {
	EventBits_t uxReturn;
	while (true)
	{
			/* 
			Set bit 0 in the event group to note this task has reached the
			sync point.  The other two tasks will set the other two bits defined
			by ALL_SYNC_BITS.  All three tasks have reached the synchronisation
			point when all the ALL_SYNC_BITS are set.  Wait a maximum of 5000ms
			for this to happen. 
			*/
			uxReturn = xEventGroupSync(evtgrpEvent, EVENT1,ALL_EVENTS,pdMS_TO_TICKS(10000));
			if ((uxReturn & ALL_EVENTS) == ALL_EVENTS)
			{
				/* All three tasks reached the synchronisation point before the call
					to xEventGroupSync() timed out. 
				*/
				Serial.print("All three events synchronized:");
				Serial.println(uxReturn, BIN);
			}
			else {
				// Timeout occured
				Serial.print("Synchronized timeout occured:");
				Serial.println(uxReturn,BIN);
			}
	}
	vTaskDelete(tskhdlEvent1);	// Shouldn't reach here!
}

TaskHandle_t tskhdlEvent2 = NULL;
void taskEvent2(void* pvParam) {
	while (true)
	{
		vTaskDelay((1 + (rand() % 10000)) / portTICK_PERIOD_MS);
		/* Set bit 1 in the event group to note this task has reached the
		synchronisation point.  The other two tasks will set the other two
		bits defined by ALL_SYNC_BITS.  All three tasks have reached the
		synchronisation point when all the ALL_SYNC_BITS are set.  Wait
		indefinitely for this to happen. */
		xEventGroupSync(evtgrpEvent, EVENT2, ALL_EVENTS, portMAX_DELAY);
		/* xEventGroupSync() was called with an indefinite block time, so
		this task will only reach here if the syncrhonisation was made by all
		three tasks, so there is no need to test the return value. */
	}
	vTaskDelete(tskhdlEvent2);	// Shouldn't reach here!
}

TaskHandle_t tskhdlEvent3 = NULL;
void taskEvent3(void* pvParam) {
	while (true)
	{
		vTaskDelay((1 + (rand() % 10000)) / portTICK_PERIOD_MS);
		/* Set bit 2 in the event group to note this task has reached the
		synchronisation point.  The other two tasks will set the other two
		bits defined by ALL_SYNC_BITS.  All three tasks have reached the
		synchronisation point when all the ALL_SYNC_BITS are set.  Wait
		indefinitely for this to happen. */
		xEventGroupSync(evtgrpEvent, EVENT3, ALL_EVENTS, portMAX_DELAY);
		/* xEventGroupSync() was called with an indefinite block time, so
		this task will only reach here if the syncrhonisation was made by all
		three tasks, so there is no need to test the return value. */
	}
	vTaskDelete(tskhdlEvent3);	// Shouldn't reach here!
}

void setup() {
	Serial.begin(115200);
	evtgrpEvent = xEventGroupCreate();
	xTaskCreate(taskEvent1, "taskEvent1", 128, NULL, 1, &tskhdlEvent1);
	xTaskCreate(taskEvent2, "taskEvent2", 128, NULL, 1, &tskhdlEvent2);
	xTaskCreate(taskEvent3, "taskEvent3", 128, NULL, 1, &tskhdlEvent3);
}

void loop() {

}