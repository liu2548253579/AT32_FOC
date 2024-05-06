#include "interrupt.h"
#include "peripherals_config.h"
#include "motion.h"
#include "menu.h"

HardwareTimer timer_task(TIM3);


int time_1ms,time_10ms,time_200ms;


void OnTimer3Interrupt() {
	// timer_task.pause();
        time_200ms++;
        time_10ms++;
        time_1ms++;
	// timer_task.resume();
}

void timer_init(void) 
{
    timer_task.setPrescaleFactor(timer_task.getTimerClkFreq()/10000 - 1);  // 设置分频因子为64M，时钟频率为10kHz
    timer_task.setOverflow(10 - 1);          // 设置溢出值为10，产生1毫秒的定时中断
    timer_task.attachInterrupt(OnTimer3Interrupt);
    timer_task.setInterruptPriority(0,0);      // 设置中断优先级为最低
    timer_task.resume();   // 启动定时器
}







