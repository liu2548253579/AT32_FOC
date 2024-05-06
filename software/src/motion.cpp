#include "motion.h"





float Rad_to_Angle (float rad)
{
    return rad*57.295779513f;
}

float Angle_to_Rad (float angle)
{
    return angle*0.01745329251f;
}


float Rad_to_Rpm (float rad)
{
    return rad*((float)(60.0f/(2*M_PI)));
}


float Rpm_to_Rad (float rpm)
{
    return rpm*((float)(2*M_PI)/60.0f);
}

void pidcalculate(PidObject* pid)
{
    float error=0,deriv=0;//误差，微分值

    error = pid->measured - pid->desired; //当前与实际的误差

    pid->integral += error;   //误差积分累加值

    //  此处进行积分限幅(可选)
    if(pid->integral>pid->integral_limit){pid->integral=pid->integral_limit;}
    if(pid->integral<-pid->integral_limit){pid->integral=-pid->integral_limit;}

    deriv = error - pid->last_error;  //前后两次误差做微分

    if(pid->ti==0){pid->out = pid->kp*(error + pid->td/pid->dt*deriv);}//PD输出
    else{pid->out = pid->kp*(error + pid->dt/pid->ti*pid->integral + pid->td/pid->dt*deriv);}//PID输出

    pid->last_error = error;  //更新上次的误差

    //  此处进行输出限幅(可选)
    // if(pid->out>pid->out_limit){pid->out=pid->out_limit;}
    // if(pid->out<-pid->out_limit){pid->out=-pid->out_limit;}
}


void pidcalculate_weizhi(PidObject* pid)
{
    static float Encoder;
    float Encoder_Least;

    Encoder_Least = pid->measured - pid->desired;                                  //速度滤波
    Encoder *= 0.7f;                                                            //一阶低通滤波器0.7
    Encoder += Encoder_Least*0.3f;                                              //一阶低通滤波器0.3
    pid->integral += Encoder - pid->desired;                             //积分出位移

    if(pid->integral>pid->integral_limit){pid->integral=pid->integral_limit;}
    if(pid->integral<-pid->integral_limit){pid->integral=-pid->integral_limit;}

    pid->out = Encoder * pid->kp + pid->integral * pid->ti;   //获取最终数值
}



float Motion_Balance_Angle(SensorData *sensor_data,float desired_angle)
{
pid_Angle_X.desired = (0.6f+desired_angle);
pid_Angle_X.measured = sensor_data->Angle_X;
pid_Angle_X.integral = 0;
pid_Angle_X.integral_limit = 100;
pid_Angle_X.ti = 0;
pid_Angle_X.dt = 0.01f;//10ms
pid_Angle_X.kp = 1.4f;//0.1-0.4   1.5最大
pidcalculate(&pid_Angle_X);

pid_Gyro_X.desired = 0.0f;
pid_Gyro_X.measured = sensor_data->Gyro_X;
pid_Gyro_X.integral = 0;
pid_Gyro_X.ti = 0;
pid_Gyro_X.dt = 0.01f;//10ms
pid_Gyro_X.kp = 0.02f;// 0.3 0.02     0.4 0.005     1.6 0.02    1.6 0.07  1.2 0.015
pidcalculate(&pid_Gyro_X);


float angle_out = pid_Angle_X.out + pid_Gyro_X.out;
const float angle_limit = 300.0f;
if(angle_out>angle_limit){angle_out=angle_limit;}
if(angle_out<-angle_limit){angle_out=-angle_limit;}

return angle_out;
}

float Motion_Balance_Velocity(float measured_velocity,float desired_velocity)
{
    pid_Velocity_X.desired = desired_velocity;
    pid_Velocity_X.measured = -measured_velocity;
    pid_Velocity_X.integral = 0;
    pid_Velocity_X.integral_limit = 200;
    pid_Velocity_X.kp = 1.4f; //0.5-1.5
    pid_Velocity_X.ti = 0;//pid_Velocity_X.kp/200.0f
    pidcalculate_weizhi(&pid_Velocity_X);
    return pid_Velocity_X.out;
}

void Banlance_Set_Velocity(uint8_t motor,int16_t velocity)
{
//设置速度环PID
FOC_M0_SET_VEL_PID(0.005f,0.00,0,0,200);
FOC_M0_SET_CURRENT_PID(0.5f,10,0,0);
FOC_M1_SET_VEL_PID(0.005f,0.00f,0,0,200);
FOC_M1_SET_CURRENT_PID(0.5f,10,0,0);
if (motor==0)
{
    FOC_M0_setVelocity(velocity);
}
else
{
    FOC_M1_setVelocity(velocity);
}
}





void Motion_Set_Velocity_Both(int16_t velocity)
{
//设置速度环PID
FOC_M0_SET_VEL_PID(0.005f,0.00,0,0,200);
FOC_M0_SET_CURRENT_PID(0.5f,50,0,0);//10
FOC_M1_SET_VEL_PID(0.005f,0.00f,0,0,200);
FOC_M1_SET_CURRENT_PID(0.5f,50,0,0);//10
FOC_M0_setVelocity(velocity);
FOC_M1_setVelocity(velocity);
}

void Motion_Set_Velocity(uint8_t motor,int16_t velocity)
{
//设置速度环PID
FOC_M0_SET_VEL_PID(0.005f,0.00,0,0,200);
FOC_M0_SET_CURRENT_PID(0.5f,50,0,0);
FOC_M1_SET_VEL_PID(0.005f,0.00f,0,0,200);
FOC_M1_SET_CURRENT_PID(0.5f,50,0,0);
if (motor==0)
{
    FOC_M0_setVelocity(velocity);
}
else
{
    FOC_M1_setVelocity(velocity);
}
}

void Motion_Set_Angle_Both(float angle)
{
    //设置角度环PID
    FOC_M0_SET_ANGLE_PID(0.4f,0,0.0001f,0,20);
    FOC_M0_SET_CURRENT_PID(0.3f,0.2f,0,0);
    FOC_M1_SET_ANGLE_PID(0.4f,0,0.0001f,0,20);
    FOC_M1_SET_CURRENT_PID(0.3f,0.2f,0,0);
    FOC_M0_set_Force_Angle(angle);
    FOC_M1_set_Force_Angle(angle);
}


void Motion_Set_Angle(uint8_t motor,float angle)
{
    //设置角度环PID
    if (motor==0)
    {   
        FOC_M0_SET_ANGLE_PID(0.4f,0,0.0001f,0,20);
        FOC_M0_SET_CURRENT_PID(0.3f,0.2f,0,0);
        FOC_M0_set_Force_Angle(angle);
    }
    else
    {
        FOC_M1_SET_ANGLE_PID(0.4f,0,0.0001f,0,20);
        FOC_M1_SET_CURRENT_PID(0.3f,0.2f,0,0);
        FOC_M1_set_Force_Angle(angle);
    }
}





void Motion_Follow(uint8_t motor)
{
    if (motor==0)
    {
        Motion_Set_Angle(0,sensor_data.Angle_val1);
    }
    else
    {
        Motion_Set_Angle(1,sensor_data.Angle_val);
    }
}


void Motion_Sync(void)
{
    Motion_Follow(0);
    Motion_Follow(1);
}


