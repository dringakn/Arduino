/*
 Name:		QueueTask.ino
 Created:	11/17/2017 7:02:49 AM
 Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <MemoryFree.h>

// Create a handle to queue buffer
QueueHandle_t queBuffer = NULL;

// Creat transmitter task handler and the task 
TaskHandle_t tskhdlTxTask;
void taskTx(void* pvParam){
	static int ctr = 0;	// Counter value to be sent
	while (true)
	{
		// xQueueSendToBack(...) -> FIFO
		// xQueueSendToFront(...) -> LIFO
		// Send the counter to the queue (FIFO), if the queue is already full, block the current task, wait for a maximum of 100mSec
		// until some space gets created in the queue. The function shall try to add the element in to the queue and if the queue is 
		// already full, block the current task for specified time. If the space get created the task gets resumed automatically,
		// otherwise after the time out the else branch is executed.
		if (xQueueSendToBack(queBuffer, &ctr, pdMS_TO_TICKS(100)) == pdTRUE){
			// The counter value is succefully added to the queue
			Serial.print("Tx: "); Serial.println(ctr); ctr++;
		}
		else{
			// The timeout occures before some space get created in the queue
			Serial.println("Failed to send to queue");
		}
		//vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

TaskHandle_t tskhdlRxTask;
void taskRx(void* pvParm){
	int ctr;
	while (true)
	{
		// The function will get an element from the queue, if the queue is empty then block current task for 100mSec.
		// If the time out occures then the else branch get exectued otherwise, the task get resumed and the element is fetched.
		if (xQueueReceive(queBuffer, &ctr, pdMS_TO_TICKS(100)) == pdTRUE){
			Serial.print("Rx: "); Serial.println(ctr);
		}
		else{
			Serial.println("Failed to recieve to queue");
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

// I am not able to find queuehandle variables

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	xTaskCreate(taskTx, "taskTx", 128, NULL, 2, &tskhdlTxTask);
	xTaskCreate(taskRx, "taskRx", 128, NULL, 2, &tskhdlRxTask);
	queBuffer = xQueueCreate(5, sizeof(int));
	//vQueueDelete(queBuffer);
	//Serial.println(uxQueueMessagesWaiting(queBuffer));
	//xQueueReset(queBuffer);
	//xQueueOverwrite(queBuffer, 0);					// For Mailbox
	//xQueuePeek(queBuffer, &ctr, pdMS_TO_TICKS(1000));	// For Mailbox
	Serial.println(freeMemory());
	Serial.println(pdMS_TO_TICKS(1000));
	Serial.println(1000/portTICK_PERIOD_MS);
	
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
