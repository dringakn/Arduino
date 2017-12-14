Following modifications are required for existing libraries before compiling the code.

FreeRTOS-10.0.0-1: 
Version (10.0.0-3) has problems
Modify the FreeRTOSConfig.h file to congigure FreeRTOS
#define configUSE_TRACE_FACILITY            1
#define configUSE_QUEUE_SETS                1
#define configQUEUE_REGISTRY_SIZE           1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetIdleTaskHandle          1 // create an idle task handle.
#define INCLUDE_xTaskGetCurrentTaskHandle       1

PID-Version1:

