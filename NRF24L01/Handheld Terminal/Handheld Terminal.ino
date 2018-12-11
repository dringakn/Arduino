/*
Name:		Handheld Terminal.ino
Created:	06 December 2018 11:42
Modified:	06 December 2018 11:42
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#include <LiquidCrystal.h>
#include <LCDMenuLib2.h>

const unsigned int LCD_ROWS = 2;
const unsigned int LCD_COLS = 16;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);	//(rs, e, dat4, dat5, dat6, dat7)
const unsigned int LCD_CURSOR = 0x7E;   // Cursor symbol
const unsigned int LCD_SCROLLBAR = 1;	// Enable a scrollbar

const uint8_t scroll_bar[5][8] = {
	{ B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001 }, // scrollbar top
	{ B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001 }, // scroll state 1
	{ B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001 }, // scroll state 2
	{ B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001 }, // scroll state 3
	{ B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111 }  // scrollbar bottom
};

void lcd_menu_display();
void lcd_menu_clear();
void lcd_menu_control();

LCDMenuLib2_menu LCDML_0(255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, LCD_ROWS, LCD_COLS, lcd_menu_display, lcd_menu_clear, lcd_menu_control);

void setup() {

}

void loop() {

}

void lcd_menu_clear()
{
	lcd.clear();
	lcd.setCursor(0, 0);
}

void lcd_menu_display()
/* ******************************************************************** */
{
	// update content
	// ***************
	if (LCDML.DISP_checkMenuUpdate()) {
		// clear menu
		// ***************
		LCDML.DISP_clear();

		// declaration of some variables
		// ***************
		// content variable
		char content_text[LCD_COLS];  // save the content text of every menu element
											  // menu element object
		LCDMenuLib2_menu *tmp;
		// some limit values
		uint8_t i = LCDML.MENU_getScroll();
		uint8_t maxi = LCD_ROWS + i;
		uint8_t n = 0;

		// check if this element has children
		if ((tmp = LCDML.MENU_getObj()->getChild(LCDML.MENU_getScroll())))
		{
			// loop to display lines
			do
			{
				// check if a menu element has a condition and if the condition be true
				if (tmp->checkCondition())
				{
					// check the type off a menu element
					if (tmp->checkType_menu() == true)
					{
						// display normal content
						LCDML_getContent(content_text, tmp->getID());
						lcd.setCursor(1, n);
						lcd.print(content_text);
					}
					else
					{
						if (tmp->checkType_dynParam()) {
							tmp->callback(n);
						}
					}
					// increment some values
					i++;
					n++;
				}
				// try to go to the next sibling and check the number of displayed rows
			} while (((tmp = tmp->getSibling(1)) != NULL) && (i < maxi));
		}
	}

	if (LCDML.DISP_checkMenuCursorUpdate())
	{
		// init vars
		uint8_t n_max = (LCDML.MENU_getChilds() >= LCD_ROWS) ? LCD_ROWS : (LCDML.MENU_getChilds());
		uint8_t scrollbar_min = 0;
		uint8_t scrollbar_max = LCDML.MENU_getChilds();
		uint8_t scrollbar_cur_pos = LCDML.MENU_getCursorPosAbs();
		uint8_t scroll_pos = ((1.*n_max * LCD_ROWS) / (scrollbar_max - 1) * scrollbar_cur_pos);


		// display rows
		for (uint8_t n = 0; n < n_max; n++)
		{
			//set cursor
			lcd.setCursor(0, n);

			//set cursor char
			if (n == LCDML.MENU_getCursorPos()) {
				lcd.write(LCD_CURSOR);
			}
			else {
				lcd.write(' ');
			}

			// delete or reset scrollbar
			if (LCD_SCROLLBAR == 1) {
				if (scrollbar_max > n_max) {
					lcd.setCursor((LCD_COLS - 1), n);
					lcd.write((uint8_t)0);
				}
				else {
					lcd.setCursor((LCD_COLS - 1), n);
					lcd.print(' ');
				}
			}
		}

		// display scrollbar
		if (LCD_SCROLLBAR == 1) {
			if (scrollbar_max > n_max) {
				//set scroll position
				if (scrollbar_cur_pos == scrollbar_min) {
					// min pos
					lcd.setCursor((LCD_COLS - 1), 0);
					lcd.write((uint8_t)1);
				}
				else if (scrollbar_cur_pos == (scrollbar_max - 1)) {
					// max pos
					lcd.setCursor((LCD_COLS - 1), (n_max - 1));
					lcd.write((uint8_t)4);
				}
				else {
					// between
					lcd.setCursor((LCD_COLS - 1), scroll_pos / n_max);
					lcd.write((uint8_t)(scroll_pos % n_max) + 1);
				}
			}
		}
	}
}
