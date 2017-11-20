/*
 Name:		SoftwareTimer.ino
 Created:	11/19/2017 11:31:39 PM
 Author:	Ahmad kamal
 */
#include <Arduino_FreeRTOS.h>
#include <timers.h>
//portYIELD();
TimerHandle_t tmrAutoReload = NULL, tmrOneShot = NULL;

static void timerCallback(TimerHandle_t timer){
	uint32_t timerID = (uint32_t)pvTimerGetTimerID(timer);
	vTimerSetTimerID(timer, (void*)++timerID);
	if (timer == tmrOneShot){
		Serial.println("OneShot Timer Callback:");
		xTimerReset(tmrOneShot, 0);
	}
	else if(timer == tmrAutoReload){
		Serial.println("AutoReload Timer Callback:");
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	tmrAutoReload = xTimerCreate("tmrAutoReload", pdMS_TO_TICKS(2500), pdTRUE, 0, timerCallback);
	if (tmrAutoReload != NULL){
		if (xTimerStart(tmrAutoReload, 0))
			Serial.println("AutoReload Timer Started Successfully");
		else
			Serial.println("AutoReload Timer Couldn't be started");
	}
	tmrOneShot = xTimerCreate("tmrOneShot", pdMS_TO_TICKS(5000), pdFALSE, 0, timerCallback);
	if (tmrOneShot != NULL){
		if (xTimerStart(tmrOneShot, 0))
			Serial.println("OneShot Timer Started Successfully");
		else
			Serial.println("OneShot Timer Couldn't be started");
	}
}

// the loop function runs over and over again until power down or reset
void loop() {

}
