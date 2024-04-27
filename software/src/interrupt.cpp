#include "interrupt.h"


HardwareTimer timer(TIM3);

int time_1ms,time_10ms,time_100ms;

void OnTimer3Interrupt() {
    time_100ms++;
    time_10ms++;
    time_1ms++;
}

void timer_init(void) 
{
    timer.setPrescaleFactor(720 - 1);  // 设置分频因子为7200，时钟频率为10kHz
    timer.setOverflow(10 - 1);          // 设置溢出值为10，产生1毫秒的定时中断
    timer.attachInterrupt(OnTimer3Interrupt);
    timer.setInterruptPriority(1,0);      // 设置中断优先级为1
    timer.refresh();  // 让寄存器更改生效
    timer.resume();   // 启动定时器
}








