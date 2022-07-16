#ifndef __SAL_H
#define __SAL_H

#ifdef __cplusplus
extern "C" {
#endif
    
/*平台对应的头文件*/
#include "at32f403a_407_clock.h"
#include "at32f403a_407.h"
#include "platform.h"
    
/* 引脚索引表 */
typedef enum {
    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
    PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
    PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
    PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, PD12, PD13, PD14, PD15,
#ifdef GPIOE
    PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7, PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15,
#endif
#ifdef GPIOF
    PF0, PF1, PF2, PF3, PF4, PF5, PF6, PF7, PF8, PF9, PF10, PF11, PF12, PF13, PF14, PF15,
#endif
#ifdef GPIOG
    PG0, PG1, PG2, PG3, PG4, PG5, PG6, PG7, PG8, PG9, PG10, PG11, PG12, PG13, PG14, PG15,
#endif
    PIN_MAX
} Pin_TypeDef;

/* 定时器索引表 */
typedef enum
{
    TIMER1 = 1,
    TIMER2 = 2,
    TIMER3 = 3,
    TIMER4 = 4,
    TIMER5 = 5,
    TIMER6 = 6,
    TIMER7 = 7,
    TIMER8 = 8,
    TIMER9 = 9,
    TIMER10 = 10,
    TIMER11 = 11,
    TIMER12 = 12,
    TIMER13 = 13,
    TIMER14 = 14,
}Timer_TypeDef;

/* spi时钟模式选择 */
typedef enum
{
    SPI_MODE_0, // LOW phase  1 edge
    SPI_MODE_1, // LOW phase  2 edge
    SPI_MODE_2, // HIGH phase  1 edge
    SPI_MODE_3  // HIGH phase  2 edge
}SPI_CLOCK_MODE;

/* spi数据格式选择 */
typedef enum
{
    Date_FRAME1,  // 8bit LSB
    Date_FRAME2,  // 8bit MSB
    Date_FRAME3,  // 16bit LSB
    Date_FRAME4,  // 16bit MSB
}SPI_DATA_FRAME;

/* 分频系数选择 */
typedef enum
{
  DIV_2,
  DIV_4,
  DIV_8,
  DIV_16,
  DIV_32,
  DIV_64,
  DIV_128
}DIV_FREQ;

/*输出模式枚举*/
typedef enum
{
    INPUT ,
    OUTPUT ,
    PIN_MUX ,
    ANALOG 
}Pin_Mode_type;

/*上下拉枚举*/
typedef enum
{
    PULL_UP ,
    PULL_DOWN ,
    PULL_NONE
}Pin_PULL_type;

/* 外部中断模式选择 */
typedef enum
{
    Rising_Edge_Mode,
    Falling_Edge_Mode,
    Both_Edge_Mode
}Exint_Mode;



typedef void(*CallbackFunction_t)(void);

/* 标准库函数 */
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

/* 中间件文件 */
#include "gpio.h"
#include "delay.h"
#include "exint.h"
#include "timer.h"
#include "pwm.h"

/* SAL初始化 */
void SAL_Init(void);
/* 全局延迟函数 */
void SAL_Delay(uint32_t ms);
/*引脚初始化*/
void SAL_GPIO_Init(Pin_TypeDef Pinx,Pin_Mode_type mode,Pin_PULL_type pull);
/*控制引脚输出高低电平*/
void SAL_GPIO_Write_Pin(Pin_TypeDef Pinx,uint16_t level);
/*读取某个GPIO的电平*/
uint8_t SAL_GPIO_Read_Pin(Pin_TypeDef Pinx);    
/* 软件i2c的管脚初始化函数 */
void SAL_I2C_GPIO_Init(Pin_TypeDef scl,Pin_TypeDef sda);
/* 外部中断设置 */
void SAL_Exit_Init(Pin_TypeDef Pin , CallbackFunction_t function , Exint_Mode Trigger_Mode, uint32_t preempt_priority, uint32_t sub_priority);
/* 定时器的设置 */
void SAL_Timer_Init(Timer_TypeDef Timx, CallbackFunction_t function ,uint32_t pr, uint32_t div, uint32_t preempt_priority, uint32_t sub_priority);
/* PWM设置 */
void SAL_PWM_Init(Pin_TypeDef Pin_x , uint32_t counter_period , uint32_t div);
/* 修改PWM占空比 */
void SAL_PWM_Write(Pin_TypeDef Pin_x,uint16_t val);
/* 一些通用的宏 */
#define PI 3.14159265f//PI圆周率



#ifdef __cplusplus
}
#endif


/* 以下是SAL的头文件层 */
#ifdef __cplusplus

/*内置头文件*/
#include "SAL_USART.h"
#include "SAL_I2C.h"
#include "SAL_SPI.h"

#endif


#endif

