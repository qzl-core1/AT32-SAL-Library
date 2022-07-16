#include "delay.h"
volatile uint32_t tick;

void delay_ms(uint32_t ms)
{
    uint32_t now_tim = tick;
    while (tick - now_tim < ms);
}

uint32_t mills(void)
{
    return tick;
}

void delay_init(void)
{
    /* 开启平台对应的系统嘀嗒定时器 */
    system_clock_config();
    systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
    SysTick_Config(system_core_clock / 1000U);
}

void SysTick_Handler(void)
{
    tick++;
}

