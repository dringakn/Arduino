/*
 Name:		StreamBuffer.ino
 Created:	12/13/2017 9:36:53 AM
 Author:	ahmad.kamal
 Purpose:	The streambuffer functionality (files) are not availilable as of today for arduino port.	
			configSUPPORT_DYNAMIC_ALLOCATION must be set to 1 or left undefined in FreeRTOSConfig.h 
			for xStreamBufferCreate() to be available. xStreamBufferCreateStatic() for a version 
			that uses statically allocated memory (memory that is allocated at compile time)
*/
#include <Arduino_FreeRTOS.h>
//#include <stream_buff.h>

//StreamBufferHandle_t xStreamBuffer;

void setup() {

}

void loop() {
  
}
