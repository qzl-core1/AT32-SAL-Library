#include "exint.h"


/*外部中断回调函数指针数组*/
static CallbackFunction_t EXTI_Function[16] = {0};

static IRQn_Type EXTI_GetIRQn(Pin_TypeDef Pin)
{
    IRQn_Type EXTIx_IRQn;
    uint8_t Pinx = __gpio_get_Bits(Pin);

    if (Pinx <= 4)
    {
        switch (Pinx)
        {
        case 0:
            EXTIx_IRQn = EXINT0_IRQn;
            break;
        case 1:
            EXTIx_IRQn = EXINT1_IRQn;
            break;
        case 2:
            EXTIx_IRQn = EXINT2_IRQn;
            break;
        case 3:
            EXTIx_IRQn = EXINT3_IRQn;
            break;
        case 4:
            EXTIx_IRQn = EXINT4_IRQn;
            break;
        }
    }
    else if (Pinx >= 5 && Pinx <= 9)
        EXTIx_IRQn = EXINT9_5_IRQn;
    else if (Pinx >= 10 && Pinx <= 15)
        EXTIx_IRQn = EXINT15_10_IRQn;

    return EXTIx_IRQn;
}

void __exit_Init(Pin_TypeDef Pin, CallbackFunction_t function, Exint_Mode Trigger_Mode, uint32_t preempt_priority, uint32_t sub_priority)
{

    /*外部中断结构体初始化*/
    exint_init_type exint_init_struct;
    /*外设复用时钟*/
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    /* 获取引脚的信息 */
    gpio_port_source_type GPIO_PORT_SOURCE_GPIOX;
    gpio_type *GPIOX = __gpio_port_get(Pin);
    uint8_t BTIS = __gpio_get_Bits(Pin);

    /* 触发方式匹配 */
    exint_polarity_config_type trigger_mode;
    switch (Trigger_Mode)
    {
    case Rising_Edge_Mode:
        trigger_mode = EXINT_TRIGGER_RISING_EDGE;
        __gpio_init(Pin, PIN_MUX, PULL_DOWN);
        break;


    case Falling_Edge_Mode:
        trigger_mode = EXINT_TRIGGER_FALLING_EDGE;
        __gpio_init(Pin, PIN_MUX, PULL_UP);
        break;


    case Both_Edge_Mode:
        trigger_mode = EXINT_TRIGGER_BOTH_EDGE;
        __gpio_init(Pin, PIN_MUX, PULL_UP);
        break;
    }

    /* 放在对应的中断回调函数里 */
    EXTI_Function[BTIS] = function;

    /* 选择中断源时钟 */
    if (GPIOX == GPIOA) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOA;
    if (GPIOX == GPIOB) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOB;
    if (GPIOX == GPIOC) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOC;
    if (GPIOX == GPIOD) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOD;

    uint32_t EXINT_LINE_X = __gpio_pin_get(Pin);

    /*外部中断源的配置*/
    gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOX, (gpio_pins_source_type)BTIS);
    /*外部中断结构体的使用默认值*/
    exint_default_para_init(&exint_init_struct);
    /*中断源是能*/
    exint_init_struct.line_enable = TRUE;
    /*中断源模式*/
    exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
    /*中断源选择*/
    exint_init_struct.line_select = EXINT_LINE_X;
    /*中断事件*/
    exint_init_struct.line_polarity = trigger_mode;
    /*中断初始化*/
    exint_init(&exint_init_struct);
    /*中断管理优先级*/
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_3);
    /*中断服务函数是能*/
    nvic_irq_enable(EXTI_GetIRQn(Pin), preempt_priority, sub_priority);
}


#define EXTIx_IRQHANDLER(n) \
do{\
    if(exint_flag_get(EXINT_LINE_##n) != RESET)\
    {\
        if(EXTI_Function[n]) EXTI_Function[n]();\
        exint_flag_clear(EXINT_LINE_##n);\
    }\
}while(0)

/*外部中断服务函数*/
/**
  * @brief  外部中断入口，通道0
  * @param  无
  * @retval 无
  */
void EXINT0_IRQHandler(void)
{
    EXTIx_IRQHANDLER(0);
}

/**
  * @brief  外部中断入口，通道1
  * @param  无
  * @retval 无
  */
void EXINT1_IRQHandler(void)
{
    EXTIx_IRQHANDLER(1);
}

/**
  * @brief  外部中断入口，通道2
  * @param  无
  * @retval 无
  */
void EXINT2_IRQHandler(void)
{
    EXTIx_IRQHANDLER(2);
}

/**
  * @brief  外部中断入口，通道3
  * @param  无
  * @retval 无
  */
void EXINT3_IRQHandler(void)
{
    EXTIx_IRQHANDLER(3);
}

/**
  * @brief  外部中断入口，通道4
  * @param  无
  * @retval 无
  */
void EXINT4_IRQHandler(void)
{
    EXTIx_IRQHANDLER(4);
}

/**
  * @brief  外部中断入口，通道5-9
  * @param  无
  * @retval 无
  */
void EXINT9_5_IRQHandler(void)
{
    EXTIx_IRQHANDLER(5);
    EXTIx_IRQHANDLER(6);
    EXTIx_IRQHANDLER(7);
    EXTIx_IRQHANDLER(8);
    EXTIx_IRQHANDLER(9);
}

void EXINT15_10_IRQHandler(void)
{
    EXTIx_IRQHANDLER(10);
    EXTIx_IRQHANDLER(11);
    EXTIx_IRQHANDLER(12);
    EXTIx_IRQHANDLER(13);
    EXTIx_IRQHANDLER(14);
    EXTIx_IRQHANDLER(15);
}
