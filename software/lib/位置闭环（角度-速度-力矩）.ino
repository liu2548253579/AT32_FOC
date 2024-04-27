#include "DengFOC.h"

int Sensor_DIR=-1;    //传感器方向
int Motor_PP=7;    //电机极对数

void setup() {
  Serial.begin(115200);
  DFOC_Vbus(12.6);   //设定驱动器供电电压
  DFOC_alignSensor(Motor_PP,Sensor_DIR);
}

void loop() 
{
  //设置PID
  DFOC_M0_SET_ANGLE_PID(0.5,0,0,0);
  DFOC_M0_SET_VEL_PID(0.01,0.00,0,0);
  //给库设定速度
  DFOC_M0_set_Velocity_Angle(serial_motor_target()); 
  //接收串口
  serialReceiveUserCommand();

}
