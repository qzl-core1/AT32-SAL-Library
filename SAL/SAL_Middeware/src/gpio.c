#include "gpio.h"

const Pin_infor_typdef GPIO_MAP[PIN_MAX] =
{
    /*GPIO_Type* GPIOx;  //对应GPIOx地址
    TIM_Type* TIMx;      //对应TIMx地址
    ADC_Type* ADCx;      //对应ADCx地址

    uint16_t GPIO_Pin_x;    //对应GPIO_Pin位
    uint8_t TimerChannel;   //对应定时器通道
    uint8_t ADC_Channel;*/  //对应ADC通道
    {GPIOA, TIM2, ADC1,  GPIO_Pin_0, 1, ADC_Channel_0}, /* PA0 */
    {GPIOA, TIM2, ADC1,  GPIO_Pin_1, 2, ADC_Channel_1}, /* PA1 */
    {GPIOA, TIM2, ADC1,  GPIO_Pin_2, 3, ADC_Channel_2}, /* PA2 */
    {GPIOA, TIM2, ADC1,  GPIO_Pin_3, 4, ADC_Channel_3}, /* PA3 */
    {GPIOA, NULL, ADC1,  GPIO_Pin_4, 0, ADC_Channel_4}, /* PA4 */
    {GPIOA, NULL, ADC1,  GPIO_Pin_5, 0, ADC_Channel_5}, /* PA5 */
    {GPIOA, TIM3, ADC1,  GPIO_Pin_6, 1, ADC_Channel_6}, /* PA6 */
    {GPIOA, TIM3, ADC1,  GPIO_Pin_7, 2, ADC_Channel_7}, /* PA7 */
    {GPIOA, TIM1, NULL,  GPIO_Pin_8, 1, ADC_Channel_X}, /* PA8 */
    {GPIOA, TIM1, NULL,  GPIO_Pin_9, 2, ADC_Channel_X}, /* PA9 */
    {GPIOA, TIM1, NULL, GPIO_Pin_10, 3, ADC_Channel_X}, /* PA10 */
    {GPIOA, TIM1, NULL, GPIO_Pin_11, 4, ADC_Channel_X}, /* PA11 */
    {GPIOA, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PA12 */
    {GPIOA, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PA13 */
    {GPIOA, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PA14 */
    {GPIOA, TIM2, NULL, GPIO_Pin_15, 1, ADC_Channel_X}, /* PA15 */

    {GPIOB, TIM3, ADC1,  GPIO_Pin_0, 3, ADC_Channel_8}, /* PB0 */
    {GPIOB, TIM3, ADC1,  GPIO_Pin_1, 4, ADC_Channel_9}, /* PB1 */
    {GPIOB, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PB2 */
    {GPIOB, TIM2, NULL,  GPIO_Pin_3, 2, ADC_Channel_X}, /* PB3 */
    {GPIOB, TIM3, NULL,  GPIO_Pin_4, 1, ADC_Channel_X}, /* PB4 */
    {GPIOB, TIM3, NULL,  GPIO_Pin_5, 2, ADC_Channel_X}, /* PB5 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_6, 1, ADC_Channel_X}, /* PB6 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_7, 2, ADC_Channel_X}, /* PB7 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_8, 3, ADC_Channel_X}, /* PB8 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_9, 4, ADC_Channel_X}, /* PB9 */
    {GPIOB, TIM2, NULL, GPIO_Pin_10, 3, ADC_Channel_X}, /* PB10 */
    {GPIOB, TIM2, NULL, GPIO_Pin_11, 4, ADC_Channel_X}, /* PB11 */
    {GPIOB, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PB12 */
    {GPIOB, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PB13 */
#ifdef TMR12
    {GPIOB, TIM12, NULL, GPIO_Pin_14, 1, ADC_Channel_X},/* PB14 */
#else
    {GPIOB, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X},/* PB14 */
#endif /*TMR12*/
    {GPIOB, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PB15 */

    {GPIOC, NULL, ADC1,  GPIO_Pin_0, 0, ADC_Channel_10},/* PC0 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_1, 0, ADC_Channel_11},/* PC1 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_2, 0, ADC_Channel_12},/* PC2 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_3, 0, ADC_Channel_13},/* PC3 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_4, 0, ADC_Channel_14},/* PC4 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_5, 0, ADC_Channel_15},/* PC5 */
    {GPIOC, TIM3, NULL,  GPIO_Pin_6, 1, ADC_Channel_X}, /* PC6 */
    {GPIOC, TIM3, NULL,  GPIO_Pin_7, 2, ADC_Channel_X}, /* PC7 */
    {GPIOC, TIM3, NULL,  GPIO_Pin_8, 3, ADC_Channel_X}, /* PC8 */
    {GPIOC, TIM3, NULL,  GPIO_Pin_9, 4, ADC_Channel_X}, /* PC9 */
    {GPIOC, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PC10 */
    {GPIOC, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PC11 */
    {GPIOC, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PC12 */
    {GPIOC, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PC13 */
    {GPIOC, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PC14 */
    {GPIOC, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PC15 */

    {GPIOD, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PD0 */
    {GPIOD, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PD1 */
    {GPIOD, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PD2 */
    {GPIOD, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PD3 */
    {GPIOD, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PD4 */
    {GPIOD, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X}, /* PD5 */
    {GPIOD, NULL, NULL,  GPIO_Pin_6, 0, ADC_Channel_X}, /* PD6 */
    {GPIOD, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PD7 */
    {GPIOD, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PD8 */
    {GPIOD, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PD9 */
    {GPIOD, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PD10 */
    {GPIOD, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PD11 */
    {GPIOD, TIM4, NULL, GPIO_Pin_12, 1, ADC_Channel_X}, /* PD12 */
    {GPIOD, TIM4, NULL, GPIO_Pin_13, 2, ADC_Channel_X}, /* PD13 */
    {GPIOD, TIM4, NULL, GPIO_Pin_14, 3, ADC_Channel_X}, /* PD14 */
    {GPIOD, TIM4, NULL, GPIO_Pin_15, 4, ADC_Channel_X}, /* PD15 */

#ifdef GPIOE
    {GPIOE, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PE0 */
    {GPIOE, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PE1 */
    {GPIOE, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PE2 */
    {GPIOE, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PE3 */
    {GPIOE, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PE4 */
    {GPIOE, TIM9, NULL,  GPIO_Pin_5, 1, ADC_Channel_X}, /* PE5 */
    {GPIOE, TIM9, NULL,  GPIO_Pin_6, 2, ADC_Channel_X}, /* PE6 */
    {GPIOE, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PE7 */
    {GPIOE, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PE8 */
    {GPIOE, TIM1, NULL,  GPIO_Pin_9, 1, ADC_Channel_X}, /* PE9 */
    {GPIOE, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PE10 */
    {GPIOE, TIM1, NULL, GPIO_Pin_11, 2, ADC_Channel_X}, /* PE11 */
    {GPIOE, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PE12 */
    {GPIOE, TIM1, NULL, GPIO_Pin_13, 3, ADC_Channel_X}, /* PE13 */
    {GPIOE, TIM1, NULL, GPIO_Pin_14, 4, ADC_Channel_X}, /* PE14 */
    {GPIOE, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PE15 */
#endif /*GPIOE*/

#ifdef GPIOF
    {GPIOF, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PF0 */
    {GPIOF, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PF1 */
    {GPIOF, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PF2 */

#ifdef ADC3
    {GPIOF, NULL, ADC3,  GPIO_Pin_3, 0, ADC_Channel_9}, /* PF3 */
    {GPIOF, NULL, ADC3,  GPIO_Pin_4, 0, ADC_Channel_14},/* PF4 */
    {GPIOF, NULL, ADC3,  GPIO_Pin_5, 0, ADC_Channel_15},/* PF5 */
    {GPIOF, TIM10, ADC3,  GPIO_Pin_6, 1, ADC_Channel_4}, /* PF6 */
    {GPIOF, TIM11, ADC3,  GPIO_Pin_7, 1, ADC_Channel_5}, /* PF7 */
    {GPIOF, TIM13, ADC3,  GPIO_Pin_8, 1, ADC_Channel_6}, /* PF8 */
    {GPIOF, TIM14, ADC3,  GPIO_Pin_9, 1, ADC_Channel_7}, /* PF9 */
    {GPIOF, NULL, ADC3, GPIO_Pin_10, 0, ADC_Channel_8}, /* PF10 */
#else
    {GPIOF, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PF3 */
    {GPIOF, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X},/* PF4 */
    {GPIOF, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X},/* PF5 */
    {GPIOF, TIM10, NULL,  GPIO_Pin_6, 1, ADC_Channel_X}, /* PF6 */
    {GPIOF, TIM11, NULL,  GPIO_Pin_7, 1, ADC_Channel_X}, /* PF7 */
    {GPIOF, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PF8 */
    {GPIOF, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PF9 */
    {GPIOF, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PF10 */
#endif /*ADC3*/
    {GPIOF, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PF11 */
    {GPIOF, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PF12 */
    {GPIOF, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PF13 */
    {GPIOF, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PF14 */
    {GPIOF, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PF15 */
#endif /*GPIOF*/

#ifdef GPIOG
    {GPIOG, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PG0 */
    {GPIOG, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PG1 */
    {GPIOG, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PG2 */
    {GPIOG, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PG3 */
    {GPIOG, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PG4 */
    {GPIOG, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X}, /* PG5 */
    {GPIOG, NULL, NULL,  GPIO_Pin_6, 0, ADC_Channel_X}, /* PG6 */
    {GPIOG, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PG7 */
    {GPIOG, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PG8 */
    {GPIOG, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PG9 */
    {GPIOG, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PG10 */
    {GPIOG, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PG11 */
    {GPIOG, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PG12 */
    {GPIOG, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PG13 */
    {GPIOG, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PG14 */
    {GPIOG, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PG15 */
#endif /*GPIOG*/
};


void __gpio_init(Pin_TypeDef Pinx, Pin_Mode_type mode, Pin_PULL_type pull)
{
    gpio_type *GPIOX = GPIO_MAP[Pinx].GPIOX;
    uint16_t PINX = GPIO_MAP[Pinx].PinX;
    /*开启对应的时钟*/
    if (GPIOX == GPIOA) crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    if (GPIOX == GPIOB) crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    if (GPIOX == GPIOC) crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    if (GPIOX == GPIOD) crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    /*开始初始化*/
    gpio_init_type gpio_init_struct;
    /*默认初始化*/
    gpio_default_para_init(&gpio_init_struct);
    /* 输出强度 */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    /*模式确认*/
    if (mode == INPUT) gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    if (mode == OUTPUT) gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    if (mode == PIN_MUX) gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    if (mode == ANALOG) gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
    /*引脚确认*/
    gpio_init_struct.gpio_pins =  PINX;
    /*选择上下拉*/
    if (pull == PULL_UP) gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    if (pull == PULL_DOWN) gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
    if (pull == PULL_NONE) gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOX, &gpio_init_struct);
}

void __i2c_gpio_init(Pin_TypeDef scl, Pin_TypeDef sda)
{
    /*开始初始化*/
    gpio_init_type gpio_init_struct;
    /*默认初始化*/
    gpio_default_para_init(&gpio_init_struct);


    /* 初始化scl */
    gpio_type *GPIOX = GPIO_MAP[scl].GPIOX;
    uint16_t PINX = GPIO_MAP[scl].PinX;
    gpio_init_struct.gpio_pins = PINX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(GPIOX, &gpio_init_struct);

    /* 初始化sda */
    GPIOX = GPIO_MAP[sda].GPIOX;
    PINX = GPIO_MAP[sda].PinX;
    gpio_init_struct.gpio_pins = PINX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(GPIOX, &gpio_init_struct);
}

/*控制GPIO输出*/
void __gpio_write_Pin(Pin_TypeDef Pinx, uint16_t level)
{
    gpio_type *GPIOX = GPIO_MAP[Pinx].GPIOX;
    uint16_t PINX = GPIO_MAP[Pinx].PinX;
    if (level) gpio_bits_set(GPIOX, PINX);
    else gpio_bits_reset(GPIOX, PINX);
}
/*读取某个GPIO的电平*/
uint8_t __gpio_read_Pin(Pin_TypeDef Pinx)
{
    uint8_t status = RESET;
    gpio_type *GPIOX = GPIO_MAP[Pinx].GPIOX;
    uint16_t PINX = GPIO_MAP[Pinx].PinX;

    if ((GPIOX->idt & PINX) != RESET)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }

    return status;
}

/* 返回引脚对应的位数 */
uint8_t __gpio_get_Bits(Pin_TypeDef Pinx)
{
    uint16_t PinSource = 0;
    uint16_t GPIO_Pin_x = GPIO_MAP[Pinx].PinX;
    while (GPIO_Pin_x > 1)
    {
        GPIO_Pin_x >>= 1;
        PinSource++;
    }
    return PinSource;
}
/* 获取引脚对应的组别 */
gpio_type *__gpio_port_get(Pin_TypeDef Pinx)
{
    return GPIO_MAP[Pinx].GPIOX;
}

/* 获取引脚对应的io号 */
uint32_t __gpio_pin_get(Pin_TypeDef Pinx)
{
    return GPIO_MAP[Pinx].PinX;
}

tmr_type* __gpio_get_timer(Pin_TypeDef Pinx)
{
    return GPIO_MAP[Pinx].TIMx;
}

uint16_t __gpio_get_pwm_channel(Pin_TypeDef Pinx)
{
    return GPIO_MAP[Pinx].TimerChannel;
}



