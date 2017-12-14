/*
 Name:		TaskNotificationWait.ino
 Created:	12/13/2017 7:35:55 PM
 Author:	ahmad.kamal
*/
#include <Arduino_FreeRTOS.h>

TaskHandle_t tskhdlTx = NULL;
TaskHandle_t tskhdlRx = NULL;
const unsigned long ULONG_MAX = 0xFFFFFFFF;

void taskTx(void *pvParam)
{
	uint32_t ulPrevValue;
	while (true)
	{
		/*
		eNoAction: Notification is generated without using specified ulValue
		eSetBits:  Tasks Notification value is ored with the specifeid ulValue
		eIncrement: Increment the task's notification value
		eSetValueWithOverwrite: Set the task's notification value with ulValue
		eSetValueWithoutOverwrite: Task's notification value updated only if there is no pending event otherwise
									pdFALSE is returend.
		*/
		if (xTaskGenericNotify(tskhdlRx, 786ul, eSetBits, &ulPrevValue) == pdTRUE) {
			Serial.print("Tx:786,"); Serial.println(ulPrevValue);
		}
		else {
			// The target task's notification value hasn't been updated because a notification has been already pending
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		/*
		TICK-TOCK Example
		xTaskNotifyGive(tskhdlRx);	// Send a notification to taskRx, use as lightweight binary semaphore
		xTaskNotify(tskhdlRx,0xFF, eSetValueWithOverwrite);	// Send 0xFF to taskRx overwriting it's existing value
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);// Block until notificaiton recieve from taskTx, if pdTRUE then decrement notificaiton value otherwise set to zero
		*/
	}
	vTaskDelete(tskhdlTx);
}

void taskRx(void *pvParam)
{
	uint32_t ulValue;
	while (true)
	{
		/*
			ulBitsToClearOnEntry: Clear the specified bits before entering the function, zero to change nothing, setting it to ULONG_MAX will reset it to zero
			ulBitsToClearOnExit:  Clear the specified bits of the notificaiton value before the function exit, ULONG_MAX will reset it to zero after read.
		*/
		if (xTaskNotifyWait(NULL, ULONG_MAX, &ulValue, pdMS_TO_TICKS(100)) == pdTRUE) {
			Serial.print("Rx:"); Serial.println(ulValue);
		}
		else {
			// Timeout occured before the next value
			Serial.println("Rx:Timeout");
		}
		/*
		TICK-TOCK Example
		xTaskNotifyGive(tskhdlTx);	// Send a notification to taskTx, use as lightweight binary semaphore
		xTaskNotify(tskhdlRx,0xFF, eSetBits);	// Set lower eight bits of taskRx notification value
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);// Block until notificaiton recieve from taskRx, if pdTRUE then decrement notificaiton value otherwise set to zero
		*/
	}
	vTaskDelete(tskhdlRx);
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskTx, "TX", 128, NULL, 1, &tskhdlTx);
	xTaskCreate(taskRx, "RX", 128, NULL, 1, &tskhdlRx);
	//vTaskStartScheduler();
	//vTaskSuspendAll();
	//xTaskResumeAll();
}

void loop() {
  
}
