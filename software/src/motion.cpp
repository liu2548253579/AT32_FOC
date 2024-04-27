#include "motion.h"



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

