/*
 Name:		BasicNavigation.ino
 Created:	12/14/2017 11:34:13 AM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Purpose:	The following program consist of two tasks. The first one is used to send data to computer
			via serial port while the second one is used to move the robot on a square path. At the end
			of the trajectory robot motors are stopped and both tasks are suspended.
*/
#include "ArduinoRobot.h"

ArduinoRobot robot;

TaskHandle_t tskTrajectory1 = NULL;
void taskTrajectory1(void* param) {
	while (true)
	{
		robot.motorPWM(-100, 100);	// Open loop control, Left:+100% PWM, Right:-100% PWM
		vTaskDelay(TIME_MS(500));	// Apply for 500 milliseconds

		robot.motorPWM(0, 0);		// Stop robot motors
		vTaskDelay(TIME_MS(1000));	// Takes around 1Sec to decay the no load max speed to zero
		vTaskSuspend(tskTrajectory1);// Suspend the current task
	}
	vTaskDelete(tskTrajectory1);	// Shouldn't reach here!
}

TaskHandle_t tskTrajectory2 = NULL;
void taskTrajectory2(void* param) {
	while (true)
	{
		robot.moveRobot(30, 0);		// Move straight 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
		vTaskDelay(TIME_MS(1000));	// Wait for 3333 milliseconds

		robot.moveRobot(0, 0);		// Stop robot motors
		vTaskDelay(TIME_MS(500));	// Takes around 500mSec to decay the no load max speed to zero
		vTaskSuspend(tskTrajectory2);// Suspend the current task
	}
	vTaskDelete(tskTrajectory2);	// Shouldn't reach here!
}

TaskHandle_t tskTrajectory3 = NULL;
void taskTrajectory3(void* param) {
	while (true)
	{
		for (int i = 0; i < 4; i++) {
			robot.moveRobot(30, 0);		// Move straight 1m @ V=30cm/sec and W=0rad/sec for 3333mSec
			vTaskDelay(TIME_MS(3333));
			robot.moveRobot(0, PI / 2);	// Rotate CW 90deg @ V=0cm/sec and W=PI/2 rad/sec for 1000mSec
			vTaskDelay(TIME_MS(1000));
		}
		robot.moveRobot(0, 0);		// Stop robot motors
		vTaskSuspend(tskTrajectory3);// Suspend the current task
	}
	vTaskDelete(tskTrajectory3);	// Shouldn't reach here!
}


void setup() {
	robot.init(1, 1, 0, 200, 20);	// Initialize robot (Kv, Kw, Kwos, Kir, Kus)
	//xTaskCreate(taskTrajectory1, "Trajectory", 128, NULL, 1, &tskTrajectory1);	// Create Trajectory1 Task
	xTaskCreate(taskTrajectory2, "Trajectory2", 128, NULL, 1, &tskTrajectory2);	// Create Trajectory2 Task
	//xTaskCreate(taskTrajectory3, "Trajectory3", 128, NULL, 1, &tskTrajectory3);	// Create Trajectory3 Task
	// Scheduler shall be started once setup is completed
}

void loop() {

}
