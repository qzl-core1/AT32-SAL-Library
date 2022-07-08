#ifndef __SAL_USART_H
#define __SAL_USART_H   
#include "SAL.h"
#include <stdarg.h>
#include <stdio.h>
#define Stream_Length 256
class SAL_USART
{
public:
    SAL_USART(usart_type* _USARTX);
    void begin(uint32_t BaudRate);
    void Stop();
    void attachInterrupt(CallbackFunction_t function);
    void printf(const char *format, ...);
    void write(uint8_t chr);
    int hasNext(void);
    int read(void);
    void IRQhandle();
private:
    usart_type* USARTX;
    volatile uint16_t _rx_buffer_head,_rx_buffer_tail;
    uint8_t Tx_buff[Stream_Length];
    volatile uint8_t Rx_buff[Stream_Length];
    void(*USART_IRQ)();
};


extern SAL_USART SAL_USART1;
extern SAL_USART SAL_USART2;
extern SAL_USART SAL_USART3;


#endif
