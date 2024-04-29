
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

  Menu_Show_3("HOLD-ON");
  mpu6050.calcGyroOffsets(false);



  Menu_Show_3("LAN-FOC");
  foc_init();        //FOC initialization



  // bool ret = CANInit(CAN_500KBPS, 2);  // CAN_RX mapped to PB8, CAN_TX mapped to PB9
  // if (!ret) while(true);



  Menu_Show_3("INIT-OK");
  Serial.printf("INIT_OK\r\n");


  timer_init();//定时器初始化
}



void loop() {


    if(main_menu.Enable)
    {
      runFOC();
      if(main_menu.mode==0){Close_Output();}//Banlance
      if(main_menu.mode==1){Motion_Set_Velocity_Both(Rpm_to_Rad(serial_motor_target()));}
      if(main_menu.mode==2){Motion_Sync();}//Sync
      if(main_menu.mode==3){Motion_Set_Angle_Both(Angle_to_Rad(serial_motor_target()));}//Angle
      if(main_menu.mode==4){Close_Output();}//Config
      if(main_menu.mode==5){Close_Output();}//Info
    }
    else
    {
      Close_Output();
    }


    if(time_1ms>=10)//1ms执行一次
    {
      time_1ms=0; 
      serialReceiveUserCommand();
    }

    if(time_10ms>=100)//10ms执行一次
    {
      time_10ms=0;
      Get_Foc_Data(&sensor_data);
      // Get_Mpu6050_Data(&sensor_data);
      // Serial_Print_All_Data(&sensor_data);
    }


    if(time_100ms>=1000)//100ms执行一次
    {
      time_100ms=0;
      Get_Analog_Data(&sensor_data);
      if(sensor_data.Key_val==3){sensor_data.Key_val=0;main_menu.Enable=!main_menu.Enable;}
      if(!main_menu.Enable)
      {
          if(sensor_data.Key_val==1){sensor_data.Key_val=0;main_menu.mode--;}
          if(sensor_data.Key_val==2){sensor_data.Key_val=0;main_menu.mode++;}
      }
      ShowMenu(&main_menu);
      digitalToggle(LED_PIN);
    }
}












