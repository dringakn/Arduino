Following modifications are required for existing libraries before compiling the code.
TODO: Replace the UltraDistSensor library with the PinChangeInterrupt Library

FreeRTOS-10.0.0-1: 
Version (10.0.0-3) has problems
Modify the FreeRTOSConfig.h file to congigure FreeRTOS
#define configUSE_TRACE_FACILITY            1
#define configUSE_QUEUE_SETS                1
#define configQUEUE_REGISTRY_SIZE           1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetIdleTaskHandle          1 // create an idle task handle.
#define INCLUDE_xTaskGetCurrentTaskHandle       1

UltraDistSensor:
Comment the lines of getReading function in the UltraDistSensor.cpp file as shown below
int UltraDistSensor::getReading(){
	//delay(10);
	if(common==true) pinMode(trig,OUTPUT);
	//digitalWrite(trig, LOW);
	//delayMicroseconds(2);
	digitalWrite(trig, HIGH);
	//delayMicroseconds(10);
	digitalWrite(trig, LOW);
	if(common==true) pinMode(echo, INPUT);
	return pulseIn(echo, HIGH,timeOut);
}
