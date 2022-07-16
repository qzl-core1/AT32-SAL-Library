#include "pwm.h"

void __pwm_clock_enable(tmr_type* Timx)
{
    if (Timx == TIM1)
    {
        crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
    }

    else if (Timx == TIM2)
    {
        crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
    }

    else if (Timx == TIM3)
    {
        crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
    }

    else if (Timx == TIM4)
    {
        crm_periph_clock_enable(CRM_TMR4_PERIPH_CLOCK, TRUE);
    }

    else if (Timx == TIM5)
    {
        crm_periph_clock_enable(CRM_TMR5_PERIPH_CLOCK, TRUE);
    }

#ifdef TMR6
    else if (Timx == TIM6)
    {
        crm_periph_clock_enable(CRM_TMR6_PERIPH_CLOCK, TRUE);
    }
#endif

#ifdef TMR7
    else if (Timx == TIM7)
    {
        crm_periph_clock_enable(CRM_TMR7_PERIPH_CLOCK, TRUE);
    }
#endif

    else if (Timx == TIM8)
    {
        crm_periph_clock_enable(CRM_TMR8_PERIPH_CLOCK, TRUE);
    }

#ifdef TMR8
    else if (Timx == TIM9)
    {
        crm_periph_clock_enable(CRM_TMR9_PERIPH_CLOCK, TRUE);
    }
#endif

    else if (Timx == TIM10)
    {
        crm_periph_clock_enable(CRM_TMR10_PERIPH_CLOCK, TRUE);
    }
    else if (Timx == TIM11)
    {
        crm_periph_clock_enable(CRM_TMR11_PERIPH_CLOCK, TRUE);
    }

#ifdef TMR12
    else if (Timx == TIM12)
    {
        crm_periph_clock_enable(CRM_TMR12_PERIPH_CLOCK, TRUE);
    }
#endif

#ifdef TMR13
    else if (Timx == TIM13)
    {
        crm_periph_clock_enable(CRM_TMR13_PERIPH_CLOCK, TRUE);
    }
#endif

#ifdef TMR14
    else if (Timx == TIM14)
    {
        crm_periph_clock_enable(CRM_TMR14_PERIPH_CLOCK, TRUE);
    }
#endif
}

tmr_channel_select_type __pwm_get_channel(uint16_t channel)
{
    switch(channel)
    {
        case 1:
            return TMR_SELECT_CHANNEL_1;
        case 2:
            return TMR_SELECT_CHANNEL_2;
        case 3:
            return TMR_SELECT_CHANNEL_3;
        case 4:
            return TMR_SELECT_CHANNEL_4;
        default:
            return 0;
    }
}

void __pwm_init(Pin_TypeDef Pin_x , uint32_t counter_period , uint32_t div)
{
    __gpio_init(Pin_x,PIN_MUX,PULL_NONE);
    tmr_type* Timx = __gpio_get_timer(Pin_x);
    tmr_channel_select_type channelx = __pwm_get_channel(__gpio_get_pwm_channel(Pin_x));
//    if(channelx == 0) return;
    
    __pwm_clock_enable(Timx);
    /* TIMx clock enable */
    tmr_output_config_type tmr_oc_init_structure;
    tmr_base_init(Timx, counter_period, div);
    tmr_cnt_dir_set(Timx, TMR_COUNT_UP);
    tmr_clock_source_div_set(Timx, TMR_CLOCK_DIV1);
    tmr_output_default_para_init(&tmr_oc_init_structure);
    tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
    tmr_oc_init_structure.oc_idle_state = FALSE;
    tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_oc_init_structure.oc_output_state = TRUE;
    tmr_output_channel_config(Timx, channelx, &tmr_oc_init_structure);
    tmr_channel_value_set(Timx, channelx, counter_period/2);
    tmr_output_channel_buffer_enable(Timx, channelx, TRUE);
    tmr_period_buffer_enable(Timx, TRUE);
   /* tmr enable counter */
    tmr_counter_enable(Timx, TRUE);
}

void __pwm_write(Pin_TypeDef Pin_x,uint16_t val)
{
    tmr_type* Timx = __gpio_get_timer(Pin_x);
    uint16_t channel = __gpio_get_pwm_channel(Pin_x);
    if(channel == 0) return;
    switch(channel)
    {
        case 1:
                Timx->c1dt = val;
        break;
        case 2:
            Timx->c2dt = val;
        break;
        case 3:
            Timx->c3dt = val;
        break;
        case 4:
            Timx->c4dt = val;
        break;
    }
}

