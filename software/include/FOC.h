#include "at32_config.h"
#include "foc_config.h"

void M0_setPwm(float Ua, float Ub, float Uc);
void M1_setPwm(float Ua, float Ub, float Uc);
void M0_setTorque(float Uq,float angle_el);
void M1_setTorque(float Uq,float angle_el);
float _normalizeAngle(float angle);
void FOC_Vbus(float power_supply);
void FOC_M0_alignSensor(int _PP,int _DIR);
void FOC_M1_alignSensor(int _PP,int _DIR);
float S0_electricalAngle();
float S1_electricalAngle();
float cal_Iq_Id(float current_a,float current_b,float angle_el);
float serial_motor_target();
String serialReceiveUserCommand();
//传感器读取
float FOC_M0_Velocity();
float FOC_M1_Velocity();
float FOC_M0_Angle();
float FOC_M1_Angle();
float FOC_M0_Current();
float FOC_M1_Current();
//PID
void FOC_M0_SET_ANGLE_PID(float P,float I,float D,float ramp,float limit);
void FOC_M0_SET_VEL_PID(float P,float I,float D,float ramp,float limit);
void FOC_M0_SET_CURRENT_PID(float P,float I,float D,float ramp);
void FOC_M1_SET_ANGLE_PID(float P,float I,float D,float ramp,float limit);
void FOC_M1_SET_VEL_PID(float P,float I,float D,float ramp,float limit);
void FOC_M1_SET_CURRENT_PID(float P,float I,float D,float ramp);
float FOC_M0_VEL_PID(float error);
float FOC_M0_ANGLE_PID(float error);
float FOC_M1_VEL_PID(float error);
float FOC_M1_ANGLE_PID(float error);

//接口函数
void FOC_M0_set_Velocity_Angle(float Target);
void FOC_M0_setVelocity(float Target);
void FOC_M0_set_Force_Angle(float Target);
void FOC_M1_set_Velocity_Angle(float Target);
void FOC_M1_setVelocity(float Target);
void FOC_M1_set_Force_Angle(float Target);
void FOC_M0_setTorque(float Target);
void FOC_M1_setTorque(float Target);   
//runFOC 循环函数
void runFOC();
//测试函数
