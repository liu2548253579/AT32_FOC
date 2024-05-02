#include "at32_config.h"
#include "foc_config.h"
#include "peripherals_config.h"
#include "menu.h"
#include "motion.h"
#include "interrupt.h"


void setup() {
  at32_board_init(); //CLOCK IO UART IIC initialization
  peripherals_init();//MPU6050 SSD1306 AT24C02

  Menu_Show_3("LOW-VOL");
  Get_Initial_Voltage(&sensor_data,6.7f);//6.7V initial voltage
  // eeprom.update(0x80,0x02);
  // Serial.println("data------------------------------");
  // Serial.println(eeprom.read(0x80));
  // Serial.println("data------------------------------");

  Menu_Show_3("HOLD-ON");
  mpu6050.calcGyroOffsets(false);


  // I2C1_EV_IRQn
  Menu_Show_3("LAN-FOC");
  foc_init(sensor_data.Bat_val_init);        //FOC initialization

  // bool ret = CANInit(CAN_500KBPS, 2);  // CAN_RX mapped to PB8, CAN_TX mapped to PB9
  // if (!ret) while(true);

  Menu_Show_3("INIT-OK");
  Serial.printf("INIT_OK\r\n");

  timer_init();//定时器初始化
}



void loop() {

    if(time_1ms>=1)
    {
      time_1ms=0;
      runFOC();
      if(main_menu.Enable)
      {
        if(main_menu.mode==1){Motion_Set_Velocity_Both(Rpm_to_Rad(main_menu.Velocity));}//Velocity
        if(main_menu.mode==2){Motion_Sync();}//Sync
        if(main_menu.mode==3){Motion_Set_Angle_Both(Angle_to_Rad(main_menu.Angle));}//Angle
        if(main_menu.mode==4){Close_Output();}//Config
        if(main_menu.mode==5){Close_Output();}//Info
      }
      else
      {
        Clear_FOC_Data();
        Close_Output();
      }
    }


    if(time_10ms>=10)//10ms执行一次
    {
		time_10ms=0;
      Get_Mpu6050_Data(&sensor_data);
      Get_Foc_Data(&sensor_data);
      if(main_menu.Enable)
      {
        if(main_menu.mode==0)//Banlance
        {
          float out_angle,out_velocity;
          out_angle=Motion_Balance_Angle(&sensor_data);
          out_velocity=Motion_Balance_Velocity(&sensor_data,0.0f);
          const int out_limit = 400;
          float out1 = out_angle+out_velocity;

          if(out1>out_limit){out1=out_limit;}
          if(out1<-out_limit){out1=-out_limit;}

          Motion_Set_Velocity_Both(out1);
        }
        else{
          Serial_Print_All_Data(&sensor_data);
        }
      }

    }

    if(time_100ms>=200)//100ms执行一次
    {
      time_100ms=0;
      Get_Analog_Data(&sensor_data);
      if(sensor_data.Bat_val<6.7f)//低电量关闭输出
      {
        main_menu.Enable=0;
        Menu_Show_3("LOW-VOL");//显示低电量
        Close_Output();
      }

      if(sensor_data.Key_val==3){sensor_data.Key_val=0;main_menu.Enable=!main_menu.Enable;}
      if(!main_menu.Enable)
      {
          if(sensor_data.Key_val==1){sensor_data.Key_val=0;main_menu.mode--;}
          if(sensor_data.Key_val==2){sensor_data.Key_val=0;main_menu.mode++;}
      }
      else
      {
        if(main_menu.mode==1){//Velocity
          if(sensor_data.Key_val==1){sensor_data.Key_val=0;main_menu.Velocity+=50;}
          if(sensor_data.Key_val==2){sensor_data.Key_val=0;main_menu.Velocity-=50;}
          if(main_menu.Velocity<=-500){main_menu.Velocity=-500;}
          if(main_menu.Velocity>=500){main_menu.Velocity=500;}
        }
        if(main_menu.mode==3){//Angle
          if(sensor_data.Key_val==1){sensor_data.Key_val=0;main_menu.Angle+=30;}
          if(sensor_data.Key_val==2){sensor_data.Key_val=0;main_menu.Angle-=30;}
        }
      }

      ShowMenu(&main_menu);
      serialReceiveUserCommand();
      digitalToggleFast(LED_PIN);
    }



}












