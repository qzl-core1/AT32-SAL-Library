#ifndef __EXINT_H
#define __EXINT_H
#include "SAL.h"
#ifdef __cplusplus
extern "C" {
#endif      
/*�ⲿ�жϳ�ʼ��*/
void __exit_Init(Pin_TypeDef Pin , CallbackFunction_t function , Exint_Mode Trigger_Mode, uint32_t preempt_priority, uint32_t sub_priority);    
#ifdef __cplusplus
}
#endif
#endif
