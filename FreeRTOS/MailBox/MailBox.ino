/*
 Name:		MailBox.ino
 Created:	11/19/2017 10:26:56 AM
 Author:	Ahmad kamal
 Purpose:	This example demostrate the use of queue as mailbox. To use queue as mailbox, we can
			use its, overwrite and peek function. The queue must be initilized with single element.
			The sender task overwrites a value in the queue while the recieve task peek the value
			present in the queue. Since the queue is not empty, therefore, it shall be not put into
			blocked mode or timeout occures.

			As an alternative to the queue, one can use task notificaiton value as a light weight 
			mailbox. It uses xTaskNotify(...) and xTaskNotifyWait(...) for implementaiton. It's only 
			limitaiton is that only one task can get the mail message.
*/
#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t queMailBox;

TaskHandle_t tskhdlSender = NULL;
void taskSender(void* pvParam){
	int uiMail = 3;
	while (true)
	{
		xQueueOverwrite(queMailBox, &uiMail);
		uiMail++;
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(tskhdlSender);	// Shouldn't reach here!
}

TaskHandle_t tskhdlReciever = NULL;
void taskReciever(void *pvParam){
	int uiMail;
	while (true)
	{
		if (xQueuePeek(queMailBox, &uiMail, pdMS_TO_TICKS(1000))==pdTRUE){
			Serial.print("Mail: "); Serial.println(uiMail);
		}
		else
		{
			Serial.println("No mail present");
		}
	}
	vTaskDelete(tskhdlReciever);	// Shouldn't reach here!
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskReciever, "taskReciever", 128, NULL, 2, &tskhdlReciever);
	xTaskCreate(taskSender, "taskSender", 128, NULL, 2, &tskhdlSender);
	queMailBox = xQueueCreate(1, sizeof(int));
}

void loop() {
  
}
