#include "peripherals_config.h"

SensorData sensor_data;

Adafruit_SSD1306 display(128, 32, &Wire, -1);
MPU6050 mpu6050(Wire1);
at24c02 eeprom(0x50,Wire1);


void peripherals_init(void)
{
    mpu6050.begin();
    Serial.println("MPU6050 initialized");
    display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
    Serial.println("OLED initialized");
}


void Get_All_Sensor_Data(SensorData *sensor_dat)
{
    mpu6050.update();
    sensor_dat->Bat_val=at32_battery_voltage_read();
    sensor_dat->Key_val=KEY_Read_Debounce();
    sensor_dat->Angle_val=FOC_M0_Angle();
    sensor_dat->Angle_val1=FOC_M1_Angle();
    sensor_dat->Velocity_val=FOC_M0_Velocity();
    sensor_dat->Velocity_val1=FOC_M1_Velocity();
    sensor_dat->Current_val=FOC_M0_Current();
    sensor_dat->Current_val1=FOC_M1_Current();
    sensor_dat->Angle_X=mpu6050.getAngleX();
    sensor_dat->Angle_Y=mpu6050.getAngleY();
    sensor_dat->Angle_Z=mpu6050.getAngleZ();
    sensor_dat->Gyro_X=mpu6050.getGyroX();
    sensor_dat->Gyro_Y=mpu6050.getGyroY();
    sensor_dat->Gyro_Z=mpu6050.getGyroZ();
}

void Serial_Print_All_Data(SensorData *sensor_dat)
{
    Serial.print("Data:");
    Serial.print(sensor_dat->Angle_val);//L0
    Serial.print(",");
    Serial.print(sensor_dat->Angle_val1);//L1
    Serial.print(",");
    Serial.print(sensor_dat->Velocity_val);//L2
    Serial.print(",");
    Serial.print(sensor_dat->Velocity_val1);//L3
    Serial.print(",");
    Serial.print(sensor_dat->Current_val);//L4
    Serial.print(",");
    Serial.print(sensor_dat->Current_val1);//L5
    Serial.print(",");
    Serial.print(sensor_dat->Bat_val);//L6
    Serial.print(",");
    Serial.print(sensor_dat->Key_val);//L7
    Serial.print(",");
    Serial.print(sensor_dat->Angle_X);//L8
    Serial.print(",");
    Serial.print(sensor_dat->Angle_Y);//L9
    Serial.print(",");
    Serial.print(sensor_dat->Angle_Z);//L10
    Serial.print("\r\n");
}













