/*
 Name:		ArduinoRobot.cpp
 Created:	12/14/2017 5:41:13 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 */

#include "ArduinoRobot.h"

// Initialize static variables
long ArduinoRobot::encoderLeftCtr = 0, ArduinoRobot::prevEncoderLeftCtr = 0;
long ArduinoRobot::encoderRightCtr = 0, ArduinoRobot::prevEncoderRightCtr = 0;

int ArduinoRobot::motorsControl = AUTOMATIC;
double ArduinoRobot::usLeft = 0, ArduinoRobot::usFront = 0, ArduinoRobot::usRight = 0;
double ArduinoRobot::irLeft = 0, ArduinoRobot::irMiddleLeft = 0, ArduinoRobot::irMiddle = 0;
double ArduinoRobot::irMiddleRight = 0, ArduinoRobot::irRight = 0;
double ArduinoRobot::x = 0, ArduinoRobot::y = 0, ArduinoRobot::theta;
double ArduinoRobot::velLeft = 0, ArduinoRobot::velRight = 0;
double ArduinoRobot::cmdVelLeft = 0, ArduinoRobot::cmdVelRight = 0;
double ArduinoRobot::linVel = 0, ArduinoRobot::angVel = 0;
double ArduinoRobot::deltaTime = 0;
double ArduinoRobot::Kp = 14, ArduinoRobot::Ki = 0, ArduinoRobot::Kd = 1;
double ArduinoRobot::Kv = 1, ArduinoRobot::Kw = 1, ArduinoRobot::Kwos = 0;
double ArduinoRobot::infraredThreshold = 200;
double ArduinoRobot::ultrasonicThreshold = 20;
double ArduinoRobot::WHEELDIST = 17.4;
double ArduinoRobot::SPEEDCONSTANT = PI * 6.7 / 940.0;

MovingAverageFilter ArduinoRobot::mavgVl(10);	// N-points moving average filter
MovingAverageFilter ArduinoRobot::mavgVr(10);	// N-points moving average filter

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

ArduinoRobot::ArduinoRobot()
{
}

ArduinoRobot::~ArduinoRobot()
{
}
void ArduinoRobot::taskUltraSonic(void *param)
{
	UltraDistSensor USLeft, USFront, USRight;
	USLeft.attach(USLEFT_TRIG, USLEFT_ECHO, 20000);		//Trigger, Echo, Timeout
	USFront.attach(USFRONT_TRIG, USFRONT_ECHO, 20000);	//Trigger, Echo, Timeout
	USRight.attach(USRIGHT_TRIG, USRIGHT_ECHO, 20000);	//Trigger, Echo, Timeout
	while (true) {
		// Around 60mSec maximum for all three ultrasonic sensors
		usFront = (USFront.distanceInCm() < ultrasonicThreshold) ? 1 : 0; vTaskDelay(1);
		usLeft = (USLeft.distanceInCm() < ultrasonicThreshold) ? 1 : 0; vTaskDelay(1);
		usRight = (USRight.distanceInCm() < ultrasonicThreshold) ? 1 : 0; vTaskDelay(1);
	}
}

void ArduinoRobot::taskInfraRed(void *param)
{
	double ir_Left = 0;
	double ir_MiddleLeft = 0;
	double ir_Middle = 0;
	double ir_MiddleRight = 0;
	double ir_Right = 0;
	const int calibSamples = 100;
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	for (int i = 0; i < calibSamples; i++) {
		ir_Left += analogRead(IRLEFT);
		ir_MiddleLeft += analogRead(IRMIDLEFT);
		ir_Middle += analogRead(IRMIDDLE);
		ir_MiddleRight += analogRead(IRMIDRIGHT);
		ir_Right += analogRead(IRRIGHT);
		//vTaskDelay(1); // 17/portTICK_PERIOD_MS
	}
	ir_Left = int(ir_Left / calibSamples);
	ir_MiddleLeft = int(ir_MiddleLeft / calibSamples);
	ir_MiddleRight = int(ir_MiddleRight / calibSamples);
	ir_Middle = int(ir_Middle / calibSamples);
	ir_Right = int(ir_Right / calibSamples);
	digitalWrite(LED, HIGH);
	while (true) {
		// Around 600uSec for all five analog readings
		irLeft = (fabs(analogRead(IRLEFT) - ir_Left) > infraredThreshold) ? 1 : 0;
		irMiddleLeft = (fabs(analogRead(IRMIDLEFT) - ir_MiddleLeft) > infraredThreshold) ? 1 : 0;
		irMiddle = (fabs(analogRead(IRMIDDLE) - ir_Middle) > infraredThreshold) ? 1 : 0;
		irMiddleRight = (fabs(analogRead(IRMIDRIGHT) - ir_MiddleRight) > infraredThreshold) ? 1 : 0;
		irRight = (fabs(analogRead(IRRIGHT) - ir_Right) > infraredThreshold) ? 1 : 0;
		vTaskDelay(1);
	}
}

void ArduinoRobot::taskMotorControl(void *param)
{
	double inputLeft, outputLeft, setpointLeft;				// Left motor control variables
	double inputRight, outputRight, setpointRight;			// Right motor control variables
	PID pidLeftMotor(&inputLeft, &outputLeft, &setpointLeft, Kp, Ki, Kd, DIRECT);
	PID pidRightMotor(&inputRight, &outputRight, &setpointRight, Kp, Ki, Kd, DIRECT);
	pidLeftMotor.SetMode(motorsControl);					// PID mode (AUTOMATIC | MANUAL)
	pidLeftMotor.SetOutputLimits(15, 255);					// PID output limits
	pidLeftMotor.SetSampleTime(portTICK_PERIOD_MS);			// PID sample time (RTOS Tick time in mSec) = 17mSec
	pidRightMotor.SetMode(motorsControl);					// PID mode (AUTOMATIC | MANUAL)
	pidRightMotor.SetOutputLimits(15, 255);					// PID output limits
	pidRightMotor.SetSampleTime(portTICK_PERIOD_MS);		// PID sample time (RTOS Tick time in mSec) = 17mSec
	TickType_t xPrevTime = xTaskGetTickCount();				// Previous tick time
	unsigned long currTime, prevTime = micros();			// Time bookkeeping
	double _velLeft, _velRight;								// Intermediate variables
	double deltaDist, deltaTheta;							// Linear and Angular displacement during deltaTime
	while (true) {
		currTime = micros();								// Calculate sample time in uSec
		deltaTime = (currTime - prevTime)/1000000.0;		// Sample time in Seconds
		prevTime = currTime;

		// Calculate wheels speed
		_velLeft = (encoderLeftCtr - prevEncoderLeftCtr) * SPEEDCONSTANT / deltaTime;
		prevEncoderLeftCtr = encoderLeftCtr;
		_velRight = (encoderRightCtr - prevEncoderRightCtr) * SPEEDCONSTANT / deltaTime;
		prevEncoderRightCtr = encoderRightCtr;
		velLeft = mavgVl.filter(_velLeft);				// Filter left motor speed
		velRight = mavgVr.filter(_velRight);			// Filter right motor speed
		linVel = (velLeft + velRight) / 2.0;			// Robot linear velocity
		angVel = (velRight - velLeft) / WHEELDIST;		// Robot angular velocity
		deltaDist = linVel*deltaTime;					// Linear displacement [cm]
		deltaTheta = angVel*deltaTime;					// Angular displacement [rad]
		x += deltaDist*cos(theta + deltaTheta / 2);		// Integrated x-position
		y += deltaDist*sin(theta + deltaTheta / 2);		// Integrated y-position
		theta +=deltaTheta;								// Integrated angle
		if (theta > PI)									// Limit angle between PI and -PI
			theta = 2 * PI - theta; 
		else if (theta < -PI)
			theta = 2 * PI + theta;
		pidLeftMotor.SetMode(motorsControl);			// PID mode (AUTOMATIC | MANUAL)
		pidLeftMotor.SetTunings(Kp, Ki, Kd);			// Update tunning parameters
		pidLeftMotor.SetSampleTime(deltaTime*1000.0);	// Update sample time in milliseconds
		setpointLeft = cmdVelLeft;						// Update desired setpoint
		inputLeft = velLeft;							// Update measured input
		pidLeftMotor.Compute();							// Calculate required output
		pidRightMotor.SetMode(motorsControl);			// PID mode (AUTOMATIC | MANUAL)
		pidRightMotor.SetTunings(Kp, Ki, Kd);	
		pidRightMotor.SetSampleTime(deltaTime*1000.0);
		setpointRight = cmdVelRight;
		inputRight = velRight;
		pidRightMotor.Compute();

		// Apply control only if the PID mode is set to automatic
		if (motorsControl == AUTOMATIC) {
			analogWrite(ENL, outputLeft);
			analogWrite(ENR, outputRight);
		}
		//deltaTime = currTime;							// For profiling
		vTaskDelayUntil(&xPrevTime, 1);	// Update sample time accordingly
	}
}

void ArduinoRobot::init(double kv, double kw, double kwos, double irThresh, double usThresh)
{
	Serial.begin(115200);
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
	Kv = kv;
	Kw = kw;
	Kwos = kwos;
	infraredThreshold = irThresh;
	ultrasonicThreshold = usThresh;
	xTaskCreate(taskMotorControl, "MOTORCONTROL", 512, NULL, 2, NULL);
	xTaskCreate(taskUltraSonic, "ULTRASONIC", 128, NULL, 1, NULL);
	xTaskCreate(taskInfraRed, "INFRARED", 128, NULL, 1, NULL);
	mtxSerial = xSemaphoreCreateMutex();
	if (mtxSerial != NULL)
	{
		if (xSemaphoreGive(mtxSerial) == pdFALSE)
		{
			// Serial.println("ERROR");
		}
	}
}

void ArduinoRobot::moveRobot(double linearVelocity, double angularVelocity)
{
	motorsControl = AUTOMATIC;			// Enable motors PID control mode
	if (fabs(linearVelocity) >= 0.001 || fabs(angularVelocity) >= PI / 256) {
		linearVelocity = Kv*linearVelocity;
		angularVelocity = Kw*angularVelocity + Kwos;
	}
	cmdVelLeft = linearVelocity + (WHEELDIST * angularVelocity) / 2.0;
	cmdVelRight = linearVelocity - (WHEELDIST * angularVelocity) / 2.0;
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
	cmdVelLeft = fabs(cmdVelLeft);
	cmdVelRight = fabs(cmdVelRight);
}

void ArduinoRobot::motorPWM(int leftPWM, int rightPWM) {
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
}

void ArduinoRobot::printRobotData(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.print(irLeft, 0); Serial.print(' ');
		Serial.print(irMiddleLeft, 0); Serial.print(' ');
		Serial.print(irMiddle, 0); Serial.print(' ');
		Serial.print(irMiddleRight, 0); Serial.print(' ');
		Serial.print(irRight, 0); Serial.print(' ');
		Serial.print(usLeft, 0); Serial.print(' ');
		Serial.print(usFront, 0); Serial.print(' ');
		Serial.print(usRight, 0); Serial.print(' ');
		Serial.print(velLeft, 2); Serial.print(' ');
		Serial.print(velRight, 2);
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
		Serial.print(deltaTime, 3); Serial.print(' ');
		Serial.print(cmdVelLeft); Serial.print(' ');
		Serial.print(velLeft); Serial.print(' ');
		Serial.print(velRight);
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
		Serial.print(millis()); Serial.print(' ');
		Serial.print(encoderLeftCtr); Serial.print(' ');
		Serial.print(encoderRightCtr);
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
		Serial.print(millis()); Serial.print(' ');
		Serial.print(deltaTime, 3); Serial.print(' ');
		Serial.print(linVel); Serial.print(' ');
		Serial.print(angVel*180.0 / PI); Serial.print(' ');
		Serial.print(x); Serial.print(' ');
		Serial.print(y); Serial.print(' ');
		Serial.print(theta*180.0 / PI);
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
		Serial.print(usLeft, 0); Serial.print(' ');
		Serial.print(usFront, 0); Serial.print(' ');
		Serial.print(usRight, 0);
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
		Serial.print(irLeft, 0); Serial.print(' ');
		Serial.print(irMiddleLeft, 0); Serial.print(' ');
		Serial.print(irMiddle, 0); Serial.print(' ');
		Serial.print(irMiddleRight, 0); Serial.print(' ');
		Serial.print(irRight, 0);
		Serial.println();
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
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

