/*
Name:		Robot_IR_Sensor_Test_Example.ino
Created:	26 November 2018
Modified:	26 November 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Purpose:	The following program consist of two parts. Setup will initialize the robot while the loop will run indefnitely
			to repeatedly check if any one of the three middle IR sensor detected a line. If the line is detected then the 
			robot led is turned on while the robot becomes stationary, otherwise, the robot is rotating and the LED is off. The
			robot will rotate at a constant angular velocity of PI/4 rad/sec.
			You can use the robot terminal program to connect and configure robot parameters.
			The terminal program runs only on a computer running Windows. For wireless communication, turn on your computers
			internal bluetooth module or get one from the lab and configure it according to insturcions provided in your lab
			handouts.
Robot Control:
			robot.irLeft, robot.bIRLeft:
				Robot's left most IR sensor value and line status respectively.
			robot.irMiddleLeft, robot.bIRMiddleLeft:
				Robot's middle left IR sensor value and line status respectively.
			robot.irMiddle, robot.bIRMiddle:
				Robot's middle IR sensor value and line status respectively.
			robot.irMiddleRight, robot.bIRMiddleRight:
				Robot's middle right IR sensor value and line status respectively.
			robot.irRight, robot.bIRRight:
				Robot's right most IR sensor value and line status respectively.
			robot.usLeft, robot.bUSLeft:
				Robot's left US sensor value and obstacle status respectively.
			robot.usFront, robot.bUSFront:
				Robot's front US sensor value and obstacle status respectively.
			robot.usRight, robot.bUSRight:
				Robot's right US sensor value and obstacle status respectively.
			robot.linVel, robot.angVel:
				Robot's current linear and angular velocity in cm/sec and rad/sec.
			robot.x, robot.y, robot.theta:
				Robot's position and orientation in centimeter and radians respectively.
			robot.moveRobot(V,W,T):
				Robot's motion command, linear velocity in cm/sec, angular velocity in rad/sec and time in milliseconds.
				if time value is ignored or passed as -1 the robot command will run indefintely.
			robot.init(Kv, Kw, Kwos, THir, THus):
				Initialize robot using calibration constants.
			*/

#include "ArduinoRobot.h"
ArduinoRobot robot;

void setup() {
	/*
	Initialize Robot
	Input Parameters:
	Kv: Linear velocity calibration constant, increse the value if robot's actual linear velocity
		is less than commanded velocity and vice versa. (Default Value: 1)
	Kw:	Angular velocity calibration constant, increase the value if robot's actual angular velocity
		is less than commanded velocity and vice versa.  (Default Value: 1)
	Kwos: Angular velocity offset. Increase/Decrease the value if robot is not going straight,
		i.e. turning during straight line motion.  (Default Value: 0)
	IR Threshold: A threshold number between 1 and 1024 to represent the line color.  (Default Value: 200)
	US Threshold: A threshold distance value in centimeter representing obstacle.  (Default Value: 20 cm)
	*/
	robot.init(1, 1, 0, 200, 20);

}

void loop() {
	// If line is in any direction: 1 1 1
	if (robot.bIRMiddleLeft || robot.bIRMiddle || robot.bIRMiddleRight) { 
		robot.moveRobot(0, 0); // Stop robot motors
		digitalWrite(robot.LED, HIGH);	// Turn on robot's led
	}
	else { // Otherwise
		robot.moveRobot(0, PI / 4); // Robot will rotate
		digitalWrite(robot.LED, LOW);	// Turn off robot's led
	}
}
