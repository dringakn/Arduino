#define LCD_CONTROL_CONFIG      2
/*
 LCD Menue Control Options:
 (0) Control over serial interface  with asdw_e_q
 (1) Control over one analog input
 (2) Control over 4 - 6 digital input pins (internal pullups enabled)
 (3) Control over encoder [third party lib] (Download: https://github.com/PaulStoffregen/Encoder)
 (4) Control with Keypad  [third party lib] (Download: http://playground.arduino.cc/Main/KeypadTutorial )
 (5) Control with an IR remote [third party lib] (Download: https://github.com/z3t0/Arduino-IRremote )
 (6) Control with a joystick
 (7) Control over I2C PCF8574
 */

 // *********************************************************************
 // *************** (0) CONTROL OVER SERIAL INTERFACE *******************
 // *********************************************************************
#if(LCD_CONTROL_CONFIG == 0)
# define LCD_CONTROL_SERIAL_ENTER           'e'
# define LCD_CONTROL_SERIAL_UP              'w'
# define LCD_CONTROL_SERIAL_DOWN            's'
# define LCD_CONTROL_SERIAL_LEFT            'a'
# define LCD_CONTROL_SERIAL_RIGHT           'd'
# define LCD_CONTROL_SERIAL_QUIT            'q'
void lcd_menu_control(void)
{
	if (LCDML.BT_setup()) {
		// If something must init, put in in the setup condition
		// runs only once
	}

	// check if new serial input is available
	if (Serial.available()) {
		// read one char from input buffer
		switch (Serial.read())
		{
		case LCD_CONTROL_SERIAL_ENTER:  LCDML.BT_enter(); break;
		case LCD_CONTROL_SERIAL_UP:     LCDML.BT_up();    break;
		case LCD_CONTROL_SERIAL_DOWN:   LCDML.BT_down();  break;
		case LCD_CONTROL_SERIAL_LEFT:   LCDML.BT_left();  break;
		case LCD_CONTROL_SERIAL_RIGHT:  LCDML.BT_right(); break;
		case LCD_CONTROL_SERIAL_QUIT:   LCDML.BT_quit();  break;
		default: break;
		}
	}
}


// *********************************************************************
// *************** (1) CONTROL OVER ONE ANALOG PIN *********************
// *********************************************************************
#elif(LCD_CONTROL_CONFIG == 1)
unsigned long LCD_DISP_PRESS_TIME = 0;
#define LCD_CONTROL_ANALOG_PIN              0
// when you did not use a button set the value to zero
#define LCD_CONTROL_ANALOG_ENTER_MIN        850     // Button Enter
#define LCD_CONTROL_ANALOG_ENTER_MAX        920
#define LCD_CONTROL_ANALOG_UP_MIN           520     // Button Up
#define LCD_CONTROL_ANALOG_UP_MAX           590
#define LCD_CONTROL_ANALOG_DOWN_MIN         700     // Button Down
#define LCD_CONTROL_ANALOG_DOWN_MAX         770
#define LCD_CONTROL_ANALOG_BACK_MIN         950     // Button Back
#define LCD_CONTROL_ANALOG_BACK_MAX         1020
#define LCD_CONTROL_ANALOG_LEFT_MIN         430     // Button Left
#define LCD_CONTROL_ANALOG_LEFT_MAX         500
#define LCD_CONTROL_ANALOG_RIGHT_MIN        610     // Button Right
#define LCD_CONTROL_ANALOG_RIGHT_MAX        680
void lcd_menu_control(void)
{
	if (LCDML.BT_setup()) {
		// If something must init, put in in the setup condition
		// runs only once
	}
	// check debounce timer
	if ((millis() - LCD_DISP_PRESS_TIME) >= 200) {
		LCD_DISP_PRESS_TIME = millis(); // reset debounce timer

		uint16_t value = analogRead(LCD_CONTROL_ANALOG_PIN);  // analogpin for keypad

		if (value >= LCD_CONTROL_ANALOG_ENTER_MIN && value <= LCD_CONTROL_ANALOG_ENTER_MAX) { LCDML.BT_enter(); }
		if (value >= LCD_CONTROL_ANALOG_UP_MIN && value <= LCD_CONTROL_ANALOG_UP_MAX) { LCDML.BT_up(); }
		if (value >= LCD_CONTROL_ANALOG_DOWN_MIN && value <= LCD_CONTROL_ANALOG_DOWN_MAX) { LCDML.BT_down(); }
		if (value >= LCD_CONTROL_ANALOG_LEFT_MIN && value <= LCD_CONTROL_ANALOG_LEFT_MAX) { LCDML.BT_left(); }
		if (value >= LCD_CONTROL_ANALOG_RIGHT_MIN && value <= LCD_CONTROL_ANALOG_RIGHT_MAX) { LCDML.BT_right(); }
		if (value >= LCD_CONTROL_ANALOG_BACK_MIN && value <= LCD_CONTROL_ANALOG_BACK_MAX) { LCDML.BT_quit(); }
	}
}


// *********************************************************************
// *************** (2) CONTROL OVER DIGITAL PINS ***********************
// *********************************************************************
#elif(LCD_CONTROL_CONFIG == 2)
#include <Button.h>
#define LCD_CONTROL_DIGITAL_ENABLE_QUIT     0
#define LCD_CONTROL_DIGITAL_ENABLE_LR       0
Button btnEnter(A0);	// Digital pin number where the button is attached
Button btnUp(A1);	// Digital pin number where the button is attached
Button btnDown(A2);	// Digital pin number where the button is attached
#if LCD_CONTROL_DIGITAL_ENABLE_QUIT
Button btnQuit();	// Digital pin number where the button is attached
#endif // LCD_CONTROL_DIGITAL_ENABLE_QUIT
#if LCD_CONTROL_DIGITAL_ENABLE_LR
Button btnLeft();	// Digital pin number where the button is attached
Button btnRight();	// Digital pin number where the button is attached
#endif // LCD_CONTROL_DIGITAL_ENABLE_LR
unsigned long ulButtonPressTimer = 0;
unsigned int uiButtonPressCounter = 0;

void lcd_menu_control(void)
{
	if (LCDML.BT_setup()) {
		btnEnter.begin();
		btnUp.begin();
		btnDown.begin();
# if LCD_CONTROL_DIGITAL_ENABLE_QUIT
		btnQuit.begin();
# endif
# if LCD_CONTROL_DIGITAL_ENABLE_LR
		btnLeft.begin();
		btnRight.begin();
# endif
	}
	uint8_t but_stat = 0;
	bitWrite(but_stat, 0, btnEnter.read() == Button::PRESSED);
	bitWrite(but_stat, 1, btnUp.read() == Button::PRESSED);
	bitWrite(but_stat, 2, btnDown.read() == Button::PRESSED);
#if LCD_CONTROL_DIGITAL_ENABLE_QUIT
	bitWrite(but_stat, 3, btnQuit.read() == Button::PRESSED);
#endif
#if LCD_CONTROL_DIGITAL_ENABLE_LR
	bitWrite(but_stat, 4, btnLeft.read() == Button::PRESSED);
	bitWrite(but_stat, 5, btnRight.read() == Button::PRESSED);
#endif

	if (but_stat > 0) {
		if ((millis() - ulButtonPressTimer) >= 100) {
			ulButtonPressTimer = millis();
			uiButtonPressCounter++;
			if (uiButtonPressCounter == 1)	// First press
			{
				if (bitRead(but_stat, 0)) { LCDML.BT_enter(); }
				if (bitRead(but_stat, 1)) { LCDML.BT_up(); }
				if (bitRead(but_stat, 2)) { LCDML.BT_down(); }
				if (bitRead(but_stat, 3)) { LCDML.BT_quit(); }
				if (bitRead(but_stat, 4)) { LCDML.BT_left(); }
				if (bitRead(but_stat, 5)) { LCDML.BT_right(); }
			}
			else if (uiButtonPressCounter >= 10)	// Hold for one second
			{
				if (bitRead(but_stat, 0)) { LCDML.BT_enter(); }
				if (bitRead(but_stat, 1)) { LCDML.BT_up(); }
				if (bitRead(but_stat, 2)) { LCDML.BT_down(); }
				if (bitRead(but_stat, 3)) { LCDML.BT_quit(); }
				if (bitRead(but_stat, 4)) { LCDML.BT_left(); }
				if (bitRead(but_stat, 5)) { LCDML.BT_right(); }
			}
		}// ButtonPressTimer
	}
	else
	{
		uiButtonPressCounter = 0;
	}
}

// *********************************************************************
// *************** (3) CONTROL WITH ENCODER ****************************
// *********************************************************************
#elif(LCD_CONTROL_CONFIG == 3)
  /*
   * Thanks to "MuchMore" (Arduino forum) to add this encoder functionality
   *
   * rotate left = Up
   * rotate right = Down
   * push = Enter
   * push long = Quit
   * push + rotate left = Left
   * push + rotate right = Right
   */

   /* encoder connection
	* button * (do not use an external resistor, the internal pullup resistor is used)
	* .-------o  Arduino Pin
	* |
	* |
	* o  /
	*   /
	*  /
	* o
	* |
	* '-------o   GND
	*
	* encoder * (do not use an external resistor, the internal pullup resistors are used)
	*
	* .---------------o  Arduino Pin A
	* |        .------o  Arduino Pin B
	* |        |
	* o  /     o  /
	*   /        /
	*  /        /
	* o        o
	* |        |
	* '--------o----o   GND (common pin)
	*/

#define encoder_A_pin       20    // physical pin has to be 2 or 3 to use interrupts (on mega e.g. 20 or 21), use internal pullups
#define encoder_B_pin       21    // physical pin has to be 2 or 3 to use interrupts (on mega e.g. 20 or 21), use internal pullups
#define encoder_button_pin  49    // physical pin , use internal pullup
#define LCD_CONTROL_BUTTON_LONG_PRESS    800   // ms
#define LCD_CONTROL_BUTTON_SHORT_PRESS   120   // ms
#define ENCODER_OPTIMIZE_INTERRUPTS //Only when using pin2/3 (or 20/21 on mega)
#include <Encoder.h> //for Encoder    Download:  https://github.com/PaulStoffregen/Encoder
Encoder ENCODER(encoder_A_pin, encoder_B_pin);
long  LCD_CONTROL_BUTTON_PRESS_TIME = 0;
bool  LCD_CONTROL_BUTTON_PREV = HIGH;
void lcd_menu_control(void)
{
	// If something must init, put in in the setup condition
	if (LCDML.BT_setup())
	{
		// runs only once

		// init pins
		pinMode(encoder_A_pin, INPUT_PULLUP);
		pinMode(encoder_B_pin, INPUT_PULLUP);
		pinMode(encoder_button_pin, INPUT_PULLUP);
	}

	//volatile Variable
	long g_LCDML_CONTROL_Encoder_position = ENCODER.read();
	bool button = digitalRead(encoder_button_pin);

	if (g_LCDML_CONTROL_Encoder_position <= -3) {

		if (!button)
		{
			LCDML.BT_left();
			LCD_CONTROL_BUTTON_PREV = LOW;
			LCD_CONTROL_BUTTON_PRESS_TIME = -1;
		}
		else
		{
			LCDML.BT_down();
		}
		ENCODER.write(g_LCDML_CONTROL_Encoder_position + 4);
	}
	else if (g_LCDML_CONTROL_Encoder_position >= 3)
	{

		if (!button)
		{
			LCDML.BT_right();
			LCD_CONTROL_BUTTON_PREV = LOW;
			LCD_CONTROL_BUTTON_PRESS_TIME = -1;
		}
		else
		{
			LCDML.BT_up();
		}
		ENCODER.write(g_LCDML_CONTROL_Encoder_position - 4);
	}
	else
	{
		if (!button && LCD_CONTROL_BUTTON_PREV)  //falling edge, button pressed
		{
			LCD_CONTROL_BUTTON_PREV = LOW;
			LCD_CONTROL_BUTTON_PRESS_TIME = millis();
		}
		else if (button && !LCD_CONTROL_BUTTON_PREV) //rising edge, button not active
		{
			LCD_CONTROL_BUTTON_PREV = HIGH;

			if (LCD_CONTROL_BUTTON_PRESS_TIME < 0)
			{
				LCD_CONTROL_BUTTON_PRESS_TIME = millis();
				//Reset for left right action
			}
			else if ((millis() - LCD_CONTROL_BUTTON_PRESS_TIME) >= LCD_CONTROL_BUTTON_LONG_PRESS)
			{
				LCDML.BT_quit();
			}
			else if ((millis() - LCD_CONTROL_BUTTON_PRESS_TIME) >= LCD_CONTROL_BUTTON_SHORT_PRESS)
			{
				LCDML.BT_enter();
			}
		}
	}
}

// *********************************************************************
// *************** (4) CONTROL WITH A KEYPAD ***************************
// *********************************************************************
#elif(LCD_CONTROL_CONFIG == 4)
#include <Keypad.h>
#define LCD_CONTROL_KEYPAD_ROWS 4 // Four rows
#define LCD_CONTROL_KEYPAD_COLS 3 // Three columns
char keys[LCD_CONTROL_KEYPAD_ROWS][LCD_CONTROL_KEYPAD_COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[LCD_CONTROL_KEYPAD_ROWS] = { 9, 8, 7, 6 };  // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[LCD_CONTROL_KEYPAD_COLS] = { 12, 11, 10 };  // Create the Keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, LCD_CONTROL_KEYPAD_ROWS, LCD_CONTROL_KEYPAD_COLS);
void lcd_menu_control(void)
{
	if (LCDML.BT_setup()) {
		// If something must init, put in in the setup condition
		// runs only once
	}
	char key = kpd.getKey();
	if (key)  // Check for a valid key.
	{
		switch (key)
		{
		case '#': LCDML.BT_enter(); break;
		case '2': LCDML.BT_up();    break;
		case '8': LCDML.BT_down();  break;
		case '4': LCDML.BT_left();  break;
		case '6': LCDML.BT_right(); break;
		case '*': LCDML.BT_quit();  break;
		default: break;
		}
	}
}

// *********************************************************************
// *************** (5) CONTROL WITH IR REMOTE ***************************
// *********************************************************************
#elif(LCD_CONTROL_CONFIG == 5)
#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
void lcd_menu_control(void)
{
	if (LCDML.BT_setup()) {
		// If something must init, put in in the setup condition
		// runs only once
		irrecv.enableIRIn(); // Start the receiver
	}

	if (irrecv.decode(&results))
	{
		// change in this function the IR values to your values
		// comment this line out, to check the correct code
		//Serial.println(results.value, HEX);

		// in this switch case you have to change the value 0x...1 to the correct IR code
		switch (results.value)
		{
		case 0x00000001: LCDML.BT_enter(); break;
		case 0x00000002: LCDML.BT_up();    break;
		case 0x00000003: LCDML.BT_down();  break;
		case 0x00000004: LCDML.BT_left();  break;
		case 0x00000005: LCDML.BT_right(); break;
		case 0x00000006: LCDML.BT_quit();  break;
		default: break;
		}
	}
}

// *********************************************************************
// *************** (6) CONTROL OVER JOYSTICK ***************************
// *********************************************************************
#elif(LCD_CONTROL_CONFIG == 6)
unsigned long LCD_DISP_PRESS_TIME = 0;
#define LCD_CONTROL_ANALOG_PINX A0
#define LCD_CONTROL_ANALOG_PINY A1
#define LCD_CONTROL_DIGITAL_READ 33 //don't work with u8glib

// when you did not use a button set the value to zero
#define LCD_CONTROL_ANALOG_UP_MIN 612 // Button Up
#define LCD_CONTROL_ANALOG_UP_MAX 1023
#define LCD_CONTROL_ANALOG_DOWN_MIN 0 // Button Down
#define LCD_CONTROL_ANALOG_DOWN_MAX 412
#define LCD_CONTROL_ANALOG_LEFT_MIN 612 // Button Left
#define LCD_CONTROL_ANALOG_LEFT_MAX 1023
#define LCD_CONTROL_ANALOG_RIGHT_MIN 0 // Button Right
#define LCD_CONTROL_ANALOG_RIGHT_MAX 412
void lcd_menu_control(void)
{
	if (LCDML.BT_setup()) {
		// If something must init, put in in the setup condition
		// runs only once
		pinMode(LCD_CONTROL_DIGITAL_READ, INPUT);
	}
	// check debounce timer
	if ((millis() - LCD_DISP_PRESS_TIME) >= 200) {
		LCD_DISP_PRESS_TIME = millis(); // reset debounce timer

		uint16_t valuex = analogRead(LCD_CONTROL_ANALOG_PINX);  // analogpinx
		uint16_t valuey = analogRead(LCD_CONTROL_ANALOG_PINY);  // analogpinx
		uint16_t valuee = digitalRead(LCD_CONTROL_DIGITAL_READ);  //digitalpinenter


		if (valuey >= LCD_CONTROL_ANALOG_UP_MIN && valuey <= LCD_CONTROL_ANALOG_UP_MAX) { LCDML.BT_up(); }        // up
		if (valuey >= LCD_CONTROL_ANALOG_DOWN_MIN && valuey <= LCD_CONTROL_ANALOG_DOWN_MAX) { LCDML.BT_down(); }    // down
		if (valuex >= LCD_CONTROL_ANALOG_LEFT_MIN && valuex <= LCD_CONTROL_ANALOG_LEFT_MAX) { LCDML.BT_left(); }     // left
		if (valuex >= LCD_CONTROL_ANALOG_RIGHT_MIN && valuex <= LCD_CONTROL_ANALOG_RIGHT_MAX) { LCDML.BT_right(); }    // right

		if (valuee == true) { LCDML.BT_enter(); }    // enter

		// back buttons have to be included as menu item
		// lock at the example LCDML_back_button
	}
}

// *********************************************************************
// *************** (7) CONTROL OVER PCF8574 ****************************
// *********************************************************************
#elif(LCD_CONTROL_CONFIG == 7)
unsigned long LCD_DISP_PRESS_TIME = 0;
#define PCF8574_1 0x26   #define PCF8574_1 0x26 // I2C address for the buttons
#define PCF8574_Pin0 254
#define PCF8574_Pin1 253
#define PCF8574_Pin2 251
#define PCF8574_Pin3 247
#define PCF8574_Pin4 239
#define PCF8574_Pin5 223
#define PCF8574_Pin6 191
#define PCF8574_Pin7 127
// Specify the PCF8574 pins here
#define LCD_CONTROL_PCF8574_ENABLE_QUIT    0
#define LCD_CONTROL_PCF8574_ENABLE_LR      0
#define LCD_CONTROL_PCF8574_ENTER          PCF8574_Pin1
#define LCD_CONTROL_PCF8574_UP             PCF8574_Pin2
#define LCD_CONTROL_PCF8574_DOWN           PCF8574_Pin0
#define LCD_CONTROL_PCF8574_LEFT           PCF8574_Pin2
#define LCD_CONTROL_PCF8574l_RIGHT         PCF8574_Pin2
#define LCD_CONTROL_PCF8574_QUIT           PCF8574_Pin2
void lcd_menu_control(void)
{
	if (LCDML.BT_setup()) {
		// If something must init, put in in the setup condition
		// runs only once
	}

	if ((millis() - LCD_DISP_PRESS_TIME) >= 200) {
		LCD_DISP_PRESS_TIME = millis(); // reset press time

		Wire.write(0xff); // All pins as input?
		Wire.requestFrom(PCF8574_1, 1);
		if (Wire.available()) {
			switch (Wire.read())
			{
			case LCD_CONTROL_PCF8574_ENTER:  LCDML.BT_enter(); break;
			case LCD_CONTROL_PCF8574_UP:     LCDML.BT_up();    break;
			case LCD_CONTROL_PCF8574_DOWN:   LCDML.BT_down();  break;
#if(LCD_CONTROL_PCF8574_ENABLE_QUIT == 1)
			case LCD_CONTROL_PCF8574_LEFT:   LCDML.BT_left();  break;
#endif
#if(LCD_CONTROL_PCF8574_ENABLE_LR   == 1)
			case LCD_CONTROL_PCF8574l_RIGHT: LCDML.BT_right(); break;
			case _LCDML_CONTROL_PCF8574_quit:   LCDML.BT_quit();  break;
#endif
			default: break;
			}
		}
	}
}

#else
#error LCD_CONTROL_CONFIG is not defined or not in range
#endif
