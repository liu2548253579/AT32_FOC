#include "menu.h"

MENU_ITEM main_menu;

void ShowMenu(MENU_ITEM *menu)
{static int8_t mode_Pre=4,enable_Pre=4;

if(menu->Enable)
{
    if(mode_Pre!=menu->mode||enable_Pre!=menu->Enable)
    {
        if(menu->mode==0){Menu_Show_3("Banlance");}//Banlance
        if(menu->mode==1){Menu_Show_3("Velocity");}//Velocity
        if(menu->mode==2){Menu_Show_3("Sync");}//Sync
        if(menu->mode==3){Menu_Show_3("Angle");}//Angle
        if(menu->mode==4){Menu_Show_3("Config");}//Config
        if(menu->mode==5){Menu_Show_3("Info");}//Info
    }
}
else{
    if(mode_Pre!=menu->mode||enable_Pre!=menu->Enable)
    {
        if(menu->mode==0){Menu_Show_2("->Banlance", "  Velocity");}//Banlance
        if(menu->mode==1){Menu_Show_2("  Banlance", "->Velocity");}//Velocity
        if(menu->mode==2){Menu_Show_2("->Sync", "  Angle");}//Sync
        if(menu->mode==3){Menu_Show_2("  Sync", "->Angle");}//Angle
        if(menu->mode==4){Menu_Show_2("->Config", "  Info");}//Config
        if(menu->mode==5){Menu_Show_2("  Config", "->Info");}//Info
    }
}

mode_Pre=menu->mode;
enable_Pre=menu->Enable;
if(menu->mode<0){menu->mode=5;}
if(menu->mode>=6){menu->mode=0;}   
}










void Menu_Show_1(const char *str1, const char *str2, const char *str3, const char *str4)
{//Only show 21 characters of each string
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(str1);
    display.setCursor(0, 8);
    display.print(str2);
    display.setCursor(0, 16);
    display.print(str3);
    display.setCursor(0, 24);
    display.print(str4);
    display.display();
}


void Menu_Show_2(const char *str1, const char *str2)
{//Only show 10 characters of each string
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(str1);
    display.setCursor(0, 16);
    display.print(str2);
    display.display();
}



void Menu_Show_3(const char *str)
{//Only show 7 characters of the string
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 4);
    display.print(str);
    display.display();
}
