#include "DengFOC.h"

int Sensor_DIR=-1;    //传感器方向
int Motor_PP=7;    //电机极对数

void setup() {
  Serial.begin(115200);
  DFOC_Vbus(12.6);   //设定驱动器供电电压
  DFOC_alignSensor(Motor_PP,Sensor_DIR);
}

int count=0;
void loop() 
{
  runFOC();

  //力位（加入电流环后）
  // DFOC_M0_SET_ANGLE_PID(0.5,0,0.003,100000,0.1);
  // DFOC_M0_SET_CURRENT_PID(1.25,50,0,100000);
  // DFOC_M0_set_Force_Angle(serial_motor_target());

  //速度（加入电流环后）
  // DFOC_M0_SET_VEL_PID(3,2,0,100000,0.5);
  // DFOC_M0_SET_CURRENT_PID(0.5,50,0,100000);
  // DFOC_M0_setVelocity(serial_motor_target());

  //位置-速度-力（加入电流环后）
  DFOC_M0_SET_ANGLE_PID(1,0,0,100000,30);
  DFOC_M0_SET_VEL_PID(0.02,1,0,100000,0.5);
  DFOC_M0_SET_CURRENT_PID(5,200,0,100000);
  DFOC_M0_set_Velocity_Angle(serial_motor_target());
  
  //电流力矩
  // DFOC_M0_SET_CURRENT_PID(5,200,0,100000);
  // DFOC_M0_setTorque(serial_motor_target());
  
  count++;
  if(count>30)
  {
      count=0;
      //Serial.printf("%f\n", DFOC_M0_Current());
      Serial.printf("%f,%f\n", DFOC_M0_Current(), DFOC_M0_Velocity());
  }
  //接收串口
  serialReceiveUserCommand();

}
