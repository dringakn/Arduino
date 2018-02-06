/*
Name:		LineFollowerAndObstacleAvoidance.ino
Created:	02/06/2018 18:26:00 PM
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Purpose:	The purpose of the following program is to intelligently navigate a robot in a clutted
			enviornment using a simple line follower algorithm. If the robot detect a line present on the floor
			then it tries to follow. Your task is to imporove the algorithm for line disconnection and 
			cross-section condition.
*/
#include <ArduinoRobot.h>

ArduinoRobot robot;
const double V = 15, W = PI / 4;	// V = cm/Sec, W = rad/Sec

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
	while (true)
	{
		if (!robot.bIRMiddleLeft && !robot.bIRMiddle && !robot.bIRMiddleRight) {		// Off-track: 0 0 0
			robot.moveRobot(0, -W);
		}
		else {
			if (!robot.bIRMiddleLeft && !robot.bIRMiddle && robot.bIRMiddleRight) {	// Rotating CCW: 0 0 1
				robot.moveRobot(0, W);		// Rotate CW
			}
			else if (!robot.bIRMiddleLeft && robot.bIRMiddle && !robot.bIRMiddleRight) {	// On-track!!!: 0 1 0
				robot.moveRobot(V, 0);		// Move Straight!!!
			}
			else if (!robot.bIRMiddleLeft && robot.bIRMiddle && robot.bIRMiddleRight) {	// Rotating CCW: 0 1 1
				robot.moveRobot(0, W);		// Rotate CW
			}
			else if (robot.bIRMiddleLeft && !robot.bIRMiddle && !robot.bIRMiddleRight) {	// Rotating CW: 1 0 0
				robot.moveRobot(0, -W);		// Rotate CCW
			}
			else if (robot.bIRMiddleLeft && !robot.bIRMiddle && robot.bIRMiddleRight) {	// On-track!!!: 1 0 1
				robot.moveRobot(V, 0);		// Move Straight!!!
			}
			else if (robot.bIRMiddleLeft && robot.bIRMiddle && !robot.bIRMiddleRight) {	// Rotating CW: 1 1 0
				robot.moveRobot(0, -W);		// Rotate CCW
			}
			else if (robot.bIRMiddleLeft && robot.bIRMiddle && robot.bIRMiddleRight) {		// On-track: 1 1 1
				robot.moveRobot(V, 0);		// Move Straight
			}
		}
		vTaskDelay(1);					// Check the condition after some time
	}
	vTaskDelete(tskLineFollow);			// Shouldn't reach here!
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
	xTaskCreate(taskLineFollow, "SenLineFollowerdData", 128, NULL, 1, &tskLineFollow);		// Create line follower Task
	xTaskCreate(taskBlink, "statusLED", 128, NULL, 2, &tskBlink);							// Create line follower Task
}

void loop() {

}
