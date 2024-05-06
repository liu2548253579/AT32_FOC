#include "at32_config.h"
#include "math.h"

/*
线阻15欧姆
波特率115200

LED(PB1)
按键ADC(PA0)
电池ADC(PB0)

MOTOR1(PA8 PA9 PA10)
AS5600_1(PF6-SCL PF7-SDA)Wire1
I-SENSE1(PA6 PA7)

MOTOR2(PA1 PA2 PA3)
AS5600_2(PB10-SCL PB11-SDA)Wire
I-SENSE2(PA4 PA5)

MPU6050(PF6-SCL PF7-SDA)Wire1
FLASH(PF6-SCL PF7-SDA)Wire1
OLED(PB10-SCL PB11-SDA)Wire

SWD(PA13-CLK PA14-DIO)
USART1(PB6-TX PB7-RX)
CAN(PB8-RX PB9-TX)
*/

TwoWire Wire1 = TwoWire(); //D14-D15



void at32_i2c_clock_config(void)
{
__HAL_RCC_I2C1_CLK_ENABLE();
__HAL_RCC_AFIO_CLK_ENABLE();
__HAL_RCC_I2C1_REMAP_CLK_ENABLE();
__HAL_RCC_GPIOF_CLK_ENABLE();
}



void gpio_pin_remap_config(uint32_t gpio_remap, confirm_state new_state)
{
    uint32_t reg_addr, remap_mask;
    uint8_t bit_offset, bit_num, bit_val;

    /* get register address, bit offset, bit number and remap value */
    reg_addr = IOMUX_BASE + (gpio_remap >> 24);
    bit_offset = (gpio_remap >> 16) & 0xFF;
    bit_num = (gpio_remap >> 8) & 0xFF;
    bit_val = gpio_remap & 0xFF;

    /* get remap mask value */
    remap_mask = 0xFFFFFFFF << (32 - bit_num - bit_offset);
    remap_mask = remap_mask >> (32 - bit_num - bit_offset);
    remap_mask = remap_mask >> bit_offset;
    remap_mask = remap_mask << bit_offset;

    /* clear remap value */
    *(uint32_t*)reg_addr &= ~remap_mask;

    if(new_state != FALSE)
    {
        /* set remap value */
        *(uint32_t*)reg_addr |= (uint32_t)(bit_val << bit_offset);
    }
}


void Foc_Pin_Init(void)
{
    pinMode(PA8,OUTPUT);pinMode(PA9,OUTPUT);pinMode(PA10,OUTPUT);//初始化电机一引脚
    pinMode(PA1,OUTPUT);pinMode(PA2,OUTPUT);pinMode(PA3,OUTPUT);//初始化电机二引脚
    digitalWrite(PA8, LOW);digitalWrite(PA9, LOW);digitalWrite(PA10, LOW);//关闭电机一防止MOS管短路
    digitalWrite(PA1, LOW);digitalWrite(PA2, LOW);digitalWrite(PA3, LOW);//关闭电机二防止MOS管短路
    pinMode(PA4,INPUT);pinMode(PA5,INPUT);//左边电机I-SENSE
    pinMode(PA6,INPUT);pinMode(PA7,INPUT);//右边电机I-SENSE
}




void at32_board_init(void)
{   
    at32_i2c_clock_config();
    gpio_pin_remap_config(I2C1_GMUX_0011,TRUE);
    
    Foc_Pin_Init();

    Wire.setClock(400000); //设置I2C时钟频率为400kHz
    Wire1.setClock(400000); //设置I2C时钟频率为400kHz
    Wire1.setSCL(PF6);Wire1.setSDA(PF7);Wire1.begin();//初始化I2C接口1
    Wire.setSCL(PB10);Wire.setSDA(PB11);Wire.begin();//初始化I2C接口2
    Serial.setRx(PB7);Serial.setTx(PB6);Serial.begin(115200);//初始化串口

    pinMode(BAT_PIN,INPUT);//电池电压测量
    pinMode(KEY_PIN,INPUT_PULLDOWN);//按键ADC
    analogReadResolution(12);//设置ADC读取精度为12位

    pinMode(LED_PIN,OUTPUT);//初始化LED引脚
    digitalWrite(LED_PIN,LOW);//LED亮
    


    Serial.println("AT32_Board Init OK!");
    Serial.printf("Serial_OK!BaudRate:115200\r\nKEY(PA0)LED(PB1)\r\nBATTERY(PB0)\r\nMOTOR1(PA8 PA9 PA10)\r\nMOTOR2(PA1 PA2 PA3)\r\nI-SENSE1(PA6 PA7)\r\nI-SENSE2(PA4 PA5)\r\nIIC1(PF6-SCL PF7-SDA)-MPU-FLASH\r\nIIC2(PB10-SCL PB11-SDA)-OLED\r\nSWD(PA13-CLK PA14-DIO)\r\nUSART1(PB6-TX PB7-RX)\r\nCAN(PB8-RX PB9-TX)\r\n");
}



float at32_battery_voltage_read(void)
{
    float bat_voltage;
    uint32_t adc_val;
    adc_val=analogRead(BAT_PIN);
    bat_voltage=((float)adc_val/4095)*3.3*10.1;
    return bat_voltage;
}
// *40.16815554




uint8_t KEY_Read(void)
{   
    const uint8_t err_val=10;
    uint8_t key_val=0;
    uint32_t adc_val;
    float key_voltage;
    adc_val=analogRead(KEY_PIN);
    key_voltage=((float)adc_val/4095)*3.3*100;

    if(fabs(key_voltage-247.5)<=err_val){
        key_val=1;
    }
    else if(fabs(key_voltage-165)<=err_val){
        key_val=2;
    }
    else if(fabs(key_voltage-82.5)<=err_val){
        key_val=3;
    }

    return key_val;
}


uint8_t KEY_Read_Debounce(void)
{
uint8_t temp;
static uint8_t key_val_pre=0;
uint8_t key_val=KEY_Read();

if(key_val)//按键按下
{
    temp=0;
}
{//按键松开
    if(key_val!=key_val_pre)//按键状态改变
    {
        temp=key_val_pre;
    }
}

key_val_pre=key_val;
return temp;
}















