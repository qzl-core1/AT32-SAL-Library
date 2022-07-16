#ifndef __TIMER_H
#define __TIMER_H
#include "SAL.h"
#ifdef __cplusplus
extern "C" {
#endif  
void _timer_IT_Init(Timer_TypeDef Timx, CallbackFunction_t function ,uint32_t pr, uint32_t div, uint32_t preempt_priority, uint32_t sub_priority);
#ifdef __cplusplus
}
#endif  
#endif
