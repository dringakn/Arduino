/*
 Name:		StreamBuffer.ino
 Created:	12/13/2017 9:36:53 AM
 Author:	ahmad.kamal
 Purpose:	configSUPPORT_DYNAMIC_ALLOCATION must be set to 1 or left undefined in FreeRTOSConfig.h 
			for xStreamBufferCreate() to be available. xStreamBufferCreateStatic() for a version 
			that uses statically allocated memory (memory that is allocated at compile time)
*/
#include <Arduino_FreeRTOS.h>
#include <stream_buffer.h>

StreamBufferHandle_t sb;
TaskHandle_t tskhdlStreamBuffer = NULL;
void taskStreamBuffer(void*) 
{
	while (true)
	{

	}
	vTaskDelete(tskhdlStreamBuffer);
}

void setup() {
	Serial.begin(115200);
	xTaskCreate(taskStreamBuffer, "StreamBuffer", 128, NULL, 1, &tskhdlStreamBuffer);
	/* Create a stream buffer that can hold 100 bytes.  The memory used to hold
	both the stream buffer structure and the data in the stream buffer is
	allocated dynamically. */
	sb = xStreamBufferCreate(100, 10);
	if (sb == NULL)
	{
		/* There was not enough heap memory space available to create the stream buffer. */
		Serial.println("Error creating buffer");
	}
	else
	{
		/* The stream buffer was created successfully and can now be used. */
		Serial.println("Streambuffer created");
	}
}

void loop() {
  
}
