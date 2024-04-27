
#include "at32_config.h"
#include "foc_config.h"
#include "peripherals_config.h"
#include "at32_can.h"

HardwareTimer timer(TIM3);

// define two tasks for Blink & AnalogRead
SensorData sensor_data;
void Get_All_Sensor_Data(SensorData *sensor_dat);
void Serial_Show_All_Data(SensorData *sensor_dat);

void Motion_Follow_Init(void);
void Motion_Follow(uint8_t motor);

void Motion_Velocity_Init(void);
void Motion_Set_Velocity(uint8_t motor,int16_t velocity);



int time_1ms, time_10ms, time_100ms, time_1s;

void OnTimer3Interrupt() {
  time_1s++;
  time_100ms++;
  time_10ms++;
  time_1ms++;
}


void timer_init(void) 
{
  timer.setPrescaleFactor(720 - 1);  // 设置分频因子为7200，时钟频率为10kHz
  timer.setOverflow(10 - 1);          // 设置溢出值为10，产生1毫秒的定时中断
  timer.attachInterrupt(OnTimer3Interrupt);
  timer.setInterruptPriority(1,0);      // 设置中断优先级为1
  timer.refresh();  // 让寄存器更改生效
  timer.resume();   // 启动定时器
}

void setup() {
  at32_board_init(); //CLOCK IO UART IIC initialization
  peripherals_init();//MPU6050 SSD1306 AT24C02

  SHOW_FULLSCREEN("HOLD-ON");
  Serial.printf("MPU6050_OFFSET_CALIBRATION...\r\n");
  mpu6050.calcGyroOffsets(false);
  Serial.printf("MPU6050_OFFSET_CALIBRATION DONE\r\n");

  SHOW_FULLSCREEN("LAN-FOC");

  foc_init();        //FOC initialization



  timer_init();

  // bool ret = CANInit(CAN_500KBPS, 2);  // CAN_RX mapped to PB8, CAN_TX mapped to PB9
  // if (!ret) while(true);
  Motion_Velocity_Init();

  SHOW_FULLSCREEN("INIT-OK");
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
      // Serial_Show_All_Data(&sensor_data);
      // serialReceiveUserCommand();
    }

}


void Motion_Velocity_Init(void)
{
  //设置速度环PID
  FOC_M0_SET_VEL_PID(0.005,0.00,0,0,200);
  FOC_M0_SET_CURRENT_PID(0.5,50,0,0);
  FOC_M1_SET_VEL_PID(0.005,0.00,0,0,200);
  FOC_M1_SET_CURRENT_PID(0.5,50,0,0);
}


void Motion_Set_Velocity(uint8_t motor,int16_t velocity)
{
  if (motor==0)
  {
    FOC_M0_setVelocity(velocity);
  }
  else
  {
    FOC_M1_setVelocity(velocity);
  }
}


void Motion_Follow_Init(void)
{
  FOC_M0_SET_ANGLE_PID(0.2,0,0.0001,0,20);
  FOC_M0_SET_CURRENT_PID(0.15,0.2,0,0);
  FOC_M1_SET_ANGLE_PID(0.2,0,0.0001,0,20);
  FOC_M1_SET_CURRENT_PID(0.15,0.2,0,0);
}


void Motion_Follow(uint8_t motor)
{
  if (motor==0)
  {
    FOC_M0_set_Force_Angle(sensor_data.Angle_val1);
  }
  else
  {
    FOC_M1_set_Force_Angle(sensor_data.Angle_val);
  }
}




void Get_All_Sensor_Data(SensorData *sensor_dat)
{
  mpu6050.update();
  sensor_dat->Bat_val=at32_battery_voltage_read();
  sensor_dat->Key_val=KEY_Read();
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


void Serial_Show_All_Data(SensorData *sensor_dat)
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
  Serial.print(sensor_dat->Key_val);
  Serial.print(",");
  Serial.print(sensor_dat->Angle_X);
  Serial.print(",");
  Serial.print(sensor_dat->Angle_Y);
  Serial.print(",");
  Serial.print(sensor_dat->Angle_Z);
  Serial.print("\r\n");
}

void display_Show_All_Data(SensorData *sensor_dat)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(sensor_dat->Bat_val);
  display.setCursor(0, 16);
  display.print(sensor_dat->Key_val);
  display.display();
}











