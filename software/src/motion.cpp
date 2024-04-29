#include "motion.h"


float Angle_to_Rad (float angle)
{
    return angle*0.01745329251f;
}

float Rpm_to_Rad (float rpm)
{
    return rpm*((float)(2*M_PI)/60.0f);
}

void Motion_Set_Velocity_Both(int16_t velocity)
{
//设置速度环PID
FOC_M0_SET_VEL_PID(0.005,0.00,0,0,200);
FOC_M0_SET_CURRENT_PID(0.5,50,0,0);
FOC_M1_SET_VEL_PID(0.005,0.00,0,0,200);
FOC_M1_SET_CURRENT_PID(0.5,50,0,0);
FOC_M0_setVelocity(velocity);
FOC_M1_setVelocity(velocity);
}




void Motion_Set_Velocity(uint8_t motor,int16_t velocity)
{
//设置速度环PID
FOC_M0_SET_VEL_PID(0.005,0.00,0,0,200);
FOC_M0_SET_CURRENT_PID(0.5,50,0,0);
FOC_M1_SET_VEL_PID(0.005,0.00,0,0,200);
FOC_M1_SET_CURRENT_PID(0.5,50,0,0);
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
    FOC_M0_SET_ANGLE_PID(0.4,0,0.0001,0,20);
    FOC_M0_SET_CURRENT_PID(0.3,0.2,0,0);
    FOC_M1_SET_ANGLE_PID(0.4,0,0.0001,0,20);
    FOC_M1_SET_CURRENT_PID(0.3,0.2,0,0);
    FOC_M0_set_Force_Angle(angle);
    FOC_M1_set_Force_Angle(angle);
}


void Motion_Set_Angle(uint8_t motor,float angle)
{
    //设置角度环PID
    if (motor==0)
    {   
        FOC_M0_SET_ANGLE_PID(0.4,0,0.0001,0,20);
        FOC_M0_SET_CURRENT_PID(0.3,0.2,0,0);
        FOC_M0_set_Force_Angle(angle);
    }
    else
    {
        FOC_M1_SET_ANGLE_PID(0.4,0,0.0001,0,20);
        FOC_M1_SET_CURRENT_PID(0.3,0.2,0,0);
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


