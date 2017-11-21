// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Arduino_FreeRTOS.h>	// Scheduler
#include <queue.h>	// Queue
#include <semphr.h>	// Semaphore, Mutex
#include <timers.h>	// Software Timers

class LEDClass
{
public:
	LEDClass(unsigned int, unsigned int);
	~LEDClass();
	void blink(unsigned int);		// Activate Blink Task
	void fade(unsigned int);		// Activate Fade Task
	void stop(void);				// Suspend Both Tasks
private:
	unsigned int _pinNo;			// Pin number
	unsigned int _delayMS;			// Delay time (milliseconds)
	TaskHandle_t tskhdlBlink;		// Blink task handle
	TaskHandle_t tskhdlFade;		// Fade task handle
	static QueueHandle_t queBuff;	// Queue for task communication (delay time period)
	static void taskBlink(void*);	// Blink Task handler
	static void taskFade(void*);	// Fade Task handler
};

#endif

