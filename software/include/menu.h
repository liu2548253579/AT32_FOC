#ifndef MENU_H_
#define MENU_H_

#include "peripherals_config.h"


typedef struct {
    int8_t mode;
    uint8_t Enable;
    int Velocity;
    int Angle;
} MENU_ITEM;

extern MENU_ITEM main_menu;

void Menu_Show_1(const char *str1, const char *str2, const char *str3, const char *str4);
void Menu_Show_2(const char *str1, const char *str2);
void Menu_Show_3(const char *str);
void Menu_Show_data(const char *str,int data);

void ShowMenu(MENU_ITEM *menu);

#endif /* MENU_H_ */

