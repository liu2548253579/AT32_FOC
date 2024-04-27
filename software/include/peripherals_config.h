#ifndef __PHERIPHERALS_CONFIG_H
#define __PHERIPHERALS_CONFIG_H

#include "at32_config.h"
#include "at32_can.h"
#include "at24c02.h"
#include <MPU6050_tockn.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "FOC.h"

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C for 128x32


extern Adafruit_SSD1306 display;
extern MPU6050 mpu6050;
extern at24c02 eeprom;
typedef struct 
{
float Angle_val;
float Angle_val1;
float Velocity_val;
float Velocity_val1;
float Current_val;
float Current_val1;
float Bat_val;
float Key_val;
float Angle_X;
float Angle_Y;
float Angle_Z;
float Gyro_X;
float Gyro_Y;
float Gyro_Z;
}SensorData;

extern SensorData sensor_data;


void peripherals_init(void);
void Get_All_Sensor_Data(SensorData *sensor_dat);
void Serial_Print_All_Data(SensorData *sensor_dat);



#endif /* __PHERIPHERALS_CONFIG_H */

