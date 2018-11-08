/*
 Name:		Roboclaw_Agribot_Tester.ino
 Created:	11/8/2018 9:47:26 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:
 */

#include <SoftwareSerial.h>
#include "RoboClaw.h"

unsigned int NRC = 4;
const unsigned long BAUD = 115200;
const unsigned long TIMEOUT = 10000;
const double Ix = 0.2360; // Longitudinal wheel offset from robot center [m]
const double Iy = 0.2645; // Lateral wheel offset from robot center [m]
const double Rw = 0.0790; // Wheel Radius [m]
const double QPPR = 908; // Quadrature pulses per revolution
const double QPPM = QPPR / (2 * PI * Rw); // Quadrature pulses per meter
const double QPPRAD = QPPR / (2 * PI); // Quadrature pulses per Radian
unsigned long scanDelay = 1000;

RoboClaw RC(&Serial1, TIMEOUT);   // RX1[19]->S2, TX1[18]->S1
//*
SoftwareSerial serial(10, 11);  // RX[10]->S2, TX[11]->S1
RoboClaw RC(&serial, TIMEOUT);
//*/

struct control {
	float kp, ki, kd;
	int32_t setpoint;
	uint32_t qpps, maxi, deadband, maxpos, minpos;
};

struct motor {
	control vel, pos; // Velocity and Position Controller parameters
	uint32_t velocity, acceleration;  // Desired velocity, acceleration/deacceleration for position control
	uint32_t current, depth; // Roboclaw sensor
	int32_t encoder, speed; // Motor senors
	uint8_t stat;    // Status flag
	bool valid;       // Sent command status
};

struct roboclaw {
	motor m1, m2;
	uint8_t address;
	uint16_t logicVoltage, batteryVoltage;
	uint32_t temperature;
	uint8_t s3_mode, s4_mode, s5_mode;
};


const float controlSettings[4][13] = {
	// vKp,     vKi,   vKd, vQpps, pKp,  pKi,pKd,piMax, pDeadband, pMaxPos, pMinPos, paccel, pvelocity
	{ 1000.0000, 1000.0000, 0, 908, 100.0, 1.0, 0, 0, 0, 50, -50, 50, 50 },
{ 1000.0000, 1000.0000, 0, 908, 100.0, 1.0, 0, 0, 0, 50, -50, 50, 50 },
{ 1000.0000, 1000.0000, 0, 908, 100.0, 1.0, 0, 0, 0, 50, -50, 50, 50 },
{ 1000.0000, 1000.0000, 0, 908, 100.0, 1.0, 0, 0, 0, 50, -50, 50, 50 }
};

roboclaw rc[4];

bool initializeRoboClaws(unsigned long baud, unsigned long timeout) {
	RC.begin(baud);
	//Set Address Values
	for (int i = 0; i < NRC; i++)
	{
		rc[i].address = 0x80 + 2 * i;
		//Set Velocity PID Constant
		rc[i].m1.vel.kp = controlSettings[i][0];
		rc[i].m1.vel.ki = controlSettings[i][1];
		rc[i].m1.vel.kd = controlSettings[i][2];
		rc[i].m1.vel.qpps = controlSettings[i][3];
		rc[i].m1.acceleration = controlSettings[i][11];
		rc[i].m1.velocity = controlSettings[i][12];
		//Set Position PID Constants
		rc[i].m2.pos.kp = controlSettings[i][4];
		rc[i].m2.pos.ki = controlSettings[i][5];
		rc[i].m2.pos.kd = controlSettings[i][6];
		rc[i].m2.pos.maxi = controlSettings[i][7];
		rc[i].m2.pos.deadband = controlSettings[i][8];
		rc[i].m2.pos.maxpos = controlSettings[i][9];
		rc[i].m2.pos.minpos = controlSettings[i][10];
		rc[i].m2.acceleration = controlSettings[i][11];
		rc[i].m2.velocity = controlSettings[i][12];
		//Set Position and Velocity PID (m1 = velocity, m2 = position)
		RC.ResetEncoders(rc[i].address);
		RC.SetEncM1(rc[i].address, 0);
		RC.SetEncM2(rc[i].address, 0);
		//RC.SetLogicVoltages(rc[i].address, 5, 34);
		//RC.SetMainVoltages(rc[i].address, 5, 34);
		//RC.SetM1MaxCurrent(rc[i].address, 15);
		//RC.SetM2MaxCurrent(rc[i].address, 15);
		RC.SetM1VelocityPID(rc[i].address, rc[i].m1.vel.kp, rc[i].m1.vel.ki, rc[i].m1.vel.kd, rc[i].m1.vel.qpps);
		RC.SetM2VelocityPID(rc[i].address, 0, 0, 0, 50);
		RC.SetM2PositionPID(rc[i].address, rc[i].m2.pos.kp, rc[i].m2.pos.ki, rc[i].m2.pos.kd, rc[i].m2.pos.maxi, rc[i].m2.pos.deadband, rc[i].m2.pos.minpos, rc[i].m2.pos.maxpos);
		//RC.WriteNVM(rc[i].address);
	}
	return true;
}

bool readRoboClaws(void) {
	static uint32_t tempUINT32;
	static uint16_t tempUINT16;
	static int16_t tempINT16_1, tempINT16_2;
	static uint8_t tempUINT8_1, tempUINT8_2, tempUINT8_3;

	for (int i = 0; i < NRC; i++) {
		tempUINT32 = RC.ReadSpeedM1(rc[i].address, &rc[i].m1.stat, &rc[i].m1.valid);
		if (rc[i].m1.valid)
			rc[i].m1.speed = tempUINT32;
		else
			rc[i].m1.speed = 0;

		tempUINT32 = RC.ReadSpeedM2(rc[i].address, &rc[i].m2.stat, &rc[i].m2.valid);
		if (rc[i].m2.valid)
			rc[i].m2.speed = tempUINT32;
		else
			rc[i].m2.speed = 0;

		tempUINT32 = RC.ReadEncM1(rc[i].address, &rc[i].m1.stat, &rc[i].m1.valid);
		if (rc[i].m1.valid)
			rc[i].m1.encoder = tempUINT32;
		else
			rc[i].m1.encoder = 0;

		tempUINT32 = RC.ReadEncM2(rc[i].address, &rc[i].m2.stat, &rc[i].m2.valid);
		if (rc[i].m2.valid)
			rc[i].m2.encoder = tempUINT32;
		else
			rc[i].m2.encoder = 0;

		if (RC.ReadCurrents(rc[i].address, tempINT16_1, tempINT16_2)) {
			rc[i].m1.current = tempINT16_1;
			rc[i].m2.current = tempINT16_2;
		}
		else {
			rc[i].m1.current = 0;
			rc[i].m2.current = 0;
		}

		tempUINT16 = RC.ReadMainBatteryVoltage(rc[i].address, &rc[i].m1.valid);
		if (rc[i].m1.valid)
			rc[i].batteryVoltage = tempUINT16;
		else
			rc[i].batteryVoltage = 0;

		tempUINT16 = RC.ReadLogicBatteryVoltage(rc[i].address, &rc[i].m1.valid);
		if (rc[i].m1.valid)
			rc[i].logicVoltage = tempUINT16;
		else
			rc[i].logicVoltage = 0;

		if (RC.ReadTemp(rc[i].address, tempUINT16))
			rc[i].temperature = tempUINT16;
		else
			rc[i].temperature = 0;

		if (RC.GetPinFunctions(rc[i].address, tempUINT8_1, tempUINT8_2, tempUINT8_3))
		{
			rc[i].s3_mode = tempUINT8_1;
			rc[i].s4_mode = tempUINT8_2;
			rc[i].s5_mode = tempUINT8_3;
		}
		else {
			rc[i].s3_mode = 0;
			rc[i].s4_mode = 0;
			rc[i].s5_mode = 0;
		}

	}
	return true;
}

void serialEvent() {
	if (Serial.available() >= 2) {
		char ch1 = tolower(Serial.read());
		char ch2 = tolower(Serial.read());
		float fvel, facc;
		int id, add, nrc;
		switch (ch1) {
		case 'w':
			switch (ch2) {
			case 'c': //wc v a  -> Move robot @V,A
				fvel = Serial.parseFloat();
				facc = Serial.parseFloat();
				fvel = constrain(fvel, -5 * QPPR, 5 * QPPR);
				facc = constrain(facc, -5 * QPPR, 5 * QPPR);
				for (int i = 0; i < NRC; i++) {
					RC.SpeedAccelM1(rc[i].address, facc, fvel);
				}
				break;
			case 'e': //we -> reset encoders
				RC.ResetEncoders(rc[0].address);
				RC.ResetEncoders(rc[1].address);
				RC.ResetEncoders(rc[2].address);
				RC.ResetEncoders(rc[3].address);
				break;
			default:
				break;
			}
			break;
		case 'r':
			switch (ch2) {
			case 'p': //rp -> Read PID
				Serial.println("PID->RX[X]:vKp,vKi,vKd,QPPS,pKp,pKi,pKd,KiMax,DeadZone,pMin,pMax");
				Serial.flush();
				for (int i = 0; i < NRC; i++) {
					RC.ReadM1VelocityPID(rc[i].address, rc[i].m1.vel.kp, rc[i].m1.vel.ki, rc[i].m1.vel.kd, rc[i].m1.vel.qpps);
					RC.ReadM2PositionPID(rc[i].address, rc[i].m2.pos.kp, rc[i].m2.pos.ki, rc[i].m2.pos.kd, rc[i].m2.pos.maxi, rc[i].m2.pos.deadband, rc[i].m2.pos.minpos, rc[i].m2.pos.maxpos);
					Serial.print("PID->RX[" + String(i) + "]:" +
						String(rc[i].m1.vel.kp) + "," +
						String(rc[i].m1.vel.ki) + "," +
						String(rc[i].m1.vel.kd) + "," +
						String(rc[i].m1.vel.qpps) + "," +
						String(rc[i].m2.pos.kp) + ",");
					Serial.flush();
					Serial.println(String(rc[i].m2.pos.ki) + "," +
						String(rc[i].m2.pos.kd) + "," +
						String(rc[i].m2.pos.maxi) + "," +
						String(rc[i].m2.pos.deadband) + "," +
						String((int32_t)rc[i].m2.pos.minpos) + "," +
						String(rc[i].m2.pos.maxpos));
					Serial.flush();
				}
				break;
			case 'v': // rv-> Read version
				for (int i = 0; i < NRC; i++)
					readRoboClawVersion(rc[i].address);
				break;
			default:
				break;
			}
			break;
		case 's':
			switch (ch2) {
			case 'a': // sa-> Change address of roboclaw
				id = Serial.parseInt();
				add = Serial.parseInt();
				id = constrain(id, 0, 4);
				add = constrain(add, 128, 128 + 8);
				rc[id].address = add;
				Serial.println("RC " + String(id) + " new address:" + String(add));
				break;
			case 'd': // sd-> delay for roboclaw reading
				scanDelay = fabs(Serial.parseInt());
				Serial.println("Scan Delay:" + String(scanDelay));
				break;
			case 'n': // sn-> Number of roboclaws to be read
				nrc = Serial.parseInt();
				NRC = constrain(nrc, 0, 4);
				Serial.println("Number of Roboclaws:" + String(NRC));
				break;
			case 'v': // sv-> Save parameters into internal EEPROM
				for (int i = 0; i < NRC; i++)
					RC.WriteNVM(rc[i].address);
				Serial.println("Parameters saved.");
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		while (Serial.available())
			Serial.read();
	}
}

void readRoboClawVersion(uint8_t address) {
	char buff[48];
	memset(buff, ' ', sizeof(buff));
	Serial.print(String(millis()) + "->RC[" + String(address, HEX) + "]:Version ");
	if (RC.ReadVersion(address, buff)) {
		Serial.print(buff);
	}
	else {
		Serial.println("Failed");
	}
}

void setup() {
	Serial.setTimeout(100);
	Serial.begin(BAUD);    //Open robot serial port
	initializeRoboClaws(BAUD, TIMEOUT); // Initialize roboclaws
}

void loop()
{
	delay(scanDelay);
	readRoboClaws();
	Serial.println("Time->RX[ADD]:LB,MB,TP,I1,I2,V1,V2,C1,C2,S3,S4,S5");
	for (int i = 0; i < NRC; i++) {
		Serial.println(String(millis()) + "->RC[" + String(rc[i].address, HEX) + "]:" +
			String(rc[i].logicVoltage / 10.0) + "," +
			String(rc[i].batteryVoltage / 10.0) + "," +
			String(rc[i].temperature / 10.0) + "," +
			String(rc[i].m1.current / 100.0) + "," +
			String(rc[i].m2.current / 100.0) + "," +
			String(rc[i].m1.speed) + "," +
			String(rc[i].m2.speed) + "," +
			String(rc[i].m1.encoder) + "," +
			String(rc[i].m2.encoder) + "," +
			String(rc[i].s3_mode, HEX) + "," +
			String(rc[i].s4_mode, HEX) + "," +
			String(rc[i].s5_mode, HEX)
		);
	}
	Serial.println();
}