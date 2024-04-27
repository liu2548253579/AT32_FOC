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
  //输出角度值
  //Serial.print("当前角度：");
  //Serial.println(DFOC_M0_Angle());
  //输出角度值
  float Kp=0.133;
  float Sensor_Angle=DFOC_M0_Angle();
  setTorque(serial_motor_target(),_electricalAngle());   //电压力矩
  serialReceiveUserCommand();
}
