/*
 Name:		SoftwareTimer.ino
 Created:	11/19/2017 11:31:39 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 */
#include <Arduino_FreeRTOS.h>
#include <timers.h>
//portYIELD();
TimerHandle_t tmrAutoReload = NULL, tmrOneShot = NULL;

void timerCallback(TimerHandle_t timer){
	uint32_t timerID = (uint32_t)pvTimerGetTimerID(timer);
	vTimerSetTimerID(timer, (void*)++timerID);	// Time ID is used if one callback is used for multiple timers
	if (timer == tmrOneShot){
		Serial.println("OneShot Timer Callback:");
		xTimerReset(tmrOneShot, 0);
	}
	else if(timer == tmrAutoReload){
		Serial.println("AutoReload Timer Callback:");
	}
}

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

void loop() {

}
