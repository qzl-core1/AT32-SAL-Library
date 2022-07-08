#include "SAL_USART.h"
/*串口构造函数*/
SAL_USART::SAL_USART(usart_type *_USARTX)
{
    this->USARTX = _USARTX;
    this->USART_IRQ = 0;
}
/*启动串口的函数*/
void SAL_USART::begin(uint32_t BaudRate)
{

    usart_type *_USARTX = this->USARTX;
    /*初始化对应的时钟和引脚,默认使用前3个串口*/
    if (_USARTX == USART1)
    {
        /*PA9->TX*/
        SAL_GPIO_Init(PA9, PIN_MUX, PULL_NONE);
        /*PA10->RX*/
        SAL_GPIO_Init(PA10, INPUT, PULL_UP);
        crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
        /*中断分组*/
        nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
        nvic_irq_enable(USART1_IRQn, 0, 0);
    }
    else if (_USARTX == USART2)
    {
        crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);
        /*PA2->TX*/
        SAL_GPIO_Init(PA2, PIN_MUX, PULL_NONE);
        /*PA3->RX*/
        SAL_GPIO_Init(PA3, INPUT, PULL_UP);
        nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
        nvic_irq_enable(USART2_IRQn, 0, 0);
    }
    else if (_USARTX == USART3)
    {
        crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);
        /*PA2->TX*/
        SAL_GPIO_Init(PB10, PIN_MUX, PULL_NONE);
        /*PA3->RX*/
        SAL_GPIO_Init(PB11, INPUT, PULL_UP);
        nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
        nvic_irq_enable(USART3_IRQn, 0, 0);
    }
    /*初始化串口的寄存器*/
    usart_init(_USARTX, BaudRate, USART_DATA_8BITS, USART_STOP_1_BIT);
    /*初始化中断接收*/
    usart_interrupt_enable(_USARTX, USART_RDBF_INT, TRUE);
    /*使能串口*/
    usart_parity_selection_config(_USARTX, USART_PARITY_NONE);
    usart_transmitter_enable(_USARTX, TRUE);
    usart_receiver_enable(_USARTX, TRUE);
    usart_enable(_USARTX, TRUE);
}
/*停止USART*/
void SAL_USART::Stop()
{
    usart_enable(this->USARTX, FALSE);
}

/*中断回调函数*/
void SAL_USART::attachInterrupt(CallbackFunction_t function)
{
    USART_IRQ = function;
}
/* 查看缓冲区有多少可用字符 */
int SAL_USART::hasNext(void)
{
    return ((unsigned int)(Stream_Length + _rx_buffer_head - _rx_buffer_tail)) % Stream_Length;
}

/* 从缓冲区读出一个字符 */
int SAL_USART::read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (_rx_buffer_head == _rx_buffer_tail)
    {
        return -1;
    }
    else
    {
        unsigned char c = Rx_buff[_rx_buffer_tail];
        _rx_buffer_tail = (uint16_t)(_rx_buffer_tail + 1) % Stream_Length;
        return c;
    }
}

/*中断服务函数*/
void SAL_USART::IRQhandle()
{
    while (usart_flag_get(USART1, USART_RDBF_FLAG) == RESET) {};
    uint8_t c = usart_data_receive(USARTX);
    uint16_t i = (uint16_t)(_rx_buffer_head + 1) % Stream_Length;
    if (i != _rx_buffer_tail)
    {
        Rx_buff[_rx_buffer_head] = c;
        _rx_buffer_head = i;
    }
    if (USART_IRQ) USART_IRQ();
}
/*单独写一个字*/
void SAL_USART::write(uint8_t chr)
{
    while (usart_flag_get(this->USARTX, USART_TDBE_FLAG) == RESET);
    usart_data_transmit(this->USARTX, chr);
}

/*printf函数*/
void SAL_USART::printf(const char *format, ...)
{
    va_list args;
    uint32_t length;
    va_start(args, format);
    length = vsnprintf((char *)Tx_buff, sizeof(Tx_buff) + 1, (char *)format, args);
    va_end(args);

    for (int i = 0; i < length; i++)
    {
        while (usart_flag_get(this->USARTX, USART_TDBE_FLAG) == RESET);
        usart_data_transmit(this->USARTX, (uint8_t)Tx_buff[i]);
    }
}

/*三个串口的对象*/
SAL_USART SAL_USART1(USART1);
SAL_USART SAL_USART2(USART2);
SAL_USART SAL_USART3(USART3);



//中断函数的入口
extern "C" {
    void USART1_IRQHandler(void)
    {
        SAL_USART1.IRQhandle();
    }

    void USART2_IRQHandler(void)
    {
        SAL_USART2.IRQhandle();
    }

    void USART3_IRQHandler(void)
    {
        SAL_USART3.IRQhandle();
    }
}
