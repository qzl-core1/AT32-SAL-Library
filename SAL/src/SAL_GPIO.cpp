#include "SAL_GPIO.h"


void SAL_GPIO_Init(Pin_TypeDef Pinx,Pin_Mode_type mode,Pin_PULL_type pull)
{
    gpio_type* GPIOX = GPIO_MAP[Pinx].GPIOX;
    uint16_t PINX = GPIO_MAP[Pinx].PinX;
    /*开启对应的时钟*/
    if(GPIOX == GPIOA) crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    if(GPIOX == GPIOB) crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    if(GPIOX == GPIOC) crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    if(GPIOX == GPIOD) crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    /*开始初始化*/
    gpio_init_type gpio_init_struct;
    /*默认初始化*/
    gpio_default_para_init(&gpio_init_struct);
    /* 输出强度 */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    /*模式确认*/
    if(mode == INPUT) gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    if(mode == OUTPUT) gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    if(mode == PIN_MUX) gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    if(mode == ANALOG) gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
    /*引脚确认*/
    gpio_init_struct.gpio_pins =  PINX;
    /*选择上下拉*/
    if(pull == PULL_UP) gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    if(pull == PULL_DOWN) gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
    if(pull == PULL_NONE) gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOX, &gpio_init_struct);
}
/*控制GPIO输出*/
void SAL_GPIO_Write_Pin(Pin_TypeDef Pinx,uint16_t level)
{
    gpio_type* GPIOX = GPIO_MAP[Pinx].GPIOX;
    uint16_t PINX = GPIO_MAP[Pinx].PinX;
    if(level) gpio_bits_set(GPIOX,PINX);
    else gpio_bits_reset(GPIOX,PINX);
}
/*读取某个GPIO的电平*/
uint8_t SAL_GPIO_Read_Pin(Pin_TypeDef Pinx)
{
  uint8_t status = RESET;
  gpio_type* GPIOX = GPIO_MAP[Pinx].GPIOX;
  uint16_t PINX = GPIO_MAP[Pinx].PinX;
  
  if((GPIOX->idt & PINX) != RESET)
  {
    status = 1;
  }
  else
  {
    status = 0;
  }

  return status;
}

/*外部中断回调函数指针数组*/
static CallbackFunction_t EXTI_Function[16] = {0};

/* 返回引脚对应的位数 */
uint8_t SAL_GPIO_Get_Bits(Pin_TypeDef Pinx)
{
    uint16_t PinSource = 0;
    uint16_t GPIO_Pin_x = GPIO_MAP[Pinx].PinX;
    while(GPIO_Pin_x > 1)
    {
        GPIO_Pin_x >>= 1;
        PinSource++;
    }
    return PinSource;
}

static IRQn_Type EXTI_GetIRQn(Pin_TypeDef Pin)
{
    IRQn_Type EXTIx_IRQn;
    uint8_t Pinx = SAL_GPIO_Get_Bits(Pin);

    if(Pinx <= 4)
    {
        switch(Pinx)
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
//    else if(Pinx >= 5 && Pinx <= 9)
//        EXTIx_IRQn = EXTI9_5_IRQn;
//    else if(Pinx >= 10 && Pinx <= 15)
//        EXTIx_IRQn = EXTI15_10_IRQn;
    
    return EXTIx_IRQn;
}

void SAL_Exit_Init(Pin_TypeDef Pin , CallbackFunction_t function , exint_polarity_config_type Trigger_Mode, uint32_t preempt_priority, uint32_t sub_priority)
{
    
    /*外部中断结构体初始化*/
    exint_init_type exint_init_struct;
    /*外设复用时钟*/
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK,TRUE);                    \
    
    gpio_port_source_type GPIO_PORT_SOURCE_GPIOX;
    gpio_type* GPIOX = GPIO_MAP[Pin].GPIOX;
    uint8_t BTIS = SAL_GPIO_Get_Bits(Pin);
    
    /* 放在对应的中断回调函数里 */
    EXTI_Function[BTIS] = function;
    
    /* 选择中断源时钟 */
    if(GPIOX == GPIOA) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOA;
    if(GPIOX == GPIOB) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOB;
    if(GPIOX == GPIOC) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOC;
    if(GPIOX == GPIOD) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOD;
    
    uint32_t EXINT_LINE_X = (uint32_t)GPIO_MAP[Pin].PinX;
    
    /*外部中断源的配置*/
    gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOX, (gpio_pins_source_type)BTIS);
    /*外部中断结构体的使用默认值*/
    exint_default_para_init(&exint_init_struct);
    /*中断源是能*/
    exint_init_struct.line_enable=TRUE;
    /*中断源模式*/
    exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
    /*中断源选择*/
    exint_init_struct.line_select=EXINT_LINE_X;
    /*中断事件*/
    exint_init_struct.line_polarity=Trigger_Mode;
    /*中断初始化*/
    exint_init(&exint_init_struct);
    /*中断管理优先级*/
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    /*中断服务函数是能*/
    nvic_irq_enable(EXTI_GetIRQn(Pin), preempt_priority , sub_priority);
}


extern "C" {
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

}


