
#include "at32_config.h"
#include "foc_config.h"
#include "peripherals_config.h"
#include "menu.h"
#include "motion.h"
#include "interrupt.h"



void setup() {
  at32_board_init(); //CLOCK IO UART IIC initialization
  peripherals_init();//MPU6050 SSD1306 AT24C02

  // eeprom.update(0x80,0x02);
  // Serial.println("data------------------------------");
  // Serial.println(eeprom.read(0x80));
  // Serial.println("data------------------------------");

  // Menu_Show_3("HOLD-ON");
  // mpu6050.calcGyroOffsets(false);

  Menu_Show_1("ABCDEFGHIJKLMNOPQRSTU","ABCDEFGHIJKLMNOPQRSTU","ABCDEFGHIJKLMNOPQRSTU","ABCDEFGHIJKLMNOPQRSTU");

while (1)
{

ShowMenu(&main_menu);

Get_All_Sensor_Data(&sensor_data);

if(sensor_data.Key_val==3){main_menu.Enable=!main_menu.Enable;}
if(!main_menu.Enable)
{
    if(sensor_data.Key_val==1){main_menu.mode--;}
    if(sensor_data.Key_val==2){main_menu.mode++;}
}


  /* code */
}


  Menu_Show_3("LAN-FOC");
  foc_init();        //FOC initialization

  timer_init();//定时器初始化

  // bool ret = CANInit(CAN_500KBPS, 2);  // CAN_RX mapped to PB8, CAN_TX mapped to PB9
  // if (!ret) while(true);


  Motion_Velocity_Init();

  Menu_Show_3("INIT-OK");
  Serial.printf("INIT_OK\r\n");
}



void loop() {
    if(time_1ms>=10)//1ms执行一次
    {
      time_1ms=0;
      runFOC();

      // Motion_Set_Velocity(0,serial_motor_target());
      // Motion_Set_Velocity(1,serial_motor_target());
      Motion_Set_Velocity(0,20);
      Motion_Set_Velocity(1,20);

      // Get_All_Sensor_Data(&sensor_data);
      serialReceiveUserCommand();
    }

    if(time_10ms>=100)//10ms执行一次
    {
      time_10ms=0;
    }


    if(time_100ms>=1000)//100ms执行一次
    {
      time_100ms=0;
      digitalToggle(LED_PIN);
    }
}












