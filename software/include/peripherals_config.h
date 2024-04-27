#ifndef __PHERIPHERALS_CONFIG_H
#define __PHERIPHERALS_CONFIG_H

#include "at32_config.h"
#include <MPU6050_tockn.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C for 128x32


extern Adafruit_SSD1306 display;
extern MPU6050 mpu6050;


void peripherals_init(void);
void SHOW_FULLSCREEN(const char *str);


#endif /* __PHERIPHERALS_CONFIG_H */

