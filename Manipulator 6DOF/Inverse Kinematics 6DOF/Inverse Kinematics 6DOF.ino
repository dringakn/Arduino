/*
 Name:		Inverse_Kinematics_6DOF.ino
 Created:	11/10/2018 6:59:28 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const unsigned char CHANNELS_MAX = 16;
const unsigned int PWM_FREQ = 50; // Hz
const unsigned int PWM_MAX = 4096;  // DN
const float PULSE_PER_USEC = ((float)PWM_FREQ * PWM_MAX) / 1.0e6;  // DN/uSec
const unsigned int SERVO_DELAY = 10;
const double RAD2DEG = 180.0 / PI;

const unsigned int SERVO_MIN = 600; // uSec
const unsigned int SERVO_MID = 1500; // uSec
const unsigned int SERVO_MAX = 2400; // uSec
const double X_MIN = -0.4;
const double X_MAX = 0.4;
const double Y_MIN = -0.4;
const double Y_MAX = 0.4;
const double Z_MIN = -0.4;
const double Z_MAX = 0.4;

const double BASE_SHOULDER_LENGTH = 0.18000;    // Base to shoulder
const unsigned char BASE_SHOULDER_SERVO = 0.035;
const unsigned int BASE_SHOULDER_SERVO_MIN = 600;
const unsigned int BASE_SHOULDER_SERVO_MAX = 2400;
const double BASE_SHOULDER_ANGLE_MIN = 0;
const double BASE_SHOULDER_ANGLE_MAX = 180;

const double SHOULDER_ELBOW_LENGTH = 0.10500;    // Shoulder to elbow
const unsigned char SHOULDER_ELBOW_SERVO = 2;
const unsigned int SHOULDER_ELBOW_SERVO_MIN = 600;
const unsigned int SHOULDER_ELBOW_SERVO_MAX = 2400;
const double SHOULDER_ELBOW_ANGLE_MIN = 0;
const double SHOULDER_ELBOW_ANGLE_MAX = 180;

const double ELBOW_WRIST_LENGTH = 0.10500;    // Elbow to writst
const unsigned char ELBOW_WRIST_SERVO = 3;
const unsigned int ELBOW_WRIST_SERVO_MIN = 600;
const unsigned int ELBOW_WRIST_SERVO_MAX = 2400;
const double ELBOW_WRIST_ANGLE_MIN = 0;
const double ELBOW_WRIST_ANGLE_MAX = 180;

const double WRIST_GRIPPER_LENGTH = 0.18542;    // Writst to gripper
const unsigned char WRIST_GRIPPER_SERVO = 4;
const unsigned int WRIST_GRIPPER_SERVO_MIN = 600;
const unsigned int WRIST_GRIPPER_SERVO_MAX = 2400;
const double WRIST_GRIPPER_ANGLE_MIN = 0;
const double WRIST_GRIPPER_ANGLE_MAX = 180;

const unsigned char WRIST_SERVO = 5;      // Wrist rotation
const unsigned int WRIST_SERVO_MIN = 600;
const unsigned int WRIST_SERVO_MAX = 2400;
const double WRIST_ANGLE_MIN = 0;
const double WRIST_ANGLE_MAX = 180;

const unsigned char GRIPPER_SERVO = 6;    // Gripper
const unsigned int GRIPPER_SERVO_MIN = 1200;
const unsigned int GRIPPER_SERVO_MAX = 1800;
const double GRIPPER_DISTANCE_MIN = 0;
const double GRIPPER_DISTANCE_MAX = 0.04;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);
unsigned int prevServo[CHANNELS_MAX + 1];

double fmap(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double fconstrain(double x, double x_min, double x_max)
{
	if (x <= x_min)
		return x_min;
	else if (x >= x_max)
		return x_max;
	else
		return x;
}

void moveArm(double x, double y, double z, double theta_gripper, double dist_gripper) {

	x = fconstrain(x, X_MIN, X_MAX);
	y = fconstrain(y, Y_MIN, Y_MAX);
	z = fconstrain(z, Z_MIN, Z_MAX);
	dist_gripper = fconstrain(dist_gripper, GRIPPER_DISTANCE_MIN, GRIPPER_DISTANCE_MAX);
	theta_gripper = fconstrain(theta_gripper, WRIST_GRIPPER_ANGLE_MIN, WRIST_GRIPPER_ANGLE_MAX);

	double theta_shoulder = atan2(y, x) * RAD2DEG;
	theta_shoulder = fconstrain(theta_shoulder, BASE_SHOULDER_ANGLE_MIN, BASE_SHOULDER_ANGLE_MAX);

	double r = sqrt(x * x + y * y);
	double r_prime = r - WRIST_GRIPPER_LENGTH * cos(theta_gripper);
	double z_prime = z - BASE_SHOULDER_LENGTH * sin(theta_gripper);
	double h = sqrt(r_prime * r_prime + z_prime * z_prime) / 2.0;
	double theta_elbow = asin(h / ELBOW_WRIST_LENGTH) * 2.0 * RAD2DEG;
	theta_elbow = fconstrain(theta_elbow, SHOULDER_ELBOW_ANGLE_MIN, SHOULDER_ELBOW_ANGLE_MAX);

	double theta_wrist = 180 + theta_gripper - theta_shoulder - theta_elbow;
	theta_wrist = fconstrain(theta_wrist, ELBOW_WRIST_ANGLE_MIN, ELBOW_WRIST_ANGLE_MAX);

	double theta_wrist_rot = 90;
	theta_wrist_rot = fconstrain(theta_wrist_rot, WRIST_ANGLE_MIN, WRIST_ANGLE_MAX);

	Serial.println("x:" + String(x) + "\ty:" + String(y) + "\tz:" + String(z) + "\tdist_gripper:" + String(dist_gripper) +
		"\ttheta_gripper:" + String(theta_gripper) + "\ttheta_wrist_rot:" + String(theta_wrist_rot) + "\ttheta_wrist:" + String(theta_wrist) +
		"\ttheta_shoulder:" + String(theta_shoulder) + "\ttheta_elbow:" + String(theta_elbow));

	servoPulse(BASE_SHOULDER_SERVO, fmap(theta_shoulder, BASE_SHOULDER_ANGLE_MIN, BASE_SHOULDER_ANGLE_MAX, BASE_SHOULDER_SERVO_MIN, BASE_SHOULDER_SERVO_MAX));
	servoPulse(SHOULDER_ELBOW_SERVO, fmap(theta_elbow, SHOULDER_ELBOW_ANGLE_MIN, SHOULDER_ELBOW_ANGLE_MAX, SHOULDER_ELBOW_SERVO_MIN, SHOULDER_ELBOW_SERVO_MAX));
	servoPulse(ELBOW_WRIST_SERVO, fmap(theta_wrist, ELBOW_WRIST_ANGLE_MIN, ELBOW_WRIST_ANGLE_MAX, ELBOW_WRIST_SERVO_MIN, ELBOW_WRIST_SERVO_MAX));
	servoPulse(WRIST_GRIPPER_SERVO, fmap(theta_gripper, WRIST_GRIPPER_ANGLE_MIN, WRIST_GRIPPER_ANGLE_MAX, WRIST_GRIPPER_SERVO_MIN, WRIST_GRIPPER_SERVO_MAX));
	servoPulse(WRIST_SERVO, fmap(theta_wrist_rot, WRIST_ANGLE_MIN, WRIST_ANGLE_MAX, WRIST_SERVO_MIN, WRIST_SERVO_MIN)); //!!!!
	servoPulse(GRIPPER_SERVO, fmap(dist_gripper, GRIPPER_DISTANCE_MIN, GRIPPER_DISTANCE_MAX, GRIPPER_SERVO_MIN, GRIPPER_SERVO_MAX));
}

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
	Serial.println("6DOF ARM");
}

void loop() {
	//Serial.println(fmap(90.0, 0, 180, 600, 2400)); // Test fmap
	//Serial.println(fconstrain(10, 5 , 50));         // Test fconstrain
	if (Serial.available()) {
		//Command:s 0.1 0.1 0.1 30 0.01
		if (tolower(Serial.read()) == 's') {
			//*/
			double x = Serial.parseFloat();
			double y = Serial.parseFloat();
			double z = Serial.parseFloat();
			double grip_angle = Serial.parseFloat();
			double grip_dist = Serial.parseFloat();
			Serial.println(x);
			moveArm(x, y, z, grip_angle, grip_dist);
			//*/
			/*/
			unsigned char x = Serial.parseInt();
			unsigned int y = Serial.parseInt();
			servoPulse(x, y);
			//*/
		}
		else {
			Serial.println("s x y z grip_angle grip_dist");
		}
		// Discard extra characters
		while (Serial.available())
			Serial.read();
	}
}