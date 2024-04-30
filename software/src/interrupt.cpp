#include "interrupt.h"
#include "peripherals_config.h"
#include "motion.h"
#include "menu.h"

HardwareTimer timer_task(TIM3);


int time_1ms,time_10ms,time_100ms;


void OnTimer3Interrupt() {
        time_100ms++;
        time_10ms++;
        time_1ms++;

}

void timer_init(void) 
{
	// __TIM3_CLK_ENABLE();
    // TIM_HandleTypeDef TIM_Handle;
	// TIM_Handle.Instance = TIM3;
	// TIM_Handle.Init.Prescaler = (uint32_t)(720 -1);
	// TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	// TIM_Handle.Init.Period = 10-1;
	// TIM_Handle.Init.ClockDivision = 0;
	// TIM_Handle.Init.RepetitionCounter = 0;

    // // HardwareTimer_Handle[TIMER3_INDEX]->handle = &OnTimer3Interrupt;
	// HAL_NVIC_SetPriority(TIM3_IRQn, 3, 0);
	// HAL_NVIC_EnableIRQ(TIM3_IRQn);
	// __HAL_TIM_CLEAR_IT(&(HardwareTimer_Handle[TIMER3_INDEX]->handle), TIM_IT_UPDATE);
	// HAL_TIM_Base_Init(&TIM_Handle);
	// HAL_TIM_Base_Start_IT(&TIM_Handle);



    // timer_task.setup(TIM3);
    timer_task.setPrescaleFactor(timer_task.getTimerClkFreq()/100000 - 1);  // 设置分频因子为64M，时钟频率为10kHz
    timer_task.setOverflow(10 - 1);          // 设置溢出值为10，产生1毫秒的定时中断
    timer_task.attachInterrupt(OnTimer3Interrupt);
    timer_task.setInterruptPriority(0,0);      // 设置中断优先级为最低
    timer_task.resume();   // 启动定时器
}







