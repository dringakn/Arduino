/*
 Name:		BasicNavigation.ino
 Created:	12/14/2017 11:34:13 AM
 Author:	ahmad.kamal
 Purpose:	The following program consist of two tasks. The first one is used to send data to computer
			via serial port while the second one is used to move the robot on a square path. At the end
			of the trajectory robot motors are stopped and both tasks are suspended.
*/
#include "ArduinoRobot.h"

ArduinoRobot robot;

TaskHandle_t tskPrint = NULL;
void taskPrint(void* param) {
	while (true)
	{
		robot.printRobotData();
	}
	vTaskDelete(tskPrint);	// Shouldn't reach here!
}

TaskHandle_t tskTrajectory = NULL;
void taskTrajectory(void* param) {
	while (true)
	{
		robot.moveRobot(30, 0);		// Move straight 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
		vTaskDelay(pdMS_TO_TICKS(3333));
		robot.moveRobot(0, PI/2);	// Rotate CW 90deg @ V=0cm/sec and W=PI/2 rad/sec for 1000mSec
		vTaskDelay(pdMS_TO_TICKS(1000));

		robot.moveRobot(30, 0);		// Move straight 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
		vTaskDelay(pdMS_TO_TICKS(3333));
		robot.moveRobot(0, PI / 2);	// Rotate CW 90deg @ V=0cm/sec and W=PI/2 rad/sec for 1000mSec
		vTaskDelay(pdMS_TO_TICKS(1000));

		robot.moveRobot(30, 0);		// Move straight 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
		vTaskDelay(pdMS_TO_TICKS(3333));
		robot.moveRobot(0, PI / 2);	// Rotate CW 90deg @ V=0cm/sec and W=PI/2 rad/sec for 1000mSec
		vTaskDelay(pdMS_TO_TICKS(1000));

		robot.moveRobot(30, 0);		// Move straight 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
		vTaskDelay(pdMS_TO_TICKS(3333));
		robot.moveRobot(0, PI / 2);	// Rotate CW 90deg @ V=0cm/sec and W=PI/2 rad/sec for 1000mSec
		vTaskDelay(pdMS_TO_TICKS(1000));

		robot.moveRobot(0, 0);		// Stop robot motors
		vTaskSuspend(tskTrajectory);// Suspend the current task
		vTaskSuspend(tskPrint);		// Suspend the data printing task
	}
	vTaskDelete(tskTrajectory);	// Shouldn't reach here!
}
void setup() {
	robot.init(1, 1, 0, 200, 20);	// Initialize robot (Kv, Kw, Kwos, Kir, Kus)
	xTaskCreate(taskPrint, "SendData", 128, NULL, 1, &tskPrint);	// Create Printing Task
	xTaskCreate(taskTrajectory, "Trajectory", 128, NULL, 1, &tskTrajectory);	// Create Trajectory Task
	// Scheduler shall be started once setup is completed
}

void loop() {

}
