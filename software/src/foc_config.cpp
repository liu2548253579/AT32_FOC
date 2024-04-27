#include "foc_config.h"


void Foc_Pin_Init(void)
{
    pinMode(PA8,OUTPUT);pinMode(PA9,OUTPUT);pinMode(PA10,OUTPUT);//初始化电机一引脚
    pinMode(PA1,OUTPUT);pinMode(PA2,OUTPUT);pinMode(PA3,OUTPUT);//初始化电机二引脚
    digitalWrite(PA8, LOW);digitalWrite(PA9, LOW);digitalWrite(PA10, LOW);//关闭电机一防止MOS管短路
    digitalWrite(PA1, LOW);digitalWrite(PA2, LOW);digitalWrite(PA3, LOW);//关闭电机二防止MOS管短路
    pinMode(PA4,INPUT);pinMode(PA5,INPUT);//左边电机I-SENSE
    pinMode(PA6,INPUT);pinMode(PA7,INPUT);//右边电机I-SENSE
}


void ledcWrite (uint32_t ulPin, uint32_t ulValue)
{
    analogWrite(ulPin, ulValue);
}

void foc_init(void)
{
    Foc_Pin_Init();
    FOC_Vbus(8.4f);

    //设置电机极数和传感器方向
    FOC_M0_alignSensor(7,1);
    FOC_M1_alignSensor(7,-1);



    Serial.printf("Foc_init_OK\r\n");
}











