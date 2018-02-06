/*
Name:		LineFollowerAndObstacleAvoidance.ino
Created:	02/06/2018 18:24:09 PM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Purpose:	The purpose of the following program is to intelligently navigate a robot in a clutted
			enviornment and avoiding collision. If the robot detect a obstacle at front or at side
			it gives a navigation command to the robot in order to avoid hitting the obstacle. Your
			task is to determine the threshold for the specified speeds to avoid hitting the obstacles.
			Furthermore, to imporve the algorithm in order to move in open spaces.
*/
#include <ArduinoRobot.h>

ArduinoRobot robot;
const double V = 15, W = PI / 4;	// V = cm/Sec, W = rad/Sec


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
			if (!robot.bUSLeft && !robot.bUSRight) {		// Obstacle only in front: 1 0 0
				if (robot.usLeft > robot.usRight)
					robot.moveRobot(0, -W);					// Rotate Left
				else
					robot.moveRobot(0, W);					// Rotate Right
			}
			else if (!robot.bUSLeft && robot.bUSRight) {	// Obstacle on front/right: 1 0 1
				robot.moveRobot(0, -W);						// Rotate CCW
			}
			else if (robot.bUSLeft && !robot.bUSRight) {	// Obstacle on front/left: 1 1 0
				robot.moveRobot(0, W);						// Rotate CW
			}
			else if (robot.bUSLeft && robot.bUSRight) {		// Obstacle in all direction: 1 1 1
				robot.moveRobot(0, -W);						// Rotate CCW
			}
		}
		else {
			if (!robot.bUSLeft && !robot.bUSRight) {		// No Obstacle: 0 0 0
				robot.moveRobot(V, 0);						// Move Straight
			}
			else if (!robot.bUSLeft && robot.bUSRight) {	// Obstacle only on right: 0 0 1
				robot.moveRobot(0, -W);						// Steer CCW
			}
			else if (robot.bUSLeft && !robot.bUSRight) {	// Obstacle only on left: 0 1 0
				robot.moveRobot(0, W);						// Steer CW
			}
			else if (robot.bUSLeft && robot.bUSRight) {		// Obstacle on left/right: 0 1 1
				robot.moveRobot(V, 0);						// Keep Moving Straight
			}
		}
		vTaskDelay(1);					// Check the condition after some time
	}
	vTaskDelete(tskObstacleAvoidance);	// Shouldn't reach here!
}

TaskHandle_t tskBlink = NULL;
void taskBlink(void* param)
{
	while (true)
	{
		robot.setLED(HIGH);
		vTaskDelay(TIME_MS(1000));	// Wait for 1000 milliseconds
		robot.setLED(LOW);
		vTaskDelay(TIME_MS(1000));	// Wait for 1000 milliseconds
	}
	vTaskDelete(tskBlink);	// Shouldn't reach here!
}

void setup() {
	robot.init(1, 1, 0, 200, 20);
	xTaskCreate(taskObstacleAvoidance, "ObstacleAvoidance", 128, NULL, 1, &tskObstacleAvoidance);	// Create obstacle avoidance Task
	xTaskCreate(taskBlink, "statusLED", 128, NULL, 2, &tskBlink);							// Create line follower Task
}

void loop() {

}
