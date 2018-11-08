/*
 Name:		PCA9685_Basic_Example.ino
 Created:	11/6/2018 6:01:27 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description: This is a sample code to interface with PCA9685 based arduino sheilds used for 16, 12-bits PWM signals
			  to drive servo motors.
 */
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const unsigned char CHANNELS_MAX = 16;
const unsigned int PWM_FREQ = 50; // Hz
const unsigned int PWM_MAX = 4096;  // DN
const float PULSE_PER_USEC = ((float)PWM_FREQ * PWM_MAX) / 1.0e6;  // DN/uSec
const unsigned int SERVO_MIN = 600; // uSec
const unsigned int SERVO_MID = 1500; // uSec
const unsigned int SERVO_MAX = 2400; // uSec
const unsigned int GRIPPER_MIN = 1200;
const unsigned int GRIPPER_MAX = 1800;
const unsigned int WRIST_MIN = 600;
const unsigned int WRIST_MAX = 2400;
const unsigned int GRIPPER_ANGLE_MIN = 600;
const unsigned int GRIPPER_ANGLE_MAX = 2400;
const unsigned int LOWER_ARM_MIN = 600;
const unsigned int LOWER_ARM_MAX = 2400;
const unsigned int UPPER_ARM_MIN = 600;
const unsigned int UPPER_ARM_MAX = 2400;
const unsigned int SHOULDER_MIN = 600;
const unsigned int SHOULDER_MAX = 2400;
const unsigned int SERVO_DELAY = 10;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);
unsigned int prevServo[CHANNELS_MAX + 1];

void servoPulse(unsigned char servo, unsigned int uSec) {
	unsigned int result = constrain(uSec, SERVO_MIN, SERVO_MAX) * PULSE_PER_USEC;
	if (result < prevServo[servo]) {
		for (unsigned int temp = prevServo[servo]; temp > result; temp -= 1) {
			pwm.setPWM(servo, 0, temp);
			delay(SERVO_DELAY);
		}
	}
	else if (result > prevServo[servo]) {
		for (unsigned int temp = prevServo[servo]; temp < result; temp += 1) {
			pwm.setPWM(servo, 0, temp);
			delay(SERVO_DELAY);
		}
	}
	prevServo[servo] = result;
}

void setup() {
	pwm.begin();
	pwm.setPWMFreq(PWM_FREQ);
	Wire.setClock(400000);
	for (int i = 0; i < CHANNELS_MAX; i++) {
		prevServo[i] = SERVO_MID * PULSE_PER_USEC;
		servoPulse(i, SERVO_MID);         // Set all servos at mid position
	}
	Serial.setTimeout(100);
	Serial.begin(115200);
	Serial.println("Manipulator 6DOF");
	Serial.println("Command: Servo#[0-15] pulseWidth[500-2500]\t Example:1 1500");
}

void loop() {
	if (Serial.available()) {
		unsigned int servo = fabs(Serial.parseInt());
		unsigned int uSec = fabs(Serial.parseInt());
		servo = constrain(servo, 0, CHANNELS_MAX);
		uSec = constrain(uSec, SERVO_MIN, SERVO_MAX);
		Serial.println("Servo:" + String(servo) + "\tuSec:" + String(uSec));
		servoPulse(servo, uSec);
		while (Serial.available())
			Serial.read();
	}
}