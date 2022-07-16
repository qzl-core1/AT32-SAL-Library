#include "timer.h"

/* 定时器中断回调数组 */
static CallbackFunction_t Timer_Function[14] = {0};

/* 使能对应的时钟 */
static void _timer_Clock_Enable(Timer_TypeDef Timx)
{
    if (Timx == TIMER1)
    {
        crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
    }

    else if (Timx == TIMER2)
    {
        crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
    }

    else if (Timx == TIMER3)
    {
        crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
    }

    else if (Timx == TIMER4)
    {
        crm_periph_clock_enable(CRM_TMR4_PERIPH_CLOCK, TRUE);
    }

    else if (Timx == TIMER5)
    {
        crm_periph_clock_enable(CRM_TMR5_PERIPH_CLOCK, TRUE);
    }

#ifdef TMR6
    else if (Timx == TIMER6)
    {
        crm_periph_clock_enable(CRM_TMR6_PERIPH_CLOCK, TRUE);
    }
#endif

#ifdef TMR7
    else if (Timx == TIMER7)
    {
        crm_periph_clock_enable(CRM_TMR7_PERIPH_CLOCK, TRUE);
    }
#endif

    else if (Timx == TIMER8)
    {
        crm_periph_clock_enable(CRM_TMR8_PERIPH_CLOCK, TRUE);
    }

#ifdef TMR8
    else if (Timx == TIMER9)
    {
        crm_periph_clock_enable(CRM_TMR9_PERIPH_CLOCK, TRUE);
    }
#endif

    else if (Timx == TIMER10)
    {
        crm_periph_clock_enable(CRM_TMR10_PERIPH_CLOCK, TRUE);
    }
    else if (Timx == TIMER11)
    {
        crm_periph_clock_enable(CRM_TMR11_PERIPH_CLOCK, TRUE);
    }

#ifdef TMR12
    else if (Timx == TIMER12)
    {
        crm_periph_clock_enable(CRM_TMR12_PERIPH_CLOCK, TRUE);
    }
#endif

#ifdef TMR13
    else if (Timx == TIMER13)
    {
        crm_periph_clock_enable(CRM_TMR13_PERIPH_CLOCK, TRUE);
    }
#endif

#ifdef TMR14
    else if (Timx == TIMER14)
    {
        crm_periph_clock_enable(CRM_TMR14_PERIPH_CLOCK, TRUE);
    }
#endif
}

/* 获取对应的定时器指针 */
static tmr_type *_timer_get_tmr(Timer_TypeDef Timx)
{
    if (Timx == TIMER1)
    {
        return TMR1;
    }

    else if (Timx == TIMER2)
    {
        return TMR2;
    }

    else if (Timx == TIMER3)
    {
        return TMR3;
    }

    else if (Timx == TIMER4)
    {
        return TMR4;
    }

    else if (Timx == TIMER5)
    {
        return TMR5;
    }

#ifdef TIM6
    else if (Timx == TIMER6)
    {
        return TMR6;
    }
#endif

#ifdef TIM7
    else if (Timx == TIMER7)
    {
        return TMR7;
    }
#endif

#ifdef TIM8
    else if (Timx == TIMER8)
    {
        return TMR8;
    }
#endif

    else if (Timx == TIMER9)
    {
        return TMR9;
    }
    else if (Timx == TIMER10)
    {
        return TMR10;
    }

    else if (Timx == TIMER11)
    {
        return TMR11;
    }

#ifdef TIM12
    else if (Timx == TIMER12)
    {
        return TMR12;
    }
#endif

#ifdef TIM13
    else if (Timx == TIMER13)
    {
        return TMR13;
    }
#endif

#ifdef TIM14
    else if (Timx == TIMER14)
    {
        return TMR14;
    }
#endif
    else return TMR1;
}

/* 获取对应的中断函数 */
static IRQn_Type _timer_get_IRQn(Timer_TypeDef Timx)
{
    if (Timx == TIMER1)
    {
        return TMR1_OVF_TMR10_IRQn;
    }

    else if (Timx == TIMER2)
    {
        return TMR2_GLOBAL_IRQn;
    }

    else if (Timx == TIMER3)
    {
        return TMR3_GLOBAL_IRQn;
    }

    else if (Timx == TIMER4)
    {
        return TMR4_GLOBAL_IRQn;
    }

    else if (Timx == TIMER5)
    {
        return TMR5_GLOBAL_IRQn;
    }

#ifdef TMR6
    else if (Timx == TIMER6)
    {
        return TMR6_GLOBAL_IRQn;
    }
#endif

#ifdef TMR7
    else if (Timx == TIMER7)
    {
        return TMR7_GLOBAL_IRQn;
    }
#endif

#ifdef TMR8
    else if (Timx == TIMER8)
    {
        return TMR8_OVF_TMR13_IRQn;
    }
#endif

    else if (Timx == TIMER9)
    {
        return TMR1_BRK_TMR9_IRQn;
    }
    else if (Timx == TIMER10)
    {
        return TMR1_OVF_TMR10_IRQn;
    }

    else if (Timx == TIMER11)
    {
        return TMR1_TRG_HALL_TMR11_IRQn;
    }

#ifdef TMR12
    else if (Timx == TIMER12)
    {
        return TMR8_BRK_TMR12_IRQn;
    }
#endif

#ifdef TMR13
    else if (Timx == TIMER13)
    {
        return TMR8_OVF_TMR13_IRQn;;
    }
#endif

#ifdef TMR14
    else if (Timx == TIMER14)
    {
        return TMR8_TRG_HALL_TMR14_IRQn;
    }
#endif

    else return TMR1_OVF_TMR10_IRQn;
}

/* 定时器中断设置 */
void _timer_IT_Init(Timer_TypeDef Timx, CallbackFunction_t function ,uint32_t pr, uint32_t div, uint32_t preempt_priority, uint32_t sub_priority)
{
    _timer_Clock_Enable(Timx);
    /* 获取对应的时钟指针 */
    tmr_type *tmrx = _timer_get_tmr(Timx);
    /* 获取对应的中断通道 */
    IRQn_Type irqn = _timer_get_IRQn(Timx);
    /* 将中断回调函数赋值 */
    Timer_Function[Timx-1] = function;
    
    /* 设置频率,freq = sysfrq/((div+1)*(pr+1)) */
    tmr_base_init(tmrx, pr, div);

    /*设置计数模式*/
    tmr_cnt_dir_set(tmrx, TMR_COUNT_UP);

    /*溢出中断是能*/
    tmr_interrupt_enable(tmrx, TMR_OVF_INT, TRUE);

    /* 中断优先级设置 */
    nvic_irq_enable(irqn, preempt_priority, sub_priority);
    
    /* 开启计数 */
    tmr_counter_enable(tmrx,TRUE);

}

#define TMRx_IRQHANDLER(n) \
do{\
    if (tmr_flag_get(TMR##n, TMR_OVF_FLAG) != RESET)\
    {\
        if(Timer_Function[n-1]) Timer_Function[n-1]();\
        tmr_flag_clear(TMR##n, TMR_OVF_FLAG);\
    }\
}while(0)


void TMR1_OVF_TMR10_IRQHandler(void)
{
    TMRx_IRQHANDLER(1);
    TMRx_IRQHANDLER(10);
}

void TMR2_GLOBAL_IRQHandler(void)
{
    TMRx_IRQHANDLER(2);
}

void TMR3_GLOBAL_IRQHandler(void)
{
    TMRx_IRQHANDLER(3);
}

void TMR4_GLOBAL_IRQHandler(void)
{
    TMRx_IRQHANDLER(4);
}

void TMR5_GLOBAL_IRQHandler(void)
{
    TMRx_IRQHANDLER(5);
}

void TMR6_GLOBAL_IRQHandler(void)
{
    TMRx_IRQHANDLER(6);
}

void TMR7_GLOBAL_IRQHandler(void)
{
    TMRx_IRQHANDLER(7);
}

void TMR8_OVF_TMR13_IRQHandler(void)
{
    TMRx_IRQHANDLER(8);
    TMRx_IRQHANDLER(13);
}

void TMR1_BRK_TMR9_IRQHandler(void)
{
    TMRx_IRQHANDLER(9);
}

void TMR1_TRG_HALL_TMR11_IRQHandler(void)
{
    TMRx_IRQHANDLER(11);
}

void TMR8_BRK_TMR12_IRQHandler(void)
{
    TMRx_IRQHANDLER(12);
}

void TMR8_TRG_HALL_TMR14_IRQHandler(void)
{
    TMRx_IRQHANDLER(14);
}

