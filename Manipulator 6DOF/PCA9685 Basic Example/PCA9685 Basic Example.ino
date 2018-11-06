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

const unsigned int PWM_MIN_VAL = 0;
const unsigned int PWM_MAX_VAL = 4096;	// 2^12
const unsigned int PWM_MAX_CHANNELS = 16;
const unsigned int PWM_MIN_FREQ = 40;	// Hz
const unsigned int PWM_MAX_FREQ = 1600;	// Hz
const unsigned int PWM_FREQ = 50;		// Hz
const unsigned int SERVO_MIN_VAL = 102;
const unsigned int SERVO_MAX_VAL = 500;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

void setServoPulse(uint8_t n, float pulse) {
	// you can use this function if you'd like to set the pulse length in seconds
	// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
	float pulselength;
	pulselength = 1000000;   // 1,000,000 us per second
	pulselength /= PWM_FREQ;   // 60 Hz
	Serial.print(pulselength);
	Serial.println(" us per period");
	pulselength /= PWM_MAX_VAL;  // 12 bits of resolution
	Serial.print(pulselength);
	Serial.println(" us per bit");
	pulse *= 1000000;  // convert to us
	pulse /= pulselength;
	Serial.println(pulse);
	pwm.setPWM(n, 0, pulse);
}

void setup() {
	Serial.setTimeout(100);
	Serial.begin(115200);
	Serial.println("PCA9685 Test");
	pwm.begin();
	pwm.setPWMFreq(PWM_FREQ);	// 40-1000 Hz
	Wire.setClock(400000);		// IC2 Communication speed, 400KHz
	for (uint8_t pin = 0; pin < PWM_MAX_CHANNELS; pin++)
		pwm.setPWM(pin, 0, SERVO_MIN_VAL);	// pin#, start offset for HIGH pin state, stop offset for LOW pin state, within 4096 cycle
}

void loop() {
	if (Serial.available())
	{
		float angle = fabs(Serial.parseFloat());
		angle = constrain(angle, 0, 180) * 1000;
		unsigned int pulselen = map(angle, 0, 180000, SERVO_MIN_VAL, SERVO_MAX_VAL);
		for (uint8_t pin = 0; pin < PWM_MAX_CHANNELS; pin++)
			pwm.setPWM(pin, 0, pulselen);	// pin#, start offset for HIGH pin state, stop offset for LOW pin state, within 4096 cycle
		Serial.println("Angle:" + String(angle/1000.0) + "\tPWM:" + String(pulselen));
	}
}
