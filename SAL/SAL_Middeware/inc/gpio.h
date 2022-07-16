#ifndef __GPIO_H
#define __GPIO_H
#include "SAL.h"
#ifdef __cplusplus
extern "C" {
#endif  
#define ADC_Channel_X ((uint8_t)0xFF)
typedef struct 
{
    gpio_type* GPIOX;
    tmr_type* TIMx;
    adc_type* ADCx;

    uint16_t PinX;
    
    uint8_t TimerChannel;
    uint8_t ADC_Channel;
}Pin_infor_typdef;

/*引脚初始化*/
void __gpio_init(Pin_TypeDef Pinx,Pin_Mode_type mode,Pin_PULL_type pull);
/*控制引脚输出高低电平*/
void __gpio_write_Pin(Pin_TypeDef Pinx,uint16_t level);
/*读取某个GPIO的电平*/
uint8_t __gpio_read_Pin(Pin_TypeDef Pinx); 
/* 返回某个引脚对应的位数 */
uint8_t __gpio_get_Bits(Pin_TypeDef Pinx);
/* 初始化为软件i2c的模式 */
void __i2c_gpio_init(Pin_TypeDef scl,Pin_TypeDef sda);
/* 获取管脚分组 */
gpio_type* __gpio_port_get(Pin_TypeDef Pinx);
/* 获取管脚号 */
uint32_t __gpio_pin_get(Pin_TypeDef Pinx);
/* 获取引脚对应的定时器 */
tmr_type* __gpio_get_timer(Pin_TypeDef Pinx);
uint16_t __gpio_get_pwm_channel(Pin_TypeDef Pinx);
#ifdef __cplusplus
}
#endif  

#endif
