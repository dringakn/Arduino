// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Arduino_FreeRTOS.h>	// Scheduler
#include <queue.h>				// Queue, enable in the header file
#include <semphr.h>				// Semaphore, Mutex, enable in the header file
#include <timers.h>				// Software Timers, enable in the header file
#include <event_groups.h>		// Event Group, enable in the header file

class LEDClass
{
public:
	LEDClass(unsigned int, unsigned int);
	~LEDClass();
	void blink(unsigned int);		// Activate Blink Task
	void fade(unsigned int);		// Activate Fade Task
	void stop(void);				// Suspend Both Tasks
private:
	static const unsigned int EVENT1 = (1 << 0);	// EventGroup first bit/flag
	static const unsigned int EVENT2 = (1 << 1);	// EventGroup second bit/flag
	static const unsigned int EVENT3 = (1 << 2);	// EventGroup third bit/flag
	unsigned int _pinNo;			// Pin number
	unsigned int _delayMS;			// Delay time (milliseconds)
	TaskHandle_t tskhdlBlink;		// Blink task handle
	TaskHandle_t tskhdlFade;		// Fade task handle
	static QueueHandle_t queBuff;	// Queue for task communication (delay time period)
	static EventGroupHandle_t evtgrpEvent;	// Event handling
	static void taskBlink(void*);	// Blink Task handler
	static void taskFade(void*);	// Fade Task handler
};

#endif

