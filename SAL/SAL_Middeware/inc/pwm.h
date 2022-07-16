#ifndef __PWM_H
#define __PWM_H
#include "SAL.h"

void __pwm_init(Pin_TypeDef Pin_x , uint32_t counter_period , uint32_t div);
void __pwm_write(Pin_TypeDef Pin_x,uint16_t val);

#endif
