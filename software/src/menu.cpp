#include "menu.h"



void SHOW_FULLSCREEN(const char *str)
{
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 4);
    display.print(str);
    display.display();
}
