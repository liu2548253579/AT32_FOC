#ifndef __FOC_CONFIG_H
#define __FOC_CONFIG_H

#include "at32_config.h"
#include "FOC.h"

#define FOC_PWM_FREQ 35000  //PWM频率
#define Resolution_PWM 10  //精度
#define PWM_MAX_VALUE 1023  //PWM最大值

#define M0_PWM_U PA8
#define M0_PWM_V PA9
#define M0_PWM_W PA10

#define M1_PWM_U PA1
#define M1_PWM_V PA2
#define M1_PWM_W PA3

#define M0_ADC_A PA4
#define M0_ADC_B PA5

#define M1_ADC_A PA6
#define M1_ADC_B PA7



//FOC算法参数设置
void foc_init(void);
void ledcWrite (uint32_t ulPin, uint32_t ulValue);


#endif /* __FOC_CONFIG_H */

