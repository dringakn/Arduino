/*
 Name:		BluetoothTransciever.ino
 Created:	1/20/2018 3:38:29 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description: This program is used to change the settings of a 
			Bluetooth transciever HC-05/HC-06 connected to a
			ArduinoMega 2560 board.
			------------------------------
			 ArduinoMega     HC-05/06
			 ------------------------------
			 Pin 19(RX1) --> Bluetooth TX
			 Pin 18(TX1) --> Bluetooth RX
			 Pin 2       --> EN/KEY
			 Pin 3       --> STATUS
			 ------------------------------
			https://www.itead.cc/wiki/Serial_Port_Bluetooth_Module_(Master/Slave)_:_HC-05
*/

#define TERMINAL_BAUD 115200
#define BLUETOOTH_DESIRED_BAUD 57600
#define BLUETOOTH_DESIRED_NAME "MYBT-1"
#define BLUETOOTH_DESIRED_PIN "1234"

const int KEY = 2;
const int STATUS = 3;
const unsigned long BAUDS[] = { 1200,2400,4800,9600,19200,38400,57600,115200 };
unsigned long baud;

void setup() {
	pinMode(KEY, OUTPUT);  // This pin will put the HC-05/06 int to to AT commands mode
	pinMode(STATUS, INPUT);// This pin get the connection status of the device  
	digitalWrite(KEY, HIGH);
	Serial.begin(TERMINAL_BAUD);
	Serial.print("Starting bluetooth (HC-05/06) configuration: ");
	Serial.println(digitalRead(STATUS) ? "CONNECTED" : "DISCONNECTED");
	detectBaud();
	getSettings();
	setSettings();
	Serial.println("<<< Commands Reference >>>");
	Serial.println("AT+NAME : See default name");
	Serial.println("AT+ADDR : see default address");
	Serial.println("AT+VERSION : See version");
	Serial.println("AT+UART : See baudrate");
	Serial.println("AT+ROLE: See role of bt module(1=master/0=slave)");
	Serial.println("AT+RESET : Reset and exit AT mode");
	Serial.println("AT+ORGL : Restore factory settings");
	Serial.println("AT+PSWD: see default password");
	Serial.println("AT+RNAME: see remote name");
	Serial.println("AT+CMODE: ");
	Serial.println("AT+INQ: ");
	Serial.println();
}

void detectBaud() {
	Serial.println("<<< AUTO BAUD DETECT >>>");
	for (int i = 0; i<sizeof(BAUDS) / sizeof(unsigned long); i++) {
		baud = BAUDS[i];
		Serial1.begin(baud);
		Serial1.setTimeout(50);
		Serial1.println("AT");
		String res = Serial1.readString();  // Invalid response
		Serial1.println("AT");              // result = OK
		res = Serial1.readString();
		Serial.println(String(baud) + ":" + res);
		if (res.length())
			break;
	}
}

void getSettings() {
	Serial1.setTimeout(100);
	Serial.println("<<< SETTINGS >>>");

	Serial1.print("AT+VERSION\r\n");
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+NAME?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+PSWD?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+UART?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+ADDR?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+CLASS?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+IAC?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+MRAD?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+SNIFF?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+SENM?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+ADCN?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+ROLE?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+INQM?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+BIND?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+POLAR?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+MPIO?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+IPSCAN?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+CMODE?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+STATE?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+FSAD?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+INIT?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+EXSNIFF?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+PAIR?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+INQ?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+PIO?\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+RNAME?\r\n")));
	Serial.print(Serial1.readString());
	Serial.println();

	//ERROR CODES:
	//0 Command Error/Invalid Command
	//1 Results in default value
	//2 PSKEY write error
	//3 Device name is too long (>32 characters)
	//4 No device name specified (0 length)
	//5 Bluetooth address NAP is too long
	//6 Bluetooth address UAP is too long
	//7 Bluetooth address LAP is too long
	//8 PIO map not specified (0 lenght)
	//9 Invalid PIO port Number entered
	//A Device Class not specified (0 lenght)
	//B Device Class too long
	//C Inquire Access Code not Specified (0 lenght)
	//D Inquire Access Code too long
	//E Invalid Iquire Access Code entered
	//F Pairing Password not specified (0 lenght)
	//10 Pairing Password too long (> 16 characters)
	//11 Invalid Role entered
	//12 Invalid Baud Rate entered
	//13 Invalid Stop Bit entered
	//14 Invalid Parity Bit entered
	//15 No device in the Pairing List
	//16 SPP not initialized
	//17 SPP already initialized
	//18 Invalid Inquiry Mode
	//19 Inquiry Timeout occured
	//1A Invalid/zero lenght address entered
	//1B Invalid Security Mode entered
	//1C Invalid Encryption Mode entered
}

void setSettings() {
	Serial1.print(String(String("AT+NAME=") + String(BLUETOOTH_DESIRED_NAME) + String("\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+PSWD=") + String(BLUETOOTH_DESIRED_PIN) + String("\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+UART=") + String(BLUETOOTH_DESIRED_BAUD) + String(",0,0\r\n")));
	Serial.print(Serial1.readString());
}

void loop() {
	if (Serial.available())
		Serial1.write(Serial.read());
	if (Serial1.available())
		Serial.write(Serial1.read());
}
