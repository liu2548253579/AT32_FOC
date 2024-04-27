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
  DFOC_M0_SET_CURRENT_PID(5,200,0,100000);
  DFOC_M0_setTorque(serial_motor_target());
  count++;
  if(count>30)
  {
      count=0;
      Serial.printf("%f\n", DFOC_M0_Current());
  }
  //接收串口
  serialReceiveUserCommand();

}
