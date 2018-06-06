/*
 Name:		BluetoothTransciever.ino
 Created:	1/20/2018 3:38:29 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description: This program is used to change the settings of a Bluetooth transciever HC-05/HC-06 connected to a
			ArduinoMega 2560 board. The Bluetooth module HC-05 is a MASTER/SLAVE module.The Role of the module 
			(Master or Slave) can be configured only by AT COMMANDS. By default the factory setting is SLAVE.
			Remember the models HC-04 or HC-06 are SLAVE only modules. To identify the model you can see the 
			pin count.If the module has 5 or 6 pins it is HC-05.If the module has only 4 pins then it is 
			HC-04 or HC-06. The slave modules can not initiate a connection to another Bluetooth device, 
			but can accept connections. Master  module can initiate a connection to other devices. 
			Cycle the power after changing baudrate.
			AT+RESET command changes the baudrate to 38400.
			------------------------------
			 ArduinoMega     HC-05/06
			 ------------------------------
			 Pin 19(RX1) --> Bluetooth TX
			 Pin 18(TX1) --> Bluetooth RX
			 Pin 2       --> EN/KEY
			 Pin 3       --> STATUS
			 ------------------------------
			https://www.itead.cc/wiki/Serial_Port_Bluetooth_Module_(Master/Slave)_:_HC-05
			http://cdn.instructables.com/ORIG/F3O/K70G/H1LWQ0PO/F3OK70GH1LWQ0PO.pdf
*/

#define TERMINAL_BAUD 115200
#define BLUETOOTH_DEFAULT_BAUD 38400
#define BLUETOOTH_DESIRED_MODE 0	// 1=Master 0=Slave 2=SlaveLoop
#define BLUETOOTH_DESIRED_NAME "MYBT-1"
#define BLUETOOTH_DESIRED_PIN "1234"

const int KEY = 2;	//KEY/EN
const int STATUS = 3;
const unsigned long BAUDS[] = { 9600,19200,38400,57600,115200 };
unsigned long baud;

void setup() {
	pinMode(KEY, OUTPUT);  // This pin will put the HC-05/06 int to to AT commands mode
	pinMode(STATUS, INPUT);// This pin get the connection status of the device  
	digitalWrite(KEY, HIGH);
	Serial.begin(TERMINAL_BAUD);
	Serial.setTimeout(100);
	Serial.print("Starting bluetooth (HC-05/06) configuration: ");
	Serial.println(digitalRead(STATUS) ? "CONNECTED" : "DISCONNECTED");
	if (digitalRead(STATUS) == false) {
		detectBaud();
		//Serial1.begin(BLUETOOTH_DEFAULT_BAUD);
		//Serial1.begin(2400);
		//getSettings();
		//setSettings();
	}
	showHelp();
}

void showHelp() {
	Serial.println("<<< Commands Reference >>>");
	Serial.println("CONNECTME | CMDMODE | DATAMODE | HELP | GETSETTINGS | DETECTBAUD | SETBAUD=XXXXXX");
	Serial.println("AT Test UART Connection");
	Serial.println("AT+RESET Reset Device, changes baud to 38400");
	Serial.println("AT+VERSION Querry firmware version");
	Serial.println("AT+ORGL Restore settings to Factory Defaults");
	Serial.println("AT+ADDR Query Device Bluetooth Address");
	Serial.println("AT+RNAME Query Remote Bluetooth Device’s Name");
	Serial.println("AT+INQ[ADD,PROFILE,RSSI] Query Nearby Discoverable Devices");
	Serial.println("AT+INQC Cancel Search for Discoverable Devices");
	Serial.println("AT+INQM=0/1,1-8,1-48 Query/Set Inquire Access Mode [standard/rssi,number of devices,timeout]");
	Serial.println("AT+PAIR=add,timeout Device Pairing");
	Serial.println("AT+ADCN Query Total Number of Device from Authenticated Device List");
	Serial.println("AT+BIND=add Query/Set Binding Bluetooth Address");
	Serial.println("AT+LINK=add Connect to a Remote Device");
	Serial.println("AT+DISC Disconnect from a Remote Device");
	Serial.println("AT+INIT Initialize SPP Profile");
	Serial.println("AT+NAME=name Query/Set Device Name");
	Serial.println("AT+ROLE=param Query/Set Device Role [0=Slave 1=Master 2=SlaveLoop]");
	Serial.println("AT+CLASS=0 Query/Set Class of Device CoD");
	Serial.println("AT+IAC=giac Query/Set Inquire Access Code");
	Serial.println("AT+PSWD=pw Query/Set Pairing Passkey");
	Serial.println("AT+UART=x,y,z [x is baudrate, y is 0=1 stop bit, 1=2 stop bits, z is 0=none, 1=odd, 2=even parity]");
	Serial.println("AT+CMODE=conn Query/Set Connection Mode [0=ConnectFixed 1=ConnectAny 2=SlaveLoop]");
	Serial.println("AT+POLAR= Query/Set LED Output Polarity");
	Serial.println("AT+PIO= Set/Reset a User I/O pin");
	Serial.println("AT+MPIO= Query/Set/Reset multiple User I/O pin");
	Serial.println("AT+IPSCAN Query/Set Scanning Parameters");
	Serial.println("AT+SNIFF Query/Set SNIFF Energy Savings Parameters");
	Serial.println("AT+SENM Query/Set Security & Encryption Modes");
	Serial.println("AT+RMSAD Delete Authenticated Device from List");
	Serial.println("AT+FSAD Find Device from Authenticated Device List");
	Serial.println("AT+MRAD Query Most Recently Used Authenticated Device");
	Serial.println("AT+STATE[INITIALIZED READY PAIRABLE PAIRED INQUIRING CONNECTING CONNECTED DISCONNECTED NUKNOW] Query Current Status of the Device");
	Serial.println("AT+ENSNIFF Enter Energy Saving mode");
	Serial.println("AT+EXSNIFF Exit Energy Saving mode");
	Serial.println();
	//at+link=11,22,987654
	//at+rname?5472,4f,9912b2
}

void detectBaud() {
	Serial.print("<<< AUTO BAUD DETECT=");
	for (int i = 0; i<sizeof(BAUDS) / sizeof(unsigned long); i++) {
		baud = BAUDS[i];
		Serial1.begin(baud);
		Serial1.setTimeout(100);
		Serial1.print("AT\r\n");
		String res = Serial1.readString();  // Invalid response
		if ((res.indexOf("AT") != -1) || 
			(res.indexOf("OK") != -1) ||
			(res.indexOf("ERROR") != -1)) 
		{	// Response recieved
			break;
		}
		Serial1.flush();
	}
	Serial.println(String(baud) + " >>>");
	//while (1) {}
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

	Serial1.print(String(String("AT+UART=") + String(BLUETOOTH_DEFAULT_BAUD) + String(",0,0\r\n")));
	Serial.print(Serial1.readString());

	Serial1.print(String(String("AT+ROLE=") + String(BLUETOOTH_DESIRED_MODE) + String("\r\n")));
	Serial.print(Serial1.readString());
}

void loop() {
	if (Serial.available()) {
		String str = Serial.readString();
		str.toUpperCase();
		if (str.indexOf("DATAMODE") != -1) {
			digitalWrite(KEY, LOW);
			Serial.print("Data Mode, Device Status:");
			Serial.println(digitalRead(STATUS) ? "CONNECTED" : "DISCONNECTED");
		} else if (str.indexOf("CMDMODE") != -1) {
			digitalWrite(KEY, HIGH);
			Serial.print("Command Mode, Device Status:");
			Serial.println(digitalRead(STATUS) ? "CONNECTED" : "DISCONNECTED");
		}else if (str.indexOf("CONNECTME") != -1) {
			digitalWrite(KEY, HIGH);
			Serial.print("Command Mode, Device Status:");
			Serial.println(digitalRead(STATUS) ? "CONNECTED" : "DISCONNECTED");
			Serial1.print("AT+LINK=,,\r\n");
		}else if (str.indexOf("HELP") != -1) {
			showHelp();
		}else if (str.indexOf("GETSETTINGS") != -1) {
			getSettings();
		}else if (str.indexOf("DETECTBAUD") != -1) {
			detectBaud();
		}else if (str.indexOf("SETBAUD=") != -1) {
			unsigned long baud = str.substring(8).toInt();
			Serial.println("Terminal Baud:" + String(baud));
			Serial1.end();
			Serial1.begin(baud);
		}else {
			Serial1.print(str);
		}
	}
	if (Serial1.available())
		Serial.write(Serial1.read());
	//Serial1.println("ddd"); Serial.println("ddd"); delay(1000);
}
