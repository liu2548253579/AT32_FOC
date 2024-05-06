#ifndef MOTION_H
#define MOTION_H

#include "FOC.h"
#include "peripherals_config.h"

typedef volatile struct
{
    float  kp, ti, td, dt;//kp ti td 执行时间dt(注意统一时间单位)
    float  desired, measured, integral, last_error, out;//期望值 实测值 积分值 上次误差 输出
    float  integral_limit, out_limit;//积分限幅
} PidObject;


PidObject pid_Angle_X;
PidObject pid_Gyro_X;
PidObject pid_Velocity_X;


float Rpm_to_Rad (float rpm);
float Rad_to_Rpm (float rad);
float Rad_to_Angle (float rad);
float Angle_to_Rad (float angle);
void Motion_Set_Angle_Both(float angle);
void Motion_Follow(uint8_t motor);
void Motion_Sync(void);
void Motion_Set_Velocity_Both(int16_t velocity);
void Motion_Set_Velocity(uint8_t motor,int16_t velocity);

//直立模式
void pidcalculate(PidObject* pid);
void pidcalculate_weizhi(PidObject* pid);
float Motion_Balance_Angle(SensorData *sensor_data,float desired_angle);
float Motion_Balance_Velocity(float measured_velocity,float desired_velocity);
void Banlance_Set_Velocity(uint8_t motor,int16_t velocity);




#endif // MOTION_H
