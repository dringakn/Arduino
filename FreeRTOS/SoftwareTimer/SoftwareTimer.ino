/*
 Name:		SoftwareTimer.ino
 Created:	11/19/2017 11:31:39 PM
 Author:	Ahmad kamal
*/
#include <Arduino_FreeRTOS.h>
#include <timers.h>
//portYIELD();
TimerHandle_t tmrAutoReload=NULL, tmrOneShot = NULL;

static void timerCallbackOneShot(TimerHandle_t timer){
	TickType_t xTimeNow = xTaskGetTickCount();
	Serial.print("OneShot Timer Callback"); Serial.println(xTimeNow);
}

static void timerCallbackAutoReload(TimerHandle_t timer){
	TickType_t xTimeNow = xTaskGetTickCount();
	Serial.print("AutoReload Timer Callback"); Serial.println(xTimeNow);
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	tmrAutoReload = xTimerCreate("tmrAutoReload", pdMS_TO_TICKS(1000), pdTRUE, 0, timerCallbackAutoReload);
	tmrOneShot = xTimerCreate("tmrOneShot", pdMS_TO_TICKS(5000), pdFALSE, 0, timerCallbackOneShot);
	if (tmrAutoReload != NULL) xTimerStart(tmrAutoReload, 0);
	if (tmrOneShot != pdFALSE)xTimerStart(tmrOneShot, 0);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
