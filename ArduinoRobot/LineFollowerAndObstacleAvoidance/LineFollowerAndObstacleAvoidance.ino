/*
 Name:		LineFollowerAndObstacleAvoidance.ino
 Created:	12/14/2017 8:20:09 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Purpose:	The purpose of the following program is to intelligently navigate a robot in a clutted
			enviornment and avoiding collision. If the robot detect a line present on the floor
			then it tries to follow it as long as it is going to collide with the obstacle. There
			are no one set of robot command (linear/angulr velocities) which will intelligently
			navigate the robot, therefore, your task is to find the one which works best for you.
 */
#include <ArduinoRobot.h>

ArduinoRobot robot;
bool lineDetected = false;		// Flag to indicate status of the line detection sensor
bool frontObstacle = false;		// Flag to indicate status of front obstacle detection sensor

/*
	The line follower task shall use three out of the five bottom IR sensors to detect the line.
	The line following logic can be understood by the following table. When a sensor is over the
	line it gives a value of 1 otherwise 0. +W will rotate robot CW and -W will rotate it CCW.
	-----------------------------------------------------------------------------------------------
				Sensors					Command
	   L			M			R		  C
	irMidLeft	irMiddle	irMidRight	(V,W)		Remarks				Sensor Position
	-----------------------------------------------------------------------------------------------
		0			0			0		(V~=0,W~=0)	Off-track	   L M R|     |L M R
		0			0			1		(V>=0,W>0)	Rotating CCW	 L M|R    |
		0			1			0		(V>0,0)		On-track!!!			 L|M|R
		0			1			1		(V>=0,W>0)	Rotating CCW	   L|M R  |
		1			0			0		(V>=0,W<0)	Rotating CW			|    L|M R
		1			0			1		(V>0,0)		On-track!!!			|L| |R|
		1			1			0		(V>=0,W<0)	Rotating CW			|  L M|R
		1			1			1		(V>0,0)		On-track			|L M R|
	----------------------------------------------------------------------------------------------
*/
TaskHandle_t tskLineFollow = NULL;
void taskLineFollow(void* param) {
	const double V = 10, W = PI / 2;	// V = cm/Sec, W = rad/Sec
	while (true)
	{
		if (!robot.bIRMiddleLeft && !robot.bIRMiddle && !robot.bIRMiddleRight) {		// Off-track: 0 0 0
			lineDetected = false;
			// robot.moveRobot(?,?)
		}
		else {
			lineDetected = true;
			if (!robot.bIRMiddleLeft && !robot.bIRMiddle && robot.bIRMiddleRight) {	// Rotating CCW: 0 0 1
				robot.moveRobot(V, W);		// Rotate CW
			}
			else if (!robot.bIRMiddleLeft && robot.bIRMiddle && !robot.bIRMiddleRight) {	// On-track!!!: 0 1 0
				robot.moveRobot(V, 0);		// Move Straight!!!
			}
			else if (!robot.bIRMiddleLeft && robot.bIRMiddle && robot.bIRMiddleRight) {	// Rotating CCW: 0 1 1
				robot.moveRobot(V, W);		// Rotate CW
			}
			else if (robot.bIRMiddleLeft && !robot.bIRMiddle && !robot.bIRMiddleRight) {	// Rotating CW: 1 0 0
				robot.moveRobot(V, -W);		// Rotate CCW
			}
			else if (robot.bIRMiddleLeft && !robot.bIRMiddle && robot.bIRMiddleRight) {	// On-track!!!: 1 0 1
				robot.moveRobot(V, 0);		// Move Straight!!!
			}
			else if (robot.bIRMiddleLeft && robot.bIRMiddle && !robot.bIRMiddleRight) {	// Rotating CW: 1 1 0
				robot.moveRobot(V, -W);		// Rotate CCW
			}
			else if (robot.bIRMiddleLeft && robot.bIRMiddle && robot.bIRMiddleRight) {		// On-track: 1 1 1
				robot.moveRobot(V, 0);		// Move Straight
			}
		}
		vTaskDelay(1);					// Check the condition after some time
	}
	vTaskDelete(tskLineFollow);			// Shouldn't reach here!
}

/*
	The obstacle avoidance algorithm uses three ultrasonic sensors (left, front, right) to detect
	obstacle and decision to plan next action. The algorithm can be understood by using following 
	table. 1 means the sensor's measured range is less then a specified range, therefoe, there is a
	obtacle present. 0 means either there is no obstacle present or the obstacle is further away 
	from the specified distance. +W will rotate robot CW and -W will rotate it CCW.
	---------------------------------------------------------------------------------------------
				Sensors					Command
	  F				L			R		  C
	usFront		usLeft		usRight		(V,W)		Remarks				Sensor Position
	---------------------------------------------------------------------------------------------
	0				0			0		(V~=0,W~=0)	No obstacle
	0				0			1		(+V,W<=0)	Obstacle on right						R|
	0				1			0		(+V,W>=0)	Obstacle on left		|L
	0				1			1		(+V,W=0)	Obstacle on left/right	|L				R|
	1				0			0		(+V!,W~=0)	Obstacle on front				F
	1				0			1		(+V!,W<0)	Obstacle on front/right			F		R|
	1				1			0		(+V!,W>0)	Obstacle on front/left	|L		F
	1				1			1		(0,W~=0)	Obstacle in all direct	|L		F		R|
	---------------------------------------------------------------------------------------------
*/
TaskHandle_t tskObstacleAvoidance = NULL;
void taskObstacleAvoidance(void* param) {
	while (true)
	{
		if (robot.bUSFront) {
			frontObstacle = true;
			if (!robot.bUSLeft && !robot.bUSRight) {		// Obstacle only in front: 1 0 0

			}
			else if (!robot.bUSLeft && robot.bUSRight) {	// Obstacle on front/right: 1 0 1

			}
			else if (robot.bUSLeft && !robot.bUSRight) {	// Obstacle on front/left: 1 1 0

			}
			else if (robot.bUSLeft && robot.bUSRight) {	// Obstacle in all direction: 1 1 1

			}
		}
		else {
			frontObstacle = false;
			if (!robot.bUSLeft && !robot.bUSRight) {		// No Obstacle: 0 0 0

			}
			else if (!robot.bUSLeft && robot.bUSRight) {	// Obstacle only on right: 0 0 1

			}
			else if (robot.bUSLeft && !robot.bUSRight) {	// Obstacle only on left: 0 1 0

			}
			else if (robot.bUSLeft && robot.bUSRight) {	// Obstacle on left/right: 0 1 1

			}
		}
		vTaskDelay(1);					// Check the condition after some time
	}
	vTaskDelete(tskObstacleAvoidance);	// Shouldn't reach here!
}

/*
	The AI task is responsible for switching between obstacle avoidance and line follower tasks. The 
	following table can be used to understand the behavior of the robot. 1 means obstacle in front or
	line detected. 0 means no obstacle in front or no line detected
	------------------------------------------------------------------------------------------------
				Sensors				Active
		 O				  L			 Task
	frontObstacle	lineDetected						Remarks
	------------------------------------------------------------------------------------------------
	0				  0			ObstacleAvoidance		No line present, obstacle avoidance get preference
	0				  1			LineFollower			no obstacle at front, linesensor get preference
	1				  0			ObstacleAvoidance		obstaccle is at front, obstacle avoidance get preference
	1				  1			ObstacleAvoidance		obstaccle is at front, obstacle avoidance get preference
	------------------------------------------------------------------------------------------------
*/
TaskHandle_t tskAI = NULL;
void taskAI(void* param) {
	while (true)
	{
		if (frontObstacle) {		// Obstacle at front, obstacle avoidance get preference
			vTaskSuspend(tskLineFollow);
			vTaskResume(tskObstacleAvoidance);
		}
		else {						// No Obstacle is at front
			if (lineDetected) {		// Line is detected
				vTaskSuspend(tskObstacleAvoidance);
				vTaskResume(tskLineFollow);
			}
			else {					// No line detected, obstacle avoidance get preference
				vTaskSuspend(tskLineFollow);
				vTaskResume(tskObstacleAvoidance);
			}
		}
		vTaskDelay(1);					// Check the condition after some time
	}
	vTaskDelete(tskAI);					// Shouldn't reach here!
}

void setup() {
	robot.init(1, 1, 0, 200, 20);
	xTaskCreate(taskAI, "AI", 128, NULL, 1, &tskAI);									// Create AI Task
	xTaskCreate(taskObstacleAvoidance, "ObstacleAvoidance", 128, NULL, 1, &tskObstacleAvoidance);	// Create obstacle avoidance Task
	xTaskCreate(taskLineFollow, "SenLineFollowerdData", 128, NULL, 1, &tskLineFollow);		// Create line follower Task
}

void loop() {
  
}
