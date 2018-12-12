void lcd_menu_clear()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

void lcd_menu_display()
{
  if (LCDML.DISP_checkMenuUpdate()) {
    LCDML.DISP_clear();

    char content_text[LCD_COLS];  // save the content text of every menu element
    LCDMenuLib2_menu *tmp;
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
          if(tmp->checkType_menu() == true)
          {
            // display normal content
            LCDML_getContent(content_text, tmp->getID());
            lcd.setCursor(1, n);
            lcd.print(content_text);
          }
          else
          {
            if(tmp->checkType_dynParam()) {
              tmp->callback(n);
            }
          }
          i++;
          n++;
        }
      // try to go to the next sibling and check the number of displayed rows
      } while (((tmp = tmp->getSibling(1)) != NULL) && (i < maxi));
    }
  }

  if(LCDML.DISP_checkMenuCursorUpdate())
  {
    uint8_t n_max             = (LCDML.MENU_getChilds() >= LCD_ROWS) ? LCD_ROWS : (LCDML.MENU_getChilds());
    uint8_t scrollbar_min     = 0;
    uint8_t scrollbar_max     = LCDML.MENU_getChilds();
    uint8_t scrollbar_cur_pos = LCDML.MENU_getCursorPosAbs();
    uint8_t scroll_pos        = ((1.*n_max * LCD_ROWS) / (scrollbar_max - 1) * scrollbar_cur_pos);

    // display rows
    for (uint8_t n = 0; n < n_max; n++)
    {
      lcd.setCursor(0, n);
      if (n == LCDML.MENU_getCursorPos()) {
        lcd.write(LCD_CURSOR);
      } else {
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
        } else if (scrollbar_cur_pos == (scrollbar_max - 1)) {
          // max pos
          lcd.setCursor((LCD_COLS - 1), (n_max - 1));
          lcd.write((uint8_t)4);
        } else {
          // between
          lcd.setCursor((LCD_COLS - 1), scroll_pos / n_max);
          lcd.write((uint8_t)(scroll_pos % n_max) + 1);
        }
      }
    }
  }
}
