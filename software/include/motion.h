#ifndef MOTION_H
#define MOTION_H

#include "FOC.h"
#include "peripherals_config.h"

float Rpm_to_Rad (float rpm);
float Angle_to_Rad (float angle);
void Motion_Set_Angle_Both(float angle);
void Motion_Follow(uint8_t motor);
void Motion_Sync(void);
void Motion_Set_Velocity_Both(int16_t velocity);
void Motion_Set_Velocity(uint8_t motor,int16_t velocity);







#endif // MOTION_H
