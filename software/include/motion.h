#ifndef MOTION_H
#define MOTION_H

#include "FOC.h"
#include "peripherals_config.h"

void Motion_Follow_Init(void);
void Motion_Follow(uint8_t motor);

void Motion_Velocity_Init(void);
void Motion_Set_Velocity(uint8_t motor,int16_t velocity);






#endif // MOTION_H
