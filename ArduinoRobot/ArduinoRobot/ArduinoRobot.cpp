/*
 Name:		ArduinoRobot.cpp
 Created:	12/14/2017 5:41:13 PM
 Author:	ahmad.kamal
 Editor:	http://www.visualmicro.com
*/

#include "ArduinoRobot.h"

// Initialize static variables
unsigned long ArduinoRobot::encoderLeftCtr = 0, ArduinoRobot::prevEncoderLeftCtr = 0;
unsigned long ArduinoRobot::encoderRightCtr = 0, ArduinoRobot::prevEncoderRightCtr = 0;

double ArduinoRobot::usLeft = 0, ArduinoRobot::usFront = 0, ArduinoRobot::usRight = 0;
double ArduinoRobot::irLeft = 0, ArduinoRobot::irMiddleLeft = 0, ArduinoRobot::irMiddle = 0;
double ArduinoRobot::irMiddleRight = 0, ArduinoRobot::irRight = 0;
double ArduinoRobot::velLeft = 0, ArduinoRobot::velRight = 0;
double ArduinoRobot::cmdVelLeft = 0, ArduinoRobot::cmdVelRight = 0;
double ArduinoRobot::linVel = 0, ArduinoRobot::angVel = 0;
double ArduinoRobot::deltaTime = 0;
double ArduinoRobot::Kp = 70, ArduinoRobot::Ki = 0, ArduinoRobot::Kd = 0;
double ArduinoRobot::Kv = 1, ArduinoRobot::Kw = 1, ArduinoRobot::Kwos = 0;
double ArduinoRobot::infraredThreshold = 200;
double ArduinoRobot::ultrasonicThreshold = 20;
double ArduinoRobot::WHEELDIST = 17.4;
double ArduinoRobot::SPEEDCONSTANT = 1000000.0 * PI * 6.7 / 940.0;

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
		usFront = USFront.distanceInCm(); vTaskDelay(1);
		usLeft = USLeft.distanceInCm(); vTaskDelay(1);
		usRight = USRight.distanceInCm(); vTaskDelay(1);
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
	for (int i = 0; i < calibSamples; i++){
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
	PID motorLeft(&inputLeft, &outputLeft, &setpointLeft, Kp, Ki, Kd, DIRECT);	// 14, 20, 2
	PID motorRight(&inputRight, &outputRight, &setpointRight, Kp, Ki, Kd, DIRECT);
	const int winSize = 10;									// Speed moving average filter
	float buffLeft[winSize], buffRight[winSize];			// Moving average filter
	float sumLeft, sumRight;
	motorLeft.SetMode(AUTOMATIC);							// Automatic control mode of PID
	motorRight.SetMode(AUTOMATIC);
	TickType_t xPrevTime = xTaskGetTickCount();				// Previous tick time
	unsigned long currTime, prevTime = micros();			// Time bookkeeping
	motorLeft.SetSampleTime(17);							// PID sample time (RTOS Tick time in mSec)
	motorRight.SetSampleTime(17);
	while (true) {
		currTime = micros();								// Calculate sample time in uSec
		deltaTime = currTime - prevTime;
		prevTime = currTime;
		// motorRight.SetTunings(myRobot::Kp,myRobot::Ki,myRobot::Kd);	// Update PID variables
		// motorLeft.SetTunings(myRobot::Kp,myRobot::Ki,myRobot::Kd);
		// motorLeft.SetSampleTime(deltaTime/1000);
		// motorRight.SetSampleTime(deltaTime/1000);
		setpointLeft = cmdVelLeft;							// Set PID controller setpoint
		setpointRight = cmdVelRight;
		velLeft = (encoderLeftCtr - prevEncoderLeftCtr) * SPEEDCONSTANT / deltaTime;
		prevEncoderLeftCtr = encoderLeftCtr;
		velRight = (encoderRightCtr - prevEncoderRightCtr) * SPEEDCONSTANT / deltaTime;
		prevEncoderRightCtr = encoderRightCtr;
		// Apply moving average filter
		sumLeft = sumRight = 0;
		for (int i = 1; i < winSize; i++) {
			buffLeft[i - 1] = buffLeft[i];
			sumLeft += buffLeft[i];
			buffRight[i - 1] = buffRight[i];
			sumRight += buffRight[i];
		}
		buffLeft[winSize - 1] = velLeft;
		sumLeft += velLeft;
		buffRight[winSize - 1] = velRight;
		sumRight += velRight;

		inputLeft = velLeft = sumLeft / winSize;
		inputRight = velRight = sumRight / winSize;
		motorRight.Compute();
		motorLeft.Compute();
		analogWrite(ENR, outputRight);
		analogWrite(ENL, outputLeft);
		vTaskDelayUntil(&xPrevTime, 1);	// Update sample time accordingly
	}
}

void ArduinoRobot::init(double kv, double kw, double kwos, double irThresh, double usThresh)
{
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

void ArduinoRobot::moveRobot(double linVel, double angVel)
{
	if (fabs(linVel) >= 0.001 || fabs(angVel) >= PI / 256) {
		linVel = Kv*linVel;
		angVel = Kw*angVel + Kwos;
	}
	cmdVelLeft = linVel + (WHEELDIST * angVel) / 2.0;
	cmdVelRight = linVel - (WHEELDIST * angVel) / 2.0;
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

void ArduinoRobot::printRobotData(void)
{
	// Wait until serial port becomes available
	if (xSemaphoreTake(mtxSerial, portMAX_DELAY) == pdTRUE)
	{
		Serial.print(irLeft); Serial.print(' ');
		Serial.print(irMiddleLeft); Serial.print(' ');
		Serial.print(irMiddle); Serial.print(' ');
		Serial.print(irMiddleRight); Serial.print(' ');
		Serial.print(irRight); Serial.print(' ');
		Serial.print(usLeft); Serial.print(' ');
		Serial.print(usFront); Serial.print(' ');
		Serial.print(usRight); Serial.print(' ');
		Serial.print(velLeft); Serial.print(' ');
		Serial.print(velRight);
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
		Serial.print(deltaTime); Serial.print(' ');
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
		Serial.print(deltaTime); Serial.print(' ');
		Serial.print(velLeft); Serial.print(' ');
		Serial.print(velRight); Serial.print(' ');
		Serial.print(encoderLeftCtr); Serial.print(' ');
		Serial.print(encoderRightCtr);
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
		Serial.print(usLeft); Serial.print(' ');
		Serial.print(usFront); Serial.print(' ');
		Serial.print(usRight);
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
		Serial.print(irLeft); Serial.print(' ');
		Serial.print(irMiddleLeft); Serial.print(' ');
		Serial.print(irMiddle); Serial.print(' ');
		Serial.print(irMiddleRight); Serial.print(' ');
		Serial.print(irRight);
		Serial.println();
		Serial.flush();
		xSemaphoreGive(mtxSerial);
	}
}

void ArduinoRobot::encRightBISR(void)
{
	encoderRightCtr++;
}

void ArduinoRobot::encRightAISR(void)
{
	encoderRightCtr++;
}

void ArduinoRobot::encLeftBISR(void)
{
	encoderLeftCtr++;
}

void ArduinoRobot::encLeftAISR(void)
{
	encoderLeftCtr++;
}
