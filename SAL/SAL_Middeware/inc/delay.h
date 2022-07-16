#ifndef __DELAY_H
#define __DELAY_H

#include "SAL.h"
#ifdef __cplusplus
extern "C" {
#endif    
void delay_init(void);
void delay_ms(uint32_t ms);
uint32_t mills(void);
    
#ifdef __cplusplus
}
#endif

#endif


