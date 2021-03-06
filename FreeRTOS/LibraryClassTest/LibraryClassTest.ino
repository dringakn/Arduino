/*
 Name:		LibraryClassTest.ino
 Created:	11/21/2017 9:08:10 AM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Description:	The program creates uses a custom library to control an led connected at specified pin.
 Currently two functions (blinking and fade) can be applied on the led pin. A function can
 be selected by sending a serial port command. The library creates two tasks which can be
 controlled (suspended/resume) using the serial port commands. The library encapsulate
 the task functionality.
 */

#include "LED.h"

// Obect decleration ( PinNumber, TimePeriod[mSec] )
LEDClass myLED(LED_BUILTIN, 250);

/*
	Serial event is called at the end of loop function to process the number of bytes
	recieved by the serial port. It shall parse the following commands
	"s f 100" --> set (f)ade led with 100mSec  time period
	"s b 250" --> set (b)link led with 250mSec  time period
	otherwise, suspend both tasks
*/
void serialEvent(){
	if (Serial.available() >= 4){
		char ch1 = Serial.read();
		char ch2 = Serial.read();	// Discard white space
		switch (ch1)
		{
		case 's':
			ch1 = Serial.read();
			ch2 = Serial.read();	// Discard white space
			switch (ch1)
			{
			case 'b':
				myLED.blink(Serial.parseInt());
				break;
			case 'f':
				myLED.fade(Serial.parseInt());
				break;
			default:
				myLED.stop();
				break;
			}
			break;
		default:
			myLED.stop();
			break;
		}
		while (Serial.available())
			ch1 = Serial.read();	// Discard linefeed and/or carriage return characters
	}
}

// Initilize the system
void setup() {
	Serial.begin(115200);	// Set Serial port baudrate
	Serial.setTimeout(100);	// Serial read timeout in milliseconds
	myLED.blink(250);		// Set the blinking mode with 250 mSec period
}

// the loop function shall be run as an idler task
void loop() {

}
