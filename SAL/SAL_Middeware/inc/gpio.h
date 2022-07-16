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

/*���ų�ʼ��*/
void __gpio_init(Pin_TypeDef Pinx,Pin_Mode_type mode,Pin_PULL_type pull);
/*������������ߵ͵�ƽ*/
void __gpio_write_Pin(Pin_TypeDef Pinx,uint16_t level);
/*��ȡĳ��GPIO�ĵ�ƽ*/
uint8_t __gpio_read_Pin(Pin_TypeDef Pinx); 
/* ����ĳ�����Ŷ�Ӧ��λ�� */
uint8_t __gpio_get_Bits(Pin_TypeDef Pinx);
/* ��ʼ��Ϊ���i2c��ģʽ */
void __i2c_gpio_init(Pin_TypeDef scl,Pin_TypeDef sda);
/* ��ȡ�ܽŷ��� */
gpio_type* __gpio_port_get(Pin_TypeDef Pinx);
/* ��ȡ�ܽź� */
uint32_t __gpio_pin_get(Pin_TypeDef Pinx);
/* ��ȡ���Ŷ�Ӧ�Ķ�ʱ�� */
tmr_type* __gpio_get_timer(Pin_TypeDef Pinx);
uint16_t __gpio_get_pwm_channel(Pin_TypeDef Pinx);
#ifdef __cplusplus
}
#endif  

#endif
