/*
 Name:		ArduinoRobot.h
 Created:	12/14/2017 5:41:13 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License

*/

#ifndef _ArduinoRobot_h
#define _ArduinoRobot_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <PID_v1.h>
#include <UltraDistSensor.h>
#include "FastReadWrite.h"
#include "MovingAverageFilter.h"
#include "MovingMedianFilter.h"

#ifndef TIME_MS
#define TIME_MS(mSec) (mSec/portTICK_PERIOD_MS)
#endif

class ArduinoRobot {
public:
	ArduinoRobot();
	~ArduinoRobot();
	static double x, y, theta;					// Robot pose x[cm], y[cm], theta[radian]
	static double velLeft, velRight;			// Measured wheel velocities
	static double linVel, angVel;				// Calculated robot velocities
	static double deltaTime;					// Recent motor velocity sample time in millisecons
	static double Kp, Ki, Kd;					// Left and Right Motor PID constants
	static double usLeft, usFront, usRight;		// Ultrasonic sensor readings
	static double irLeft, irMiddleLeft, irMiddle, irMiddleRight, irRight;	// Infrared sensor readings
	static double infraredThreshold, ultrasonicThreshold;	// Sensor Threshold
	static MovingAverageFilter mavgVl, mavgVr;	// Filtering on speed signals

	static void taskUltraSonic(void*);			// Ultrasonic sensor measurement callback
	static void taskInfraRed(void*);			// Infrared sensor measurement callback
	static void taskMotorControl(void*);		// Motor control callback

	void init(double kv, double kw, double kwos, double irThresh, double usThresh);
	void moveRobot(double linVel, double angVel);	// Navigation command
	void motorPWM(int leftPWM, int rightPWM);		// Raw motors PWM

	void printRobotData(void);					// Send robot measurements to the serial port
	void printPID(void);						// Send speed control measurements to the serial port
	void printMotorEncoder(void);				// Send motor measurements to the serial port
	void printOdometry(void);					// Send wheel odometry to the serial port
	void printUltrasonic(void);					// Send Ultrasonic sensor measurements to the serial port
	void printInfrared(void);					// Send Infrared sensor measurements to the serial port

private:
	static int motorsControl;					// Left/Right motors control (AUTOMATIC | MANUAL)
	static double cmdVelLeft, cmdVelRight;		// Commanded velocities
	static long encoderRightCtr, prevEncoderRightCtr;	// Right encoder pulses counter
	static long encoderLeftCtr, prevEncoderLeftCtr;	// Left encoder pulses counter
	static double Kv, Kw, Kwos;				// Calibration Constants
	static double WHEELDIST;				// Robot wheels seperation distance
	static double SPEEDCONSTANT;			// Pulse constant = PI*D/PPR
	SemaphoreHandle_t mtxSerial = NULL;		// Serial port binary semaphore

	static unsigned int LED;		// Robot Status LED

	static unsigned int ENCLA;	// Left Motor Encoder Channel A
	static unsigned int ENCLB;	// Left Motor Encoder Channel B
	static unsigned int ENCRA;	// Right Motor Encoder Channel A
	static unsigned int ENCRB;	// Right Motor Encoder Channel B

	static unsigned int ENL;	// Left Motor Enable
	static unsigned int INL1;	// Left Motor Direction Control Pin 1
	static unsigned int INL2;	// Left Motor Direction Control Pin 2
	static unsigned int ENR;		// Right Motor Enable
	static unsigned int INR1;	// Right Motor Direction Control Pin 1
	static unsigned int INR2;	// Right Motor Direction Control Pin 2

	static unsigned int IRLEFT;	// Left Inrared sensor
	static unsigned int IRMIDLEFT;	// Middle Left Inrared sensor
	static unsigned int IRMIDDLE;	// Middle Inrared sensor
	static unsigned int IRMIDRIGHT;	// Middle Right Inrared sensor
	static unsigned int IRRIGHT;	// Right Inrared sensor

	static unsigned int USLEFT_TRIG;	// Left Ultrasonic sensor trigger pin
	static unsigned int USLEFT_ECHO;	// Left Ultrasonic sensor echo pin
	static unsigned int USFRONT_TRIG;	// Front Ultrasonic sensor trigger pin
	static unsigned int USFRONT_ECHO;	// Front Ultrasonic sensor echo pin
	static unsigned int USRIGHT_TRIG;	// Right Ultrasonic sensor trigger pin
	static unsigned int USRIGHT_ECHO;	// Right Ultrasonic sensor echo pin

	static void encRightAISR(void);	// Right motor ecoder channel A Interrupt Service Routine
	static void encRightBISR(void);	// Right motor ecoder channel B Interrupt Service Routine
	static void encLeftAISR(void);	// Left motor ecoder channel A Interrupt Service Routine
	static void encLeftBISR(void);	// Left motor ecoder channel B Interrupt Service Routine
};

#endif

