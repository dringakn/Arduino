/*
 Name:		ArduinoRobot.cpp
 Created:	12/14/2017 5:41:13 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description: Upload the program into an ArduinoMega2560 and connect a serial terminal
			with settings 115200-8-N-1. Send the following command "h?", without quotes
			to the Arduino through the terminal.
 */

#include "ArduinoRobot.h"

 // Initialize static variables
long ArduinoRobot::encoderLeftCtr = 0, ArduinoRobot::prevEncoderLeftCtr = 0;
long ArduinoRobot::encoderRightCtr = 0, ArduinoRobot::prevEncoderRightCtr = 0;

int ArduinoRobot::motorsControl = AUTOMATIC;
double ArduinoRobot::usLeft = 0, ArduinoRobot::usFront = 0, ArduinoRobot::usRight = 0;
double ArduinoRobot::irLeft = 0, ArduinoRobot::irMiddleLeft = 0, ArduinoRobot::irMiddle = 0;
double ArduinoRobot::irMiddleRight = 0, ArduinoRobot::irRight = 0;
double ArduinoRobot::bUSLeft = 0, ArduinoRobot::bUSFront = 0, ArduinoRobot::bUSRight = 0;
double ArduinoRobot::bIRLeft = 0, ArduinoRobot::bIRMiddleLeft = 0, ArduinoRobot::bIRMiddle = 0;
double ArduinoRobot::bIRMiddleRight = 0, ArduinoRobot::bIRRight = 0;
double ArduinoRobot::x = 0, ArduinoRobot::y = 0, ArduinoRobot::theta;
double ArduinoRobot::velLeft = 0, ArduinoRobot::velRight = 0;
double ArduinoRobot::cmdVelLeft = 0, ArduinoRobot::cmdVelRight = 0;
double ArduinoRobot::linVel = 0, ArduinoRobot::angVel = 0;
double ArduinoRobot::deltaTime = 0;
long ArduinoRobot::cmdTime = -1;
double ArduinoRobot::Kp = 20, ArduinoRobot::Ki = 20, ArduinoRobot::Kd = 1;
double ArduinoRobot::Kv = 1, ArduinoRobot::Kw = 1, ArduinoRobot::Kwos = 0;
double ArduinoRobot::infraredThreshold = 200, ArduinoRobot::ultrasonicThreshold = 20;
int ArduinoRobot::nVSamples = 10, ArduinoRobot::nIRSamples = 5, ArduinoRobot::nUSSamples = 3;
int ArduinoRobot::calibIRLeft = 0, ArduinoRobot::calibIRMiddleLeft = 0;
int ArduinoRobot::calibIRMiddle = 0, ArduinoRobot::calibIRMiddleRight = 0;
int ArduinoRobot::calibIRRight = 0;
int ArduinoRobot::prevCmd = 'c';


double ArduinoRobot::WHEELDIST = 17.4;
double ArduinoRobot::SPEEDCONSTANT = PI * 6.7 / 940.0;
MovingAverageFilterFixed<double> ArduinoRobot::filtVl(nVSamples);	// N-points moving average filter
MovingAverageFilterFixed<double> ArduinoRobot::filtVr(nVSamples);	// N-points moving average filter
MovingAverageFilterFixed<int> ArduinoRobot::filtIRLeft(nIRSamples);
MovingAverageFilterFixed<int> ArduinoRobot::filtIRMiddleLeft(nIRSamples), ArduinoRobot::filtIRMiddle(nIRSamples);
MovingAverageFilterFixed<int> ArduinoRobot::filtIRMiddleRight(nIRSamples), ArduinoRobot::filtIRRight(nIRSamples);
MovingMedianFilterFixed<int> ArduinoRobot::filtUSLeft(nUSSamples);
MovingMedianFilterFixed<int> ArduinoRobot::filtUSFront(nUSSamples), ArduinoRobot::filtUSRight(nUSSamples);

TaskHandle_t ArduinoRobot::tskPrint = NULL;
TaskHandle_t ArduinoRobot::tskInfrared = NULL;
TaskHandle_t ArduinoRobot::tskUltrasonic = NULL;
TaskHandle_t ArduinoRobot::tskMotorControl = NULL;

unsigned int  ArduinoRobot::LED = 9;

unsigned int  ArduinoRobot::ENCLA = 2;
unsigned int  ArduinoRobot::ENCLB = 21;
unsigned int  ArduinoRobot::ENCRA = 3;
unsigned int  ArduinoRobot::ENCRB = 20;

unsigned int  ArduinoRobot::ENL = 11;
unsigned int  ArduinoRobot::INL1 = 12;
unsigned int  ArduinoRobot::INL2 = 10;
unsigned int  ArduinoRobot::ENR = 6;
unsigned int  ArduinoRobot::INR1 = 7;
unsigned int  ArduinoRobot::INR2 = 8;

unsigned int ArduinoRobot::IRLEFT = A8;
unsigned int ArduinoRobot::IRMIDLEFT = A9;
unsigned int ArduinoRobot::IRMIDDLE = A10;
unsigned int ArduinoRobot::IRMIDRIGHT = A11;
unsigned int ArduinoRobot::IRRIGHT = A12;

unsigned int ArduinoRobot::USLEFT_TRIG = A3;
unsigned int ArduinoRobot::USLEFT_ECHO = A3;
unsigned int ArduinoRobot::USFRONT_TRIG = A1;
unsigned int ArduinoRobot::USFRONT_ECHO = A1;
unsigned int ArduinoRobot::USRIGHT_TRIG = 4;
unsigned int ArduinoRobot::USRIGHT_ECHO = 4;

unsigned int ArduinoRobot::ADDRESS_KP = 1;		
unsigned int ArduinoRobot::ADDRESS_KI = 10;
unsigned int ArduinoRobot::ADDRESS_KD = 20;
unsigned int ArduinoRobot::ADDRESS_KV = 30;
unsigned int ArduinoRobot::ADDRESS_KW = 40;
unsigned int ArduinoRobot::ADDRESS_KWOS = 50;
unsigned int ArduinoRobot::ADDRESS_IRTRSH = 60;
unsigned int ArduinoRobot::ADDRESS_USTRSH = 70;
unsigned int ArduinoRobot::ADDRESS_NVSPL = 80;
unsigned int ArduinoRobot::ADDRESS_NIRSPL = 90;
unsigned int ArduinoRobot::ADDRESS_NUSSPL = 100;
unsigned int ArduinoRobot::ADDRESS_IRL = 110;
unsigned int ArduinoRobot::ADDRESS_IRML = 120;
unsigned int ArduinoRobot::ADDRESS_IRM = 130;
unsigned int ArduinoRobot::ADDRESS_IRMR = 140;
unsigned int ArduinoRobot::ADDRESS_IRR = 150;
unsigned int ArduinoRobot::ADDRESS_PRVCMD = 160;

ArduinoRobot::ArduinoRobot()
{
}

ArduinoRobot::~ArduinoRobot()
{
}

void ArduinoRobot::taskUltraSonic(void *param)
{
	uint32_t cmd;										// Recieved command
	UltraDistSensor USLeft, USFront, USRight;
	USLeft.attach(USLEFT_TRIG, USLEFT_ECHO, 20000);		//Trigger, Echo, Timeout
	USFront.attach(USFRONT_TRIG, USFRONT_ECHO, 20000);	//Trigger, Echo, Timeout
	USRight.attach(USRIGHT_TRIG, USRIGHT_ECHO, 20000);	//Trigger, Echo, Timeout
	nUSSamples = EEPROM.readInt(ADDRESS_NUSSPL);		// Load nUSSamples from EEPROM
	filtUSLeft.resize(nUSSamples);
	filtUSFront.resize(nUSSamples);
	filtUSRight.resize(nUSSamples);
	ultrasonicThreshold = EEPROM.readDouble(ADDRESS_USTRSH);

	while (true) {
		// Around 60mSec maximum for all three ultrasonic sensors
		cmd = ulTaskNotifyTake(pdTRUE, 1);
		if (cmd == 'f') {
			filtUSLeft.resize(nUSSamples);
			filtUSFront.resize(nUSSamples);
			filtUSRight.resize(nUSSamples);
		}
		usLeft = filtUSLeft.filter(USLeft.distanceInCm());
		bUSLeft = (usLeft < ultrasonicThreshold) ? 1 : 0;
		vTaskDelay(1);
		usFront = filtUSFront.filter(USFront.distanceInCm());
		bUSFront = (usFront < ultrasonicThreshold) ? 1 : 0; 
		vTaskDelay(1);
		usRight = filtUSRight.filter(USRight.distanceInCm());
		bUSRight = (usRight < ultrasonicThreshold) ? 1 : 0; 
	}
	vTaskDelete(NULL);	// Shouldn't reach here!
}

void ArduinoRobot::taskInfraRed(void *param)
{	
	const int calibSamples = 25;					// Less then 31, overflow
	uint32_t cmd;									// Command recieved
	nIRSamples = EEPROM.readInt(ADDRESS_NIRSPL);	// Load nIRSamples from EEPROM
	infraredThreshold = EEPROM.readDouble(ADDRESS_IRTRSH);
	calibIRLeft = EEPROM.readInt(ADDRESS_IRL);
	calibIRMiddleLeft = EEPROM.readInt(ADDRESS_IRML);
	calibIRMiddle = EEPROM.readInt(ADDRESS_IRM);
	calibIRMiddleRight = EEPROM.readInt(ADDRESS_IRMR);
	calibIRRight = EEPROM.readInt(ADDRESS_IRR);
	filtIRLeft.resize(nIRSamples);
	filtIRMiddleLeft.resize(nIRSamples);
	filtIRMiddle.resize(nIRSamples);
	filtIRMiddleRight.resize(nIRSamples);
	filtIRRight.resize(nIRSamples);
	while (true) {
		// Around 600uSec for all five analog readings
		cmd = ulTaskNotifyTake(pdTRUE, 1);
		if (cmd == 'i') {
			pinMode(LED, OUTPUT);
			digitalWrite(LED, LOW);
			calibIRLeft = calibIRMiddleLeft = calibIRMiddle = calibIRMiddleRight = calibIRRight = 0;
			for (int i = 0; i < calibSamples; i++) {
				calibIRLeft += analogRead(IRLEFT);
				calibIRMiddleLeft += analogRead(IRMIDLEFT);
				calibIRMiddle += analogRead(IRMIDDLE);
				calibIRMiddleRight += analogRead(IRMIDRIGHT);
				calibIRRight += analogRead(IRRIGHT);
			}
			calibIRLeft = int(calibIRLeft / calibSamples);
			calibIRMiddleLeft = int(calibIRMiddleLeft / calibSamples);
			calibIRMiddle = int(calibIRMiddle / calibSamples);
			calibIRMiddleRight = int(calibIRMiddleRight / calibSamples);
			calibIRRight = int(calibIRRight / calibSamples);
			EEPROM.writeInt(ADDRESS_IRL, calibIRLeft);
			EEPROM.writeInt(ADDRESS_IRML, calibIRMiddleLeft);
			EEPROM.writeInt(ADDRESS_IRM, calibIRMiddle);
			EEPROM.writeInt(ADDRESS_IRMR, calibIRMiddleRight);
			EEPROM.writeInt(ADDRESS_IRR, calibIRRight);
			digitalWrite(LED, HIGH);
		}
		else if (cmd == 'f') {
			filtIRLeft.resize(nIRSamples);
			filtIRMiddleLeft.resize(nIRSamples);
			filtIRMiddle.resize(nIRSamples);
			filtIRMiddleRight.resize(nIRSamples);
			filtIRRight.resize(nIRSamples);
		}
		irLeft = filtIRLeft.filter(fabs(analogRead(IRLEFT) - calibIRLeft));
		irMiddleLeft = filtIRMiddleLeft.filter(fabs(analogRead(IRMIDLEFT) - calibIRMiddleLeft));
		irMiddle = filtIRMiddle.filter(fabs(analogRead(IRMIDDLE) - calibIRMiddle));
		irMiddleRight = filtIRMiddleRight.filter(fabs(analogRead(IRMIDRIGHT) - calibIRMiddleRight));
		irRight = filtIRRight.filter(fabs(analogRead(IRRIGHT) - calibIRRight));
		bIRLeft = (irLeft > infraredThreshold) ? 1 : 0;
		bIRMiddleLeft = (irMiddleLeft > infraredThreshold) ? 1 : 0;
		bIRMiddle = (irMiddle > infraredThreshold) ? 1 : 0;
		bIRMiddleRight = (irMiddleRight > infraredThreshold) ? 1 : 0;
		bIRRight = (irRight > infraredThreshold) ? 1 : 0;
	}
	vTaskDelete(NULL);	// Shouldn't reach here!
}

void ArduinoRobot::taskMotorControl(void *param)
{
	double inputLeft, outputLeft, setpointLeft;				// Left motor control variables
	double inputRight, outputRight, setpointRight;			// Right motor control variables
	Kp = EEPROM.readDouble(ADDRESS_KP);						// Load Kp from EEPROM
	Ki = EEPROM.readDouble(ADDRESS_KI);						// Load Ki from EEPROM
	Kd = EEPROM.readDouble(ADDRESS_KD);						// Load Kd from EEPROM
	PID pidLeftMotor(&inputLeft, &outputLeft, &setpointLeft, Kp, Ki, Kd, DIRECT);
	PID pidRightMotor(&inputRight, &outputRight, &setpointRight, Kp, Ki, Kd, DIRECT);
	pidLeftMotor.SetMode(motorsControl);					// PID mode (AUTOMATIC | MANUAL)
	pidLeftMotor.SetOutputLimits(0, 255);					// PID output limits
	pidLeftMotor.SetSampleTime(portTICK_PERIOD_MS);			// PID sample time (RTOS Tick time in mSec) = 17mSec
	pidRightMotor.SetMode(motorsControl);					// PID mode (AUTOMATIC | MANUAL)
	pidRightMotor.SetOutputLimits(0, 255);					// PID output limits
	pidRightMotor.SetSampleTime(portTICK_PERIOD_MS);		// PID sample time (RTOS Tick time in mSec) = 17mSec
	Kv = EEPROM.readDouble(ADDRESS_KV);						// Load Kv from EEPROM 
	Kw = EEPROM.readDouble(ADDRESS_KW);						// Load Kw from EEPROM
	Kwos = EEPROM.readDouble(ADDRESS_KWOS);					// Load Kwos from EEPROM
	nVSamples = EEPROM.readInt(ADDRESS_NVSPL);				// Load nVSamples from EEPROM
	filtVl.resize(nVSamples);								// Update moving average filter window size
	filtVr.resize(nVSamples);								// Update moving average filter window size
	TickType_t xPrevTime = xTaskGetTickCount();				// Previous tick time
	unsigned long currTime, prevTime = micros();			// Time bookkeeping
	double _velLeft, _velRight;								// Intermediate variables
	double deltaDist, deltaTheta;							// Linear and Angular displacement during deltaTime
	uint32_t cmd;

	while (true) {
		currTime = micros();								// Calculate sample time in uSec
		deltaTime = (currTime - prevTime) / 1000000.0;		// Sample time in Seconds
		prevTime = currTime;

		// Calculate wheels speed
		_velLeft = (encoderLeftCtr - prevEncoderLeftCtr) * SPEEDCONSTANT / deltaTime;
		prevEncoderLeftCtr = encoderLeftCtr;
		_velRight = (encoderRightCtr - prevEncoderRightCtr) * SPEEDCONSTANT / deltaTime;
		prevEncoderRightCtr = encoderRightCtr;
		velLeft = filtVl.filter(_velLeft);				// Filter left motor speed
		velRight = filtVr.filter(_velRight);			// Filter right motor speed
		linVel = (velLeft + velRight) / 2.0;			// Robot linear velocity
		angVel = (velRight - velLeft) / WHEELDIST;		// Robot angular velocity
		deltaDist = linVel*deltaTime;					// Linear displacement [cm]
		deltaTheta = angVel*deltaTime;					// Angular displacement [rad]
		x += deltaDist*cos(theta + deltaTheta / 2);		// Integrated x-position
		y += deltaDist*sin(theta + deltaTheta / 2);		// Integrated y-position
		theta += deltaTheta;								// Integrated angle
		if (theta > PI)									// Limit angle between PI and -PI
			theta = 2 * PI - theta;
		else if (theta < -PI)
			theta = 2 * PI + theta;
		pidLeftMotor.SetMode(motorsControl);			// PID mode (AUTOMATIC | MANUAL)
		pidLeftMotor.SetTunings(Kp, Ki, Kd);			// Update tunning parameters
		pidLeftMotor.SetSampleTime(deltaTime*1000.0);	// Update sample time in milliseconds
		setpointLeft = fabs(cmdVelLeft);				// Update desired setpoint
		inputLeft = fabs(velLeft);						// Update measured input
		pidLeftMotor.Compute();							// Calculate required output
		pidRightMotor.SetMode(motorsControl);			// PID mode (AUTOMATIC | MANUAL)
		pidRightMotor.SetTunings(Kp, Ki, Kd);
		pidRightMotor.SetSampleTime(deltaTime*1000.0);
		setpointRight = fabs(cmdVelRight);
		inputRight = fabs(velRight);
		pidRightMotor.Compute();

		// Apply control only if the PID mode is set to automatic
		if (motorsControl == AUTOMATIC) {
			analogWrite(ENL, outputLeft);
			analogWrite(ENR, outputRight);
		}

		// If command timeout has been specified
		if (cmdTime >= 0)
			// If specified time out has occured, stop the motors
			if (cmdTime-- == 0) {
				if (motorsControl == AUTOMATIC) {
					cmdVelLeft = 0;
					cmdVelRight = 0;
				}
				else if (motorsControl == MANUAL) {
					analogWrite(ENL, 0);
					analogWrite(ENR, 0);
				}
			}
		// Apply the recieved filter command (resize window size), if any
		cmd = ulTaskNotifyTake(pdTRUE, 0);
		if (cmd == 'f') {
			filtVl.resize(nVSamples);					// Update the number of samples
			filtVr.resize(nVSamples);
		}
		vTaskDelayUntil(&xPrevTime, 1);	// Update sample time accordingly
	}
	vTaskDelete(NULL);	// Shouldn't reach here!
}

void ArduinoRobot::taskParseCommands(void *param)
{
	/*
	This task is called periodically to process the number of bytes
	recieved by the serial port. It shall parse the following commands
	Supported Commands:
	"h?"				--> Robot settings inquiry
	"lX X=e|i|o|u|p|s"	--> Suspend/Resume robot transmission data
	"mo 100 100 [-1]"   --> Move open loop at leftPWM, rightPWM, Time
	"mc 30 0 [-1]"	     --> Move close loop at linVel,angVel,Time
	"ms"				--> Motors stop
	"rr"				--> reset robot
	"ro"				--> reset the odometry
	"sc 20 20 1"        --> set Kp Ki Kd
	"sf 10 5 3"		    --> set number of filtering window samples nVSamples, nIRSamples, nUSSamples
	"st 200 20"			--> set Ultrasonic and Infrared threshold
	"sk 1 1 0"			--> set Odometric calibration constants
	*/
	ArduinoRobot *rob = (ArduinoRobot*)param;
	char ch1, ch2;					// Intermediate variables
	double fTemp1, fTemp2, fTemp3, fTemp4;
	long lTemp1, lTemp2, lTemp3, lTemp4;
	unsigned int nBytes = 0, ticks = 0;
	bool bProcess = false;
	while (true)
	{	
		if (nBytes != Serial.available()) {
			nBytes = Serial.available();
			ticks = 0;
		}
		else {
			if (++ticks >= TIME_MS(100) || nBytes >= 2) {
				bProcess = true;
				ticks = 0;
			}
		}
		if (bProcess) {
			bProcess = false;
			ch1 = Serial.read();// Command
			ch2 = Serial.read();// Sub-command
			Serial.read();	// Discard white space
			switch (ch1)
			{
			case 'h':
				switch (ch2)	// "h?" - Robot settings
				{
				case '?':
					rob->printSettings();
					break;
				default:
					break;
				}
			case 'l':		// "l" - Transsmission commands
				if (xTaskNotify(tskPrint, ch2, eSetValueWithOverwrite) == pdTRUE) {}
				else {}
				break;
			case 'm':		// "m" - Motor commands
				switch (ch2)
				{
				case 'o':	// "mo leftPWM rightPWM [mSec]" - Open loop mode
					lTemp1 = Serial.parseFloat();
					lTemp2 = Serial.parseFloat();
					lTemp3 = floor(TIME_MS(Serial.parseFloat()));
					lTemp1 = constrain(lTemp1, -100, 100);	// -100 <= leftPWM <= +100
					lTemp2 = constrain(lTemp2, -100, 100);	// -100 <= rightPWM <= +100
					lTemp3 = constrain(lTemp3, -1, 1e6);	// 0 <= time <= 1e6
					rob->motorPWM(lTemp1, lTemp2, lTemp3);
					break;
				case 'c':	// "mc V W [mSec]" - Close loop mode
					fTemp1 = Serial.parseFloat();
					fTemp2 = Serial.parseFloat();
					lTemp3 = floor(TIME_MS(Serial.parseFloat()));
					fTemp1 = constrain(fTemp1, -100, 100);		// -100 <= V <= +100
					fTemp2 = constrain(fTemp2, -2 * PI, 2 * PI);// -2PI <= W <= +2PI
					lTemp3 = constrain(lTemp3, -1, 1e6);		// 0 <= time <= 1e6
					rob->moveRobot(fTemp1, fTemp2, lTemp3);
					break;
				case 's':	// "ms" - Stop motors
					rob->motorPWM(0, 0);
				default:	// "m?"
					break;
				}
				break;
			case 'r':		// "r" - Reset commands
				switch (ch2)
				{
				case 'i':	// "ri" - Re-calibrate infrared
					if (xTaskNotify(tskInfrared, ch2, eSetValueWithOverwrite) == pdTRUE) {}
					break;
				case 'o':	// "ro"	- Reset robot odometry
					x = 0;
					y = 0;
					theta = 0;
					encoderLeftCtr = prevEncoderLeftCtr = 0;
					encoderRightCtr = prevEncoderRightCtr = 0;
					break;
				case 'r':	// "rr"	- Reset robot
					rob->resetMe();
					break;
				default:	// "r?"
					break;
				}
				break;
			case 's':		// "s" - Transmition commands
				switch (ch2)
				{
				case 'c':	// "sc Kp Ki Kd" -  Set PID parameters
					fTemp1 = Serial.parseFloat();
					fTemp2 = Serial.parseFloat();
					fTemp3 = Serial.parseFloat();
					Kp = constrain(fTemp1, 0, 1e6);		// 0 <= Kp <= 1e6
					Ki = constrain(fTemp2, 0, 1e6);		// 0 <= Ki <= 1e6
					Kd = constrain(fTemp3, 0, 1e6);		// 0 <= Kd <= 1e6
					EEPROM.writeDouble(ADDRESS_KP, Kp);
					EEPROM.writeDouble(ADDRESS_KI, Ki);
					EEPROM.writeDouble(ADDRESS_KD, Kd);
					break;
				case 'f':	// "sf nVSamples nIRSamples nUSSamples" - Set filtering window size
					lTemp1 = Serial.parseInt();			// Issue with parseInt()!!!
					lTemp2 = Serial.parseInt();
					lTemp3 = Serial.parseInt();
					nVSamples = constrain(lTemp1, 1, 50);	// 1 <= nVSamples <= 50
					nIRSamples = constrain(lTemp2, 1, 50);	// 1 <= nIRSamples <= 50
					nUSSamples = constrain(lTemp3, 1, 10);	// 1 <= nUSSamples <= 10
					EEPROM.writeInt(ADDRESS_NVSPL, nVSamples);
					EEPROM.writeInt(ADDRESS_NIRSPL, nIRSamples);
					EEPROM.writeInt(ADDRESS_NUSSPL, nUSSamples);
					if (xTaskNotify(tskMotorControl, ch2, eSetValueWithOverwrite)) {}
					if (xTaskNotify(tskInfrared, ch2, eSetValueWithOverwrite)) {}
					if (xTaskNotify(tskUltrasonic, ch2, eSetValueWithOverwrite)) {}
					break;
				case 't':	// "sk irThresh usThresh " - Set sensor thresholds
					fTemp1 = Serial.parseFloat();
					fTemp2 = Serial.parseFloat();
					infraredThreshold = constrain(fTemp1, 0, 1023);		// 0 <= irThresh <= 1023
					ultrasonicThreshold = constrain(fTemp2, 0, 500);	// 0 <= usThresh <= 500
					EEPROM.writeDouble(ADDRESS_IRTRSH, infraredThreshold);
					EEPROM.writeDouble(ADDRESS_USTRSH, ultrasonicThreshold);
					break;
				case 'k':	// "st Kv Kw Kwos" - Set Odometric calibration constants
					fTemp1 = Serial.parseFloat();
					fTemp2 = Serial.parseFloat();
					fTemp3 = Serial.parseFloat();
					Kv = constrain(fTemp1, 0, 10);		// 0 <= Kv <= 1
					Kw = constrain(fTemp2, 0, 10);		// 0 <= Kw <= 1
					Kwos = constrain(fTemp3, -PI, PI);	// -PI <= K <= PI
					EEPROM.writeDouble(ADDRESS_KV, Kv);
					EEPROM.writeDouble(ADDRESS_KW, Kw);
					EEPROM.writeDouble(ADDRESS_KWOS, Kwos);
					break;
				default:	// "s?"
					break;
				}
				break;
			default:
				break;
			}
			while (Serial.available())
				Serial.read();	// Discard linefeed and/or carriage return characters
		}
		vTaskDelay(1);					// 17mSec
	}
	vTaskDelete(NULL);	// Shouldn't reach here!
}

void ArduinoRobot::taskPrint(void* param) {
	ArduinoRobot *rob = (ArduinoRobot*)param;
	prevCmd = EEPROM.readInt(ADDRESS_PRVCMD);	// Un-comment to initialize first time.
	char temp;
	while (true)
	{
		temp = (char)ulTaskNotifyTake(pdTRUE, 1);	// Wait 1Tick = 17mSec before sending new set of data
		if (temp) {
			prevCmd = temp;
			EEPROM.writeInt(ADDRESS_PRVCMD, prevCmd);
		}
		switch (prevCmd)
		{
		case 'e':	// "le" - Robot motors encoder data transmission mode
			rob->printMotorEncoder();
			break;
		case 'i':	// "li" - Robot infrared data transmission mode
			rob->printInfrared();
			break;
		case 'o':	// "lo" - Robot odometry data transmission mode
			rob->printOdometry();
			break;
		case 'p':	// "lp" - Robot motors PID data transmission mode
			rob->printPID();
			break;
		case 'u':	// "lu" - Robot ultrasonic data transmission mode
			rob->printUltrasonic();
			break;
		case 's':	// "ls" - Robot sensor data transmission mode
			rob->printRobotSensors();
			break;
		default:	// "l?"
			prevCmd = ' ';
			break;
		}
	}
	vTaskDelete(tskPrint);	// Shouldn't reach here!
}

void ArduinoRobot::init(double kv, double kw, double kwos, double irThresh, double usThresh)
{
	Serial.begin(115200);	// Set serial port baud rate
	Serial.setTimeout(200);// Serial read timeout in milliseconds
	pinMode(ENCRB, INPUT_PULLUP);
	pinMode(ENCLA, INPUT_PULLUP);
	pinMode(ENCLB, INPUT_PULLUP);
	pinMode(ENCRA, INPUT_PULLUP);
	pinMode(ENCRB, INPUT_PULLUP);
	attachInterrupt(0, encLeftAISR, CHANGE);
	attachInterrupt(2, encLeftBISR, CHANGE);
	attachInterrupt(1, encRightAISR, CHANGE);
	attachInterrupt(3, encRightBISR, CHANGE);
	pinMode(ENL, OUTPUT);
	pinMode(INL1, OUTPUT);
	pinMode(INL2, OUTPUT);
	pinMode(ENR, OUTPUT);
	pinMode(INR1, OUTPUT);
	pinMode(INR2, OUTPUT);
	pinMode(LED, OUTPUT);
	
	EEPROM.setMaxAllowedWrites(3e4);
	EEPROM.setMemPool(0, EEPROMSizeMega);
	//loadDefaultParameters();	// Un-comment to load default parameters first time

	xTaskCreate(taskMotorControl, "MOTORCONTROL", 1024, this, 2, &tskMotorControl);
	xTaskCreate(taskUltraSonic, "ULTRASONIC", 192, this, 1, &tskUltrasonic);
	xTaskCreate(taskInfraRed, "INFRARED", 192, this, 1, &tskInfrared);
	xTaskCreate(taskParseCommands, "PARSECOMMANDS", 1024, this, 1, NULL);
	xTaskCreate(taskPrint, "PRINT", 128, this, 1, &tskPrint);

	mtxSerial = xSemaphoreCreateMutex();
	if (mtxSerial != NULL)
	{
		if (xSemaphoreGive(mtxSerial) == pdFALSE)
		{
			// Serial.println("ERROR");
		}
	}

	//printSettings();
	//while (1);
}

void ArduinoRobot::moveRobot(double linearVelocity, double angularVelocity, long time = -1)
{
	motorsControl = AUTOMATIC;			// Enable motors PID control mode
	if (fabs(linearVelocity) >= 0.001 || fabs(angularVelocity) >= PI / 256) {
		linearVelocity = Kv*linearVelocity;
		angularVelocity = Kw*angularVelocity + Kwos;
	}
	cmdVelLeft = linearVelocity + (WHEELDIST * angularVelocity) / 2.0;
	cmdVelRight = linearVelocity - (WHEELDIST * angularVelocity) / 2.0;
	cmdTime = time;
	if (cmdVelLeft < 0) {
		digitalWrite(INL1, HIGH);
		digitalWrite(INL2, LOW);
	}
	else {
		digitalWrite(INL1, LOW);
		digitalWrite(INL2, HIGH);
	}
	if (cmdVelRight < 0) {
		digitalWrite(INR1, HIGH);
		digitalWrite(INR2, LOW);
	}
	else {
		digitalWrite(INR1, LOW);
		digitalWrite(INR2, HIGH);
	}
}

void ArduinoRobot::motorPWM(int leftPWM, int rightPWM, long time = -1) {
	motorsControl = MANUAL;			// Disable motors PID control mode
	if (leftPWM < 0) {
		digitalWrite(INL1, HIGH);
		digitalWrite(INL2, LOW);
	}
	else {
		digitalWrite(INL1, LOW);
		digitalWrite(INL2, HIGH);
	}
	if (rightPWM < 0) {
		digitalWrite(INR1, HIGH);
		digitalWrite(INR2, LOW);
	}
	else {
		digitalWrite(INR1, LOW);
		digitalWrite(INR2, HIGH);
	}
	analogWrite(ENL, map(abs(leftPWM), 0, 100, 0, 255));
	analogWrite(ENR, map(abs(rightPWM), 0, 100, 0, 255));
	cmdTime = time;
}

void ArduinoRobot::printRobotSensors(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.print(irLeft, 0); Serial.print(SEPERATOR);
		Serial.print(irMiddleLeft, 0); Serial.print(SEPERATOR);
		Serial.print(irMiddle, 0); Serial.print(SEPERATOR);
		Serial.print(irMiddleRight, 0); Serial.print(SEPERATOR);
		Serial.print(irRight, 0); Serial.print(SEPERATOR);
		Serial.print(usLeft, 0); Serial.print(SEPERATOR);
		Serial.print(usFront, 0); Serial.print(SEPERATOR);
		Serial.print(usRight, 0); Serial.print(SEPERATOR);
		Serial.print(velLeft, 2); Serial.print(SEPERATOR);
		Serial.print(velRight, 2);//Serial.print(SEPERATOR);
		Serial.println();
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
}

void ArduinoRobot::printPID(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.print(cmdVelLeft); Serial.print(SEPERATOR);
		Serial.print(velLeft); Serial.print(SEPERATOR);
		Serial.print(velRight); //Serial.print(SEPERATOR);
		//Serial.print(cmdTime); //Serial.print(SEPERATOR);
		Serial.println();
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
}

void ArduinoRobot::printMotorEncoder(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.print(encoderLeftCtr); Serial.print(SEPERATOR);
		Serial.print(encoderRightCtr); Serial.print(SEPERATOR);
		Serial.print(millis());// Serial.print(SEPERATOR);
		Serial.println();
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
}

void ArduinoRobot::printOdometry(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.print(millis()); Serial.print(SEPERATOR);
		Serial.print(deltaTime, 3); Serial.print(SEPERATOR);
		Serial.print(linVel); Serial.print(SEPERATOR);
		Serial.print(angVel*180.0 / PI); Serial.print(SEPERATOR);
		Serial.print(x); Serial.print(SEPERATOR);
		Serial.print(y); Serial.print(SEPERATOR);
		Serial.print(theta*180.0 / PI); //Serial.print(SEPERATOR);
		//Serial.print(cmdTime); //Serial.print(SEPERATOR);
		Serial.println();
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
}

void ArduinoRobot::printUltrasonic(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.print(bUSLeft, 0); Serial.print(SEPERATOR);
		Serial.print(bUSFront, 0); Serial.print(SEPERATOR);
		Serial.print(bUSRight, 0);//Serial.print(SEPERATOR);
		Serial.println();
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
}

void ArduinoRobot::printInfrared(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.print(bIRLeft, 0); Serial.print(SEPERATOR);
		Serial.print(bIRMiddleLeft, 0); Serial.print(SEPERATOR);
		Serial.print(bIRMiddle, 0); Serial.print(SEPERATOR);
		Serial.print(bIRMiddleRight, 0); Serial.print(SEPERATOR);
		Serial.print(bIRRight, 0);//Serial.print(SEPERATOR);
		Serial.println();
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
}

void ArduinoRobot::printSettings(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.println();
		Serial.print("Kp: "); Serial.print(Kp, 3); Serial.print(SEPERATOR);
		Serial.print("Ki: "); Serial.print(Ki, 3); Serial.print(SEPERATOR);
		Serial.print("Kd: "); Serial.print(Kd, 3); Serial.println();
		Serial.print("Kv: "); Serial.print(Kv, 3); Serial.print(SEPERATOR);
		Serial.print("Kw: "); Serial.print(Kw, 3); Serial.print(SEPERATOR);
		Serial.print("Kwos: "); Serial.print(Kwos, 3); Serial.println();
		Serial.print("Kir: "); Serial.print(infraredThreshold, 3); Serial.print(SEPERATOR);
		Serial.print("Kus: "); Serial.print(ultrasonicThreshold, 3); Serial.println();
		Serial.print("nVlSamples: "); Serial.print(filtVl.getWinSize()); Serial.print(SEPERATOR);
		Serial.print("nVrSamples: "); Serial.print(filtVr.getWinSize()); Serial.println();
		Serial.print("nIRSamples: "); Serial.print(filtIRMiddle.getWinSize()); Serial.print(SEPERATOR);
		Serial.print("nUSSamples: "); Serial.print(filtUSFront.getWinSize()); Serial.println();
		Serial.print("IRCalib: "); Serial.print(calibIRLeft); Serial.print(SEPERATOR); 
		Serial.print(calibIRMiddleLeft); Serial.print(SEPERATOR);
		Serial.print(calibIRMiddle); Serial.print(SEPERATOR);
		Serial.print(calibIRMiddleRight); Serial.print(SEPERATOR);
		Serial.print(calibIRRight); Serial.println();
		Serial.print("Free RAM: "); Serial.println(freeRam());
		Serial.println("h?                --> Robot settings inquiry");
		Serial.println("lX X=e|i|o|u|p|s  --> Suspend / Resume robot transmission data");
		Serial.println("mo 100 100 -1     --> Move open loop at leftPWM, rightPWM, Time");
		Serial.println("mc 30 0 -1        --> Move close loop at linVel, angVel, Time");
		Serial.println("ms                --> Motors stop");
		Serial.println("rr                --> reset robot");
		Serial.println("ro                --> reset the odometry");
		Serial.println("sc 20 20 1        --> set Kp Ki Kd");
		Serial.println("sf 10 5 3         --> set number of filtering window samples nV, nIR, nUS");
		Serial.println("st 200 20         --> set Ultrasonic and Infrared threshold");
		Serial.println("sk 1 1 0          --> set Odometric calibration constants");
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
}

void ArduinoRobot::loadParameters(void)
{
	Kp = constrain(EEPROM.readDouble(ADDRESS_KP),0,1e6);
	Ki = constrain(EEPROM.readDouble(ADDRESS_KI),0 ,1e6 );
	Kd = constrain(EEPROM.readDouble(ADDRESS_KD),0 ,1e6 );
	Kv = constrain(EEPROM.readDouble(ADDRESS_KV), 0, 1);
	Kw = constrain(EEPROM.readDouble(ADDRESS_KW), 0, 1);
	Kwos = constrain(EEPROM.readDouble(ADDRESS_KWOS), -PI, PI);
	infraredThreshold = constrain(EEPROM.readDouble(ADDRESS_IRTRSH), 0, 1023);
	ultrasonicThreshold = constrain(EEPROM.readDouble(ADDRESS_USTRSH), 0, 500);
	nVSamples = constrain(EEPROM.readInt(ADDRESS_NVSPL), 0, 20);
	nIRSamples = constrain(EEPROM.readInt(ADDRESS_NIRSPL), 0, 5);
	nUSSamples = constrain(EEPROM.readInt(ADDRESS_NUSSPL), 0, 4);
	calibIRLeft = constrain(EEPROM.readInt(ADDRESS_IRL), 0, 1023);
	calibIRMiddleLeft = constrain(EEPROM.readInt(ADDRESS_IRML), 0, 1023);
	calibIRMiddle = constrain(EEPROM.readInt(ADDRESS_IRM), 0, 1023);
	calibIRMiddleRight = constrain(EEPROM.readInt(ADDRESS_IRMR), 0, 1023);
	calibIRRight = constrain(EEPROM.readInt(ADDRESS_IRR), 0, 1023);
}

void ArduinoRobot::loadDefaultParameters(void)
{
	Kp = 20; EEPROM.writeDouble(ADDRESS_KP, Kp);
	Ki = 20; EEPROM.writeDouble(ADDRESS_KI, Ki);
	Kd = 1; EEPROM.writeDouble(ADDRESS_KD, Kd);
	Kv = 1; EEPROM.writeDouble(ADDRESS_KV, Kv);
	Kw = 1; EEPROM.writeDouble(ADDRESS_KW, Kw);
	Kwos = 0; EEPROM.writeDouble(ADDRESS_KWOS, Kwos);
	infraredThreshold = 200; EEPROM.writeDouble(ADDRESS_IRTRSH, infraredThreshold);
	ultrasonicThreshold = 20; EEPROM.writeDouble(ADDRESS_USTRSH, ultrasonicThreshold);
	nVSamples = 10; EEPROM.writeInt(ADDRESS_NVSPL, nVSamples);
	nIRSamples = 5; EEPROM.writeInt(ADDRESS_NIRSPL, nIRSamples);
	nUSSamples = 3; EEPROM.writeInt(ADDRESS_NUSSPL, nUSSamples);
	calibIRLeft = 0; EEPROM.writeInt(ADDRESS_IRL, calibIRLeft);
	calibIRMiddleLeft = 0; EEPROM.writeInt(ADDRESS_IRML, calibIRMiddleLeft);
	calibIRMiddle = 0; EEPROM.writeInt(ADDRESS_IRM, calibIRMiddle);
	calibIRMiddleRight = 0; EEPROM.writeInt(ADDRESS_IRML, calibIRMiddleRight);
	calibIRRight = 0; EEPROM.writeInt(ADDRESS_IRL, calibIRRight);
	prevCmd = ' '; EEPROM.writeInt(ADDRESS_PRVCMD, prevCmd);
}

void ArduinoRobot::saveParameters(void)
{
	Kp = constrain(Kp, 0, 1e6); EEPROM.writeDouble(ADDRESS_KP, Kp);
	Ki = constrain(Ki,0 ,1e6 ); EEPROM.writeDouble(ADDRESS_KI, Ki);
	Kd = constrain(Kd,0 ,1e6 ); EEPROM.writeDouble(ADDRESS_KD, Kd);
	Kv = constrain(Kv,0 ,10 ); EEPROM.writeDouble(ADDRESS_KV, Kv);
	Kw = constrain(Kw, 0, 10); EEPROM.writeDouble(ADDRESS_KW, Kw);
	Kwos = constrain(Kwos, -PI, PI); EEPROM.writeDouble(ADDRESS_KWOS, Kwos);
	infraredThreshold = constrain(infraredThreshold, 0,1023 ); EEPROM.writeDouble(ADDRESS_IRTRSH, infraredThreshold);
	ultrasonicThreshold = constrain(ultrasonicThreshold, 0, 500); EEPROM.writeDouble(ADDRESS_USTRSH, ultrasonicThreshold);
	nVSamples = constrain(nVSamples, 1, 50); EEPROM.writeInt(ADDRESS_NVSPL, nVSamples);
	nIRSamples = constrain(nIRSamples, 1, 50); EEPROM.writeInt(ADDRESS_NIRSPL, nIRSamples);
	nUSSamples = constrain(nUSSamples, 1, 10); EEPROM.writeInt(ADDRESS_NUSSPL, nUSSamples);
	calibIRLeft = constrain(calibIRLeft, 0, 1023); EEPROM.writeInt(ADDRESS_IRL, calibIRLeft);
	calibIRMiddleLeft = constrain(calibIRMiddleLeft, 0, 1023); EEPROM.writeInt(ADDRESS_IRML, calibIRMiddleLeft);
	calibIRMiddle = constrain(calibIRMiddle, 0, 1023); EEPROM.writeInt(ADDRESS_IRM, calibIRMiddle);
	calibIRMiddleRight = constrain(calibIRMiddleRight, 0, 1023); EEPROM.writeInt(ADDRESS_IRML, calibIRMiddleRight);
	calibIRRight = constrain(calibIRMiddleRight, 0, 1023); EEPROM.writeInt(ADDRESS_IRL, calibIRRight);
}

/*
Clockwise:			___		___
		CHA:	___|   |___|   |___
					  ___	  ___
		CHB:	  ___|   |___|   |___
	ChannelA ISR: (CHA,CHB)
	State:		  (1,0) or (0,1)
	ChannelB ISR: (CHA,CHB)
	State:		  (1,1) or (0,0)

AntiClockwise:		___		___
		CHA:	___|   |___|   |___
				  ___	  ___
		CHB:  ___|   |___|   |___
		ChannelA ISR: (CHA,CHB)
		State:		  (1,1) or (0,0)
		ChannelB ISR: (CHA,CHB)
		State:		  (1,0) or (0,1)
*/
void ArduinoRobot::encLeftAISR(void)
{
	// Maximum 4uSec to execute the ISR
	if (digitalReadFast(ENCLA) ^ digitalReadFast(ENCLB))
		encoderLeftCtr++;
	else
		encoderLeftCtr--;
}

void ArduinoRobot::encLeftBISR(void)
{
	// Maximum 4uSec to execute the ISR
	if (digitalReadFast(ENCLA) ^ digitalReadFast(ENCLB))
		encoderLeftCtr--;
	else
		encoderLeftCtr++;
}

void ArduinoRobot::encRightAISR(void)
{
	// Maximum 4uSec to execute the ISR
	if (digitalReadFast(ENCRA) ^ digitalReadFast(ENCRB))
		encoderRightCtr--;
	else
		encoderRightCtr++;
}

void ArduinoRobot::encRightBISR(void)
{
	// Maximum 4uSec to execute the ISR
	if (digitalReadFast(ENCRA) ^ digitalReadFast(ENCRB))
		encoderRightCtr++;
	else
		encoderRightCtr--;
}

int ArduinoRobot::freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void ArduinoRobot::setControllerParameters(double kp=1, double ki=0, double kd=0, unsigned int nSamples=10) {
	Kp = kp;
	Ki = ki;
	Kd = kd;
	nVSamples = nSamples;
	if (xTaskNotify(tskMotorControl, 'f', eSetValueWithOverwrite)==pdTRUE) {}
	saveParameters();
}

void ArduinoRobot::setOdometryConstants(double kv=1, double kw=1, double kwos=0) {
	Kv = kv;
	Kw = kw;
	Kwos = kwos;
	saveParameters();
}

void ArduinoRobot::setInraredSettings(double tresh = 200, unsigned int nSamples = 10) {
	infraredThreshold = tresh;
	nIRSamples = nSamples;
	if(xTaskNotify(tskInfrared,'f',eSetValueWithOverwrite)==pdTRUE){}
	saveParameters();
}

void ArduinoRobot::setUltrasonicSettings(double tresh = 20, unsigned int nSamples = 5) {
	ultrasonicThreshold= tresh;
	nUSSamples = nSamples;
	if (xTaskNotify(tskUltrasonic, 'f', eSetValueWithOverwrite) == pdTRUE) {}
	saveParameters();
}