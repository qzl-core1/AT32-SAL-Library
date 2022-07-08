#ifndef __SAL_GPIO_H
#define __SAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "SAL.h"
#include "at32f403a_407_clock.h"
#include "at32f403a_407.h"
typedef struct 
{
  gpio_type* GPIOX;
  uint16_t PinX; 
}Pin_infor_typdef;

const Pin_infor_typdef GPIO_MAP[] =
{
   /*GPIOA*/
  {GPIOA,GPIO_PINS_0}, /* PA0 */
  {GPIOA,GPIO_PINS_1}, /* PA1 */
  {GPIOA,GPIO_PINS_2}, /* PA2 */
  {GPIOA,GPIO_PINS_3}, /* PA3 */
  {GPIOA,GPIO_PINS_4}, /* PA4 */
  {GPIOA,GPIO_PINS_5}, /* PA5 */
  {GPIOA,GPIO_PINS_6}, /* PA6 */
  {GPIOA,GPIO_PINS_7}, /* PA7 */
  {GPIOA,GPIO_PINS_8}, /* PA8 */
  {GPIOA,GPIO_PINS_9}, /* PA9 */
  {GPIOA,GPIO_PINS_10}, /* PA10 */
  {GPIOA,GPIO_PINS_11}, /* PA11 */
  {GPIOA,GPIO_PINS_12}, /* PA12 */
  {GPIOA,GPIO_PINS_13}, /* PA13 */
  {GPIOA,GPIO_PINS_14}, /* PA14 */
  {GPIOA,GPIO_PINS_15}, /* PA15 */
  /*GPIOB*/
  {GPIOB,GPIO_PINS_0}, /* PB0 */
  {GPIOB,GPIO_PINS_1}, /* PB1 */
  {GPIOB,GPIO_PINS_2}, /* PB2 */
  {GPIOB,GPIO_PINS_3}, /* PB3 */
  {GPIOB,GPIO_PINS_4}, /* PB4 */
  {GPIOB,GPIO_PINS_5}, /* PB5 */
  {GPIOB,GPIO_PINS_6}, /* PB6 */
  {GPIOB,GPIO_PINS_7}, /* PB7 */
  {GPIOB,GPIO_PINS_8}, /* PB8 */
  {GPIOB,GPIO_PINS_9}, /* PB9 */
  {GPIOB,GPIO_PINS_10}, /* PB10 */
  {GPIOB,GPIO_PINS_11}, /* PB11 */
  {GPIOB,GPIO_PINS_12}, /* PB12 */
  {GPIOB,GPIO_PINS_13}, /* PB13 */
  {GPIOB,GPIO_PINS_14}, /* PB14 */
  {GPIOB,GPIO_PINS_15}, /* PB15 */
  /*GPIOC*/
  {GPIOC,GPIO_PINS_0}, /* PC0 */
  {GPIOC,GPIO_PINS_1}, /* PC1 */
  {GPIOC,GPIO_PINS_2}, /* PC2 */
  {GPIOC,GPIO_PINS_3}, /* PC3 */
  {GPIOC,GPIO_PINS_4}, /* PC4 */
  {GPIOC,GPIO_PINS_5}, /* PC5 */
  {GPIOC,GPIO_PINS_6}, /* PC6 */
  {GPIOC,GPIO_PINS_7}, /* PC7 */
  {GPIOC,GPIO_PINS_8}, /* PC8 */
  {GPIOC,GPIO_PINS_9}, /* PC9 */
  {GPIOC,GPIO_PINS_10}, /* PC10 */
  {GPIOC,GPIO_PINS_11}, /* PC11 */
  {GPIOC,GPIO_PINS_12}, /* PC12 */
  {GPIOC,GPIO_PINS_13}, /* PC13 */
  {GPIOC,GPIO_PINS_14}, /* PC14 */
  {GPIOC,GPIO_PINS_15}, /* PC15 */
  /*GPIOD*/
  {GPIOD,GPIO_PINS_0}, /* PD0 */
  {GPIOD,GPIO_PINS_1}, /* PD1 */
  {GPIOD,GPIO_PINS_2}, /* PD2 */
  {GPIOD,GPIO_PINS_3}, /* PD3 */
  {GPIOD,GPIO_PINS_4}, /* PD4 */
  {GPIOD,GPIO_PINS_5}, /* PD5 */
  {GPIOD,GPIO_PINS_6}, /* PD6 */
  {GPIOD,GPIO_PINS_7}, /* PD7 */
  {GPIOD,GPIO_PINS_8}, /* PD8 */
  {GPIOD,GPIO_PINS_9}, /* PD9 */
  {GPIOD,GPIO_PINS_10}, /* PD10 */
  {GPIOD,GPIO_PINS_11}, /* PD11 */
  {GPIOD,GPIO_PINS_12}, /* PD12 */
  {GPIOD,GPIO_PINS_13}, /* PD13 */
  {GPIOD,GPIO_PINS_14}, /* PD14 */
  {GPIOD,GPIO_PINS_15}, /* PD15 */
  #ifdef GPIOE
  /*GPIOE*/
  {GPIOE,GPIO_PINS_0}, /* PE0 */
  {GPIOE,GPIO_PINS_1}, /* PE1 */
  {GPIOE,GPIO_PINS_2}, /* PE2 */
  {GPIOE,GPIO_PINS_3}, /* PE3 */
  {GPIOE,GPIO_PINS_4}, /* PE4 */
  {GPIOE,GPIO_PINS_5}, /* PE5 */
  {GPIOE,GPIO_PINS_6}, /* PE6 */
  {GPIOE,GPIO_PINS_7}, /* PE7 */
  {GPIOE,GPIO_PINS_8}, /* PE8 */
  {GPIOE,GPIO_PINS_9}, /* PE9 */
  {GPIOE,GPIO_PINS_10}, /* PE10 */
  {GPIOE,GPIO_PINS_11}, /* PE11 */
  {GPIOE,GPIO_PINS_12}, /* PE12 */
  {GPIOE,GPIO_PINS_13}, /* PE13 */
  {GPIOE,GPIO_PINS_14}, /* PE14 */
  {GPIOE,GPIO_PINS_15}, /* PE15 */
  #endif
  #ifdef GPIOF
  /*GPIOF*/
  {GPIOF,GPIO_PINS_0}, /* PF0 */
  {GPIOF,GPIO_PINS_1}, /* PF1 */
  {GPIOF,GPIO_PINS_2}, /* PF2 */
  {GPIOF,GPIO_PINS_3}, /* PF3 */
  {GPIOF,GPIO_PINS_4}, /* PF4 */
  {GPIOF,GPIO_PINS_5}, /* PF5 */
  {GPIOF,GPIO_PINS_6}, /* PF6 */
  {GPIOF,GPIO_PINS_7}, /* PF7 */
  {GPIOF,GPIO_PINS_8}, /* PF8 */
  {GPIOF,GPIO_PINS_9}, /* PF9 */
  {GPIOF,GPIO_PINS_10}, /* PF10 */
  {GPIOF,GPIO_PINS_11}, /* PF11 */
  {GPIOF,GPIO_PINS_12}, /* PF12 */
  {GPIOF,GPIO_PINS_13}, /* PF13 */
  {GPIOF,GPIO_PINS_14}, /* PF14 */
  {GPIOF,GPIO_PINS_15}, /* PF15 */
  #endif
};


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

/*引脚初始化*/
void SAL_GPIO_Init(Pin_TypeDef Pinx,Pin_Mode_type mode,Pin_PULL_type pull);
/*控制引脚输出高低电平*/
void SAL_GPIO_Write_Pin(Pin_TypeDef Pinx,uint16_t level);
/*读取某个GPIO的电平*/
uint8_t SAL_GPIO_Read_Pin(Pin_TypeDef Pinx);    
uint8_t SAL_GPIO_Get_Bits(Pin_TypeDef Pinx);
void SAL_Exit_Init(Pin_TypeDef Pin , CallbackFunction_t function , exint_polarity_config_type Trigger_Mode, uint32_t preempt_priority, uint32_t sub_priority);
#ifdef __cplusplus
}// extern "C"
#endif
#endif
