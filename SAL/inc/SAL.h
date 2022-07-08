#ifndef __SAL_H
#define __SAL_H

#ifdef __cplusplus
extern "C" {
#endif
    
/*平台对应的头文件*/
#include "at32f403a_407_clock.h"
#include "at32f403a_407.h"
    
 
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

typedef enum
{
    SPI_MODE_0, // LOW phase  1 edge
    SPI_MODE_1, // LOW phase  2 edge
    SPI_MODE_2, // HIGH phase  1 edge
    SPI_MODE_3  // HIGH phase  2 edge
}SPI_CLOCK_MODE;

typedef enum
{
    Date_FRAME1,  // 8bit LSB
    Date_FRAME2,  // 8bit MSB
    Date_FRAME3,  // 16bit LSB
    Date_FRAME4,  // 16bit MSB
}SPI_DATA_FRAME;

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

typedef void(*CallbackFunction_t)(void);

/*内置头文件*/
#include "SAL_GPIO.h"
#include "SAL_USART.h"
#include "SAL_I2C.h"
#include "SAL_SPI.h"
#include <math.h>
void SAL_Delay(uint32_t ms);
void SAL_Init(void);
/* 一些通用的宏 */
#define PI 3.14159265f//PI圆周率
#ifdef __cplusplus
}
#endif

#endif
