#include "foc_config.h"




void ledcWrite (uint32_t ulPin, uint32_t ulValue)
{
    analogWrite(ulPin, ulValue);
}



void foc_init(float power_supply)
{
    FOC_Vbus(power_supply);
    //设置电机极数和传感器方向
    FOC_M0_alignSensor(7,1);
    FOC_M1_alignSensor(7,-1);

    Serial.printf("Foc_init_OK\r\n");
}











