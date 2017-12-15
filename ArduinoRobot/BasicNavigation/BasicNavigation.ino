/*
 Name:		BasicNavigation.ino
 Created:	12/14/2017 11:34:13 AM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com)
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
		//robot.printRobotData();
		robot.printMotorEncoder();
		//robot.printPID();
		vTaskDelay(1);					// Wait 1Tick = 17mSec before sending new set of data
	}
	vTaskDelete(tskPrint);	// Shouldn't reach here!
}

TaskHandle_t tskTrajectory = NULL;
void taskTrajectory(void* param) {
	while (true)
	{
		for (int i = 0; i < 4; i++) {
			robot.moveRobot(30, 0);		// Move straight 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
			vTaskDelay(TIME_MS(3333));
			robot.moveRobot(0, PI / 2);	// Rotate CW 90deg @ V=0cm/sec and W=PI/2 rad/sec for 1000mSec
			vTaskDelay(TIME_MS(1000));
		}
		robot.moveRobot(0, 0);		// Stop robot motors
		vTaskSuspend(tskPrint);		// Suspend the data printing task, before suspending itself!!!
		vTaskSuspend(tskTrajectory);// Suspend the current task
	}
	vTaskDelete(tskTrajectory);	// Shouldn't reach here!
}

TaskHandle_t tskTrajectory2 = NULL;
void taskTrajectory2(void* param) {
	while (true)
	{
		robot.moveRobot(30, 0);		// Move straight 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
		vTaskDelay(TIME_MS(3333));
		robot.moveRobot(-30, 0);	// Move back 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
		vTaskDelay(TIME_MS(3333));

		robot.moveRobot(0, 0);		// Stop robot motors
		vTaskSuspend(tskPrint);		// Suspend the data printing task, before suspending itself!!!
		vTaskSuspend(tskTrajectory2);// Suspend the current task
	}
	vTaskDelete(tskTrajectory2);	// Shouldn't reach here!
}

void setup() {
	robot.init(1, 1, 0, 200, 20);	// Initialize robot (Kv, Kw, Kwos, Kir, Kus)
	xTaskCreate(taskPrint, "SendData", 128, NULL, 1, &tskPrint);	// Create Printing Task
	//xTaskCreate(taskTrajectory, "Trajectory", 128, NULL, 1, &tskTrajectory);	// Create Trajectory Task
	xTaskCreate(taskTrajectory2, "Trajectory2", 128, NULL, 1, &tskTrajectory2);	// Create Trajectory2 Task
	// Scheduler shall be started once setup is completed
}

void loop() {

}
