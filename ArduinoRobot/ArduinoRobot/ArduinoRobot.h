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
#include <EEPROMex.h>
#include <EEPROMVar.h>
#include "FastReadWrite.h"
#include "MovingAverageFilterFixed.h"
#include "MovingMedianFilterFixed.h"

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
	static double usLeft, usFront, usRight;		// Ultrasonic sensor readings
	static double irLeft, irMiddleLeft, irMiddle, irMiddleRight, irRight;// Infrared sensor readings
	static double bUSLeft, bUSFront, bUSRight;	// Ultrasonic obstacle status
	static double bIRLeft, bIRMiddleLeft, bIRMiddle, bIRMiddleRight, bIRRight;// Infrared line status
	static long cmdTime;						// Remaining motors command execution time in milliseconds
	
	static double Kp, Ki, Kd;					// Left and Right Motor PID constants
	static double infraredThreshold, ultrasonicThreshold;// Sensor Threshold
	static double Kv, Kw, Kwos;					// Calibration Constants
	static int nVSamples, nUSSamples, nIRSamples;// Speed filtering window size
	static int calibIRLeft, calibIRMiddleLeft, calibIRMiddle;
	static int calibIRMiddleRight, calibIRRight;
	static int prevCmd;

	static MovingAverageFilterFixed<double> filtVl, filtVr;	// Filtering on speed signals
	static MovingAverageFilterFixed<int> filtIRLeft;		// Filter for infrarred sensors
	static MovingAverageFilterFixed<int> filtIRMiddleLeft, filtIRMiddle, filtIRMiddleRight, filtIRRight;
	static MovingMedianFilterFixed<int> filtUSLeft;		// Filter for ultrasonic sensors
	static MovingMedianFilterFixed<int> filtUSFront, filtUSRight;

	const void (*resetMe)(void) = 0;			// Reset function

	void init(double kv, double kw, double kwos, double irThresh, double usThresh);
	void moveRobot(double linVel, double angVel, long time=-1);// Navigation command
	void motorPWM(int leftPWM, int rightPWM, long time=-1);
	// Raw motors PWM
	void printRobotSensors(void);				// Send robot measurements to the serial port
	void printPID(void);						// Send speed control measurements to the serial port
	void printMotorEncoder(void);				// Send motor measurements to the serial port
	void printOdometry(void);					// Send wheel odometry to the serial port
	void printUltrasonic(void);					// Send Ultrasonic sensor measurements to the serial port
	void printInfrared(void);					// Send Infrared sensor measurements to the serial port
	void printSettings(void);					// Send robot settings to the serial port

	void loadParameters(void);					// Load parameters from EEPROM
	void loadDefaultParameters(void);			// Load default parameters from EEPROM
	void saveParameters(void);					// Validate and save the parameters in EEPROM

private:
	static int motorsControl;					// Left/Right motors control (AUTOMATIC | MANUAL)
	static double cmdVelLeft, cmdVelRight;		// Commanded velocities
	static long encoderRightCtr, prevEncoderRightCtr;	// Right encoder pulses counter
	static long encoderLeftCtr, prevEncoderLeftCtr;	// Left encoder pulses counter
	static double WHEELDIST;				// Robot wheels seperation distance
	static double SPEEDCONSTANT;			// Pulse constant = PI*D/PPR
	SemaphoreHandle_t mtxSerial = NULL;		// Serial port binary semaphore
	static TaskHandle_t tskPrint;			// Task handle for printing control
	static TaskHandle_t tskInfrared;		// Task handle for infrared sensor calibration
	const char SEPERATOR = ',';				// Data seperator for serial port transmission

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

	static unsigned int ADDRESS_KP;		// EEPROM address of Kp
	static unsigned int ADDRESS_KI;		// EEPROM address of Ki
	static unsigned int ADDRESS_KD;		// EEPROM address of Kd
	static unsigned int ADDRESS_KV;		// EEPROM address of Kv
	static unsigned int ADDRESS_KW;		// EEPROM address of Kw
	static unsigned int ADDRESS_KWOS;	// EEPROM address of Kwos
	static unsigned int ADDRESS_IRTRSH;	// EEPROM address of infraredThreshold
	static unsigned int ADDRESS_USTRSH;	// EEPROM address of ultrasonicThreshold
	static unsigned int ADDRESS_NVSPL;	// EEPROM address of nVSamples
	static unsigned int ADDRESS_NIRSPL;	// EEPROM address of nIRSamples
	static unsigned int ADDRESS_NUSSPL;	// EEPROM address of nUSSamples
	static unsigned int ADDRESS_IRL;	// EEPROM address of calibIRLeft
	static unsigned int ADDRESS_IRML;	// EEPROM address of calibIRMiddleLeft
	static unsigned int ADDRESS_IRM;	// EEPROM address of calibIRMiddle
	static unsigned int ADDRESS_IRMR;	// EEPROM address of calibIRMiddleRight
	static unsigned int ADDRESS_IRR;	// EEPROM address of calibIRRight
	static unsigned int ADDRESS_PRVCMD;	// EEPROM address of prevCmd

	static void taskUltraSonic(void*);	// Ultrasonic sensor measurement callback
	static void taskInfraRed(void*);	// Infrared sensor measurement callback
	static void taskMotorControl(void*);// Motor control callback
	static void taskParseCommands(void*);// Serial port command handler task
	static void taskPrint(void*);		// Serial port data transmitter

	static void encRightAISR(void);	// Right motor ecoder channel A Interrupt Service Routine
	static void encRightBISR(void);	// Right motor ecoder channel B Interrupt Service Routine
	static void encLeftAISR(void);	// Left motor ecoder channel A Interrupt Service Routine
	static void encLeftBISR(void);	// Left motor ecoder channel B Interrupt Service Routine
	int freeRam();
};

#endif

