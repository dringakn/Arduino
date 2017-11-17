/*
 Name:		QueueTask.ino
 Created:	11/17/2017 7:02:49 AM
 Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <MemoryFree.h>

// Create a handle to queue buffer
QueueHandle_t queBuffer;

// Creat transmitter task handler and the task 
TaskHandle_t tskhdlTxTask;
void taskTx(void* pvParam){
	static int ctr = 0;	// Counter value to be sent
	while (true)
	{
		// xQueueSendToBack(...) -> FIFO
		// xQueueSendToFront(...) -> LIFO
		// Send the counter to the queue (FIFO), if the queue is already full, block the current task, wait for a maximum of 100mSec
		// until some space gets created in the queue.
		if (xQueueSendToBack(queBuffer, &ctr, pdMS_TO_TICKS(1000)) == pdFALSE){
			// The timeout occures before some space get created in the queue
			Serial.println("Failed to send to queue");
		}
		else{
			// The counter value is succefully added to the queue
			Serial.print("Tx: "); Serial.println(ctr);
			ctr++;	// Increment the n
			//vTaskDelay(pdMS_TO_TICKS(20));
		}
	}
}

TaskHandle_t tskhdlRxTask;
void taskRx(void* pvParm){
	int ctr;
	while (true)
	{
		if (xQueueReceive(queBuffer, &ctr, pdMS_TO_TICKS(1000) == pdFALSE)){
			Serial.println("Failed to recieve to queue");
		}
		else{
			Serial.print("Rx: "); Serial.println(ctr);
			vTaskDelay(pdMS_TO_TICKS(1000));
		}
	}
}

// I am not able to find queuehandle variables

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	xTaskCreate(taskTx, "taskTx", 128, NULL, 2, &tskhdlTxTask);
	xTaskCreate(taskRx, "taskRx", 128, NULL, 2, &tskhdlRxTask);
	queBuffer = xQueueCreate(5, sizeof(int));
	Serial.println(freeMemory());
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
