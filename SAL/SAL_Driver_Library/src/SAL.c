#include "SAL.h" 

/* 全局延迟函数 */
void SAL_Delay(uint32_t ms)
{
    delay_ms(ms);
}
/* 平台对应的全局时钟初始化 */
void SAL_Init(void)
{
    /*
        中断分组:
        0-3的抢占优先级
        0-3的响应优先级
    */
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_2);
    delay_init();
}

/* 获取上电以来的毫秒数 */
uint32_t SAL_Get_Millis(void)
{
    return mills();
}

/* GPIO初始化函数 */
void SAL_GPIO_Init(Pin_TypeDef Pinx,Pin_Mode_type mode,Pin_PULL_type pull)
{
    __gpio_init(Pinx,mode,pull);
}

/* GPIO输出函数 */
void SAL_GPIO_Write_Pin(Pin_TypeDef Pinx,uint16_t level)
{
    __gpio_write_Pin(Pinx,level);
}


/* GPIO读取电平的函数 */
uint8_t SAL_GPIO_Read_Pin(Pin_TypeDef Pinx)
{
    return __gpio_read_Pin(Pinx);
}

/* 软件I2C的读取函数 */
void SAL_I2C_GPIO_Init(Pin_TypeDef scl,Pin_TypeDef sda)
{
    __i2c_gpio_init(scl,sda);
}

/* 外部中断的初始化函数 */
void SAL_Exit_Init(Pin_TypeDef Pin , CallbackFunction_t function , Exint_Mode Trigger_Mode, uint32_t preempt_priority, uint32_t sub_priority)
{
    __exit_Init(Pin,function,Trigger_Mode,preempt_priority,sub_priority);
}

/* 定时器初始化函数 */
void SAL_Timer_Init(Timer_TypeDef Timx, CallbackFunction_t function ,uint32_t pr, uint32_t div, uint32_t preempt_priority, uint32_t sub_priority)
{
    _timer_IT_Init(Timx,function,pr,div,preempt_priority,sub_priority);
}

/* PWM初始化 */
void SAL_PWM_Init(Pin_TypeDef Pin_x , uint32_t counter_period , uint32_t div)
{
    __pwm_init(Pin_x , counter_period , div);
}

/* 修改PWM占空比 */
void SAL_PWM_Write(Pin_TypeDef Pin_x,uint16_t val)
{
    __pwm_write(Pin_x , val);
}