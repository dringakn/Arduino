/*
 Name:		Button Test.ino
 Created:	12 December 2018
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Purpose:	The purpose of this test program is to test buttons/switches attached to arduino .
*/

#include <Button.h>

#define ENABLE_QUIT     0
#define ENABLE_LR       0

Button btnEnter(7);	// Digital pin number where the button is attached
Button btnDown(6);	// Digital pin number where the button is attached
Button btnUp(5);	// Digital pin number where the button is attached

#if ENABLE_QUIT
Button btnQuit();	// Digital pin number where the button is attached
#endif // LCD_CONTROL_DIGITAL_ENABLE_QUIT
#if ENABLE_LR
Button btnLeft();	// Digital pin number where the button is attached
Button btnRight();	// Digital pin number where the button is attached
#endif // LCD_CONTROL_DIGITAL_ENABLE_LR

unsigned long ulButtonPressTimer = 0;
unsigned int uiButtonPressCounter = 0;

void setup() {
	Serial.begin(115200);
	btnEnter.begin();
	btnUp.begin();
	btnDown.begin();
# if ENABLE_QUIT
	btnQuit.begin();
# endif
# if ENABLE_LR
	btnLeft.begin();
	btnRight.begin();
# endif
}

void loop() {
	uint8_t but_stat = 0;
	bitWrite(but_stat, 0, btnEnter.read() == Button::PRESSED);
	bitWrite(but_stat, 1, btnUp.read() == Button::PRESSED);
	bitWrite(but_stat, 2, btnDown.read()==Button::PRESSED);
#if ENABLE_QUIT
	bitWrite(but_stat, 3, btnQuit.read() == Button::PRESSED);
#endif
#if ENABLE_LR
	bitWrite(but_stat, 4, btnLeft.read() == Button::PRESSED);
	bitWrite(but_stat, 5, btnRight.read() == Button::PRESSED);
#endif

	if (but_stat > 0) {
		if ((millis() - ulButtonPressTimer) >= 200) {
			ulButtonPressTimer = millis();
			uiButtonPressCounter++;
			if (uiButtonPressCounter==1)	// First press
			{
				if (bitRead(but_stat, 0)) { /*Enter*/Serial.println("E"); }
				if (bitRead(but_stat, 1)) { /*Up*/Serial.println("U"); }
				if (bitRead(but_stat, 2)) { /*Down*/Serial.println("D"); }
				if (bitRead(but_stat, 3)) { /*Quit*/Serial.println("Q"); }
				if (bitRead(but_stat, 4)) { /*Left*/Serial.println("L"); }
				if (bitRead(but_stat, 5)) { /*Right*/Serial.println("R"); }
			}
			else if (uiButtonPressCounter>=10)	// Hold for two second
			{
				if (bitRead(but_stat, 0)) { /*Enter*/Serial.println("E"); }
				if (bitRead(but_stat, 1)) { /*Up*/Serial.println("U"); }
				if (bitRead(but_stat, 2)) { /*Down*/Serial.println("D"); }
				if (bitRead(but_stat, 3)) { /*Quit*/Serial.println("Q"); }
				if (bitRead(but_stat, 4)) { /*Left*/Serial.println("L"); }
				if (bitRead(but_stat, 5)) { /*Right*/Serial.println("R"); }

			}
		}// ButtonPressTimer
	}
	else
	{
		uiButtonPressCounter = 0;
	}
}// loop
