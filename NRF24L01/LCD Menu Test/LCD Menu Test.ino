#include <LiquidCrystal.h>
#include <LCDMenuLib2.h>

#define LCD_ROWS  2
#define LCD_COLS  16
# if(LCD_ROWS > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib2.h
# endif

#define LCD_CURSOR 0x7E   // cursor Symbol
#define LCD_SCROLLBAR 1   // enable a scrollbar

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //(RS, EN, data4, data5, data6, data7)

const uint8_t scroll_bar[5][8] = {
  {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
  {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
  {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
  {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
  {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
};

void lcd_menu_display();
void lcd_menu_clear();
void lcd_menu_control();

LCDMenuLib2_menu LCDML_0(255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, LCD_ROWS, LCD_COLS, lcd_menu_display, lcd_menu_clear, lcd_menu_control);

// LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)
LCDML_add(0, LCDML_0, 1, "Information", mFunc_information);       // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(1, LCDML_0, 2, "Time info", mFunc_timer_info);        // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(2, LCDML_0, 3, "Program", NULL);                    // NULL = no menu function
LCDML_add(3, LCDML_0_3, 1, "Program 1", NULL);                    // NULL = no menu function
LCDML_add(4, LCDML_0_3_1, 1, "P1 dummy", NULL);                    // NULL = no menu function
LCDML_add(5, LCDML_0_3_1, 2, "P1 Settings", NULL);                    // NULL = no menu function
LCDML_add(6, LCDML_0_3_1_2, 1, "Warm", NULL);                    // NULL = no menu function
LCDML_add(7, LCDML_0_3_1_2, 2, "Cold", NULL);                    // NULL = no menu function
LCDML_add(8, LCDML_0_3_1_2, 3, "Back", mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(9, LCDML_0_3_1, 3, "Back", mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(10, LCDML_0_3, 2, "Program 2", mFunc_p2);                // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(11, LCDML_0_3, 3, "Back", mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(12, LCDML_0, 4, "Special", NULL);                    // NULL = no menu function
LCDML_add(13, LCDML_0_4, 1, "Go to Root", mFunc_goToRootMenu);      // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(14, LCDML_0_4, 2, "Jump to Time info", mFunc_jumpTo_timer_info); // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add(15, LCDML_0_4, 3, "Back", mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab


// LCDMenuLib_add(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced(16, LCDML_0, 5, NULL, "Parameter", NULL, 0, _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_addAdvanced(17, LCDML_0_5, 1, NULL, "Parameter 1", mFunc_para, 10, _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_addAdvanced(18, LCDML_0_5, 2, NULL, "Parameter 2", mFunc_para, 20, _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_addAdvanced(19, LCDML_0_5, 3, NULL, "Parameter 3", mFunc_para, 30, _LCDML_TYPE_default);                    // NULL = no menu function
LCDML_add(20, LCDML_0_5, 4, "Back", mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab


// LCDMenuLib_add(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced(21, LCDML_0, 6, NULL, "", mDyn_para, 0, _LCDML_TYPE_dynParam);                     // NULL = no menu function

// LCDMenuLib_add(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced(22, LCDML_0, 7, COND_hide, "screensaver", mFunc_screensaver, 0, _LCDML_TYPE_default);       // this menu function can be found on "LCDML_display_menuFunction" tab

#define LCD_DISP_CNT    22	// menu element count - last element id

LCDML_createMenu(LCD_DISP_CNT);

void setup()
{
	lcd.begin(LCD_COLS, LCD_ROWS);
	lcd.createChar(0, (uint8_t*)scroll_bar[0]);// set special chars for scrollbar
	lcd.createChar(1, (uint8_t*)scroll_bar[1]);
	lcd.createChar(2, (uint8_t*)scroll_bar[2]);
	lcd.createChar(3, (uint8_t*)scroll_bar[3]);
	lcd.createChar(4, (uint8_t*)scroll_bar[4]);
	LCDML_setup(LCD_DISP_CNT);
	LCDML.MENU_enRollover();	// Enable Menu Rollover
	LCDML.SCREEN_enable(mFunc_screensaver, 10000); // Enable Screensaver (screensaver menu function, time to activate in 10000 ms)
	//LCDML.SCREEN_disable();
	//LCDML.OTHER_jumpToFunc(mFunc_p2); // jump to a menu function from anywhere with
}

void loop()
{
	LCDML.loop();
}
