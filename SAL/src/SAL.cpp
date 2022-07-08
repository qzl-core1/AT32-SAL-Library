#include "SAL.h"
volatile uint32_t tick;       
/*平台对应时钟的全局中断*/
extern "C" {
    void SysTick_Handler(void)
    {
        tick++;
    }
}
/*
    全局延迟函数
*/
void SAL_Delay(uint32_t ms)
{
    uint32_t now_tim = tick;
    while(tick-now_tim<ms);
}
/*平台对应的全局时钟初始化*/
void SAL_Init(void)
{
    system_clock_config();
    systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
    SysTick_Config(system_core_clock / 1000U);
}
