#ifndef __FOC_CONFIG_H
#define __FOC_CONFIG_H

#include "at32_config.h"
#include "FOC.h"

#define FOC_PWM_FREQ 35000  //PWM频率
#define Resolution_PWM 10  //精度
#define PWM_MAX_VALUE 1023  //PWM最大值

#define M0_PWM_U PA_8
#define M0_PWM_V PA_9
#define M0_PWM_W PA_10

#define M1_PWM_U PA_1
#define M1_PWM_V PA_2
#define M1_PWM_W PA_3

#define M0_ADC_A PA_4
#define M0_ADC_B PA_5

#define M1_ADC_A PA_6
#define M1_ADC_B PA_7



//FOC算法参数设置
void foc_init(float power_supply);
void ledcWrite (uint32_t ulPin, uint32_t ulValue);


#endif /* __FOC_CONFIG_H */

