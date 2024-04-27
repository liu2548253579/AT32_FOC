#include "peripherals_config.h"

Adafruit_SSD1306 display(128, 32, &Wire, -1);
MPU6050 mpu6050(Wire1);



void peripherals_init(void)
{
    mpu6050.begin();
    Serial.println("MPU6050 initialized");
    display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
    Serial.println("OLED initialized");
}

void SHOW_FULLSCREEN(const char *str)
{
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 4);
    display.print(str);
    display.display();
}



void mpu6050_test(void)
{
    mpu6050.update();
    Serial.print("AngleXYZ:");
    Serial.print(mpu6050.getAngleX());
    Serial.print(",");
    Serial.print(mpu6050.getAngleY());
    Serial.print(",");
    Serial.println(mpu6050.getAngleZ());
}

void display_test(void)
{
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(1, 4);
    display.print("LAN_FOC");
    display.display();
}











