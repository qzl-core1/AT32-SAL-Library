#include "exint.h"


/*�ⲿ�жϻص�����ָ������*/
static CallbackFunction_t EXTI_Function[16] = {0};

static IRQn_Type EXTI_GetIRQn(Pin_TypeDef Pin)
{
    IRQn_Type EXTIx_IRQn;
    uint8_t Pinx = __gpio_get_Bits(Pin);

    if (Pinx <= 4)
    {
        switch (Pinx)
        {
        case 0:
            EXTIx_IRQn = EXINT0_IRQn;
            break;
        case 1:
            EXTIx_IRQn = EXINT1_IRQn;
            break;
        case 2:
            EXTIx_IRQn = EXINT2_IRQn;
            break;
        case 3:
            EXTIx_IRQn = EXINT3_IRQn;
            break;
        case 4:
            EXTIx_IRQn = EXINT4_IRQn;
            break;
        }
    }
    else if (Pinx >= 5 && Pinx <= 9)
        EXTIx_IRQn = EXINT9_5_IRQn;
    else if (Pinx >= 10 && Pinx <= 15)
        EXTIx_IRQn = EXINT15_10_IRQn;

    return EXTIx_IRQn;
}

void __exit_Init(Pin_TypeDef Pin, CallbackFunction_t function, Exint_Mode Trigger_Mode, uint32_t preempt_priority, uint32_t sub_priority)
{

    /*�ⲿ�жϽṹ���ʼ��*/
    exint_init_type exint_init_struct;
    /*���踴��ʱ��*/
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    /* ��ȡ���ŵ���Ϣ */
    gpio_port_source_type GPIO_PORT_SOURCE_GPIOX;
    gpio_type *GPIOX = __gpio_port_get(Pin);
    uint8_t BTIS = __gpio_get_Bits(Pin);

    /* ������ʽƥ�� */
    exint_polarity_config_type trigger_mode;
    switch (Trigger_Mode)
    {
    case Rising_Edge_Mode:
        trigger_mode = EXINT_TRIGGER_RISING_EDGE;
        __gpio_init(Pin, PIN_MUX, PULL_DOWN);
        break;


    case Falling_Edge_Mode:
        trigger_mode = EXINT_TRIGGER_FALLING_EDGE;
        __gpio_init(Pin, PIN_MUX, PULL_UP);
        break;


    case Both_Edge_Mode:
        trigger_mode = EXINT_TRIGGER_BOTH_EDGE;
        __gpio_init(Pin, PIN_MUX, PULL_UP);
        break;
    }

    /* ���ڶ�Ӧ���жϻص������� */
    EXTI_Function[BTIS] = function;

    /* ѡ���ж�Դʱ�� */
    if (GPIOX == GPIOA) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOA;
    if (GPIOX == GPIOB) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOB;
    if (GPIOX == GPIOC) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOC;
    if (GPIOX == GPIOD) GPIO_PORT_SOURCE_GPIOX = GPIO_PORT_SOURCE_GPIOD;

    uint32_t EXINT_LINE_X = __gpio_pin_get(Pin);

    /*�ⲿ�ж�Դ������*/
    gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOX, (gpio_pins_source_type)BTIS);
    /*�ⲿ�жϽṹ���ʹ��Ĭ��ֵ*/
    exint_default_para_init(&exint_init_struct);
    /*�ж�Դ����*/
    exint_init_struct.line_enable = TRUE;
    /*�ж�Դģʽ*/
    exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
    /*�ж�Դѡ��*/
    exint_init_struct.line_select = EXINT_LINE_X;
    /*�ж��¼�*/
    exint_init_struct.line_polarity = trigger_mode;
    /*�жϳ�ʼ��*/
    exint_init(&exint_init_struct);
    /*�жϹ������ȼ�*/
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_3);
    /*�жϷ���������*/
    nvic_irq_enable(EXTI_GetIRQn(Pin), preempt_priority, sub_priority);
}


#define EXTIx_IRQHANDLER(n) \
do{\
    if(exint_flag_get(EXINT_LINE_##n) != RESET)\
    {\
        if(EXTI_Function[n]) EXTI_Function[n]();\
        exint_flag_clear(EXINT_LINE_##n);\
    }\
}while(0)

/*�ⲿ�жϷ�����*/
/**
  * @brief  �ⲿ�ж���ڣ�ͨ��0
  * @param  ��
  * @retval ��
  */
void EXINT0_IRQHandler(void)
{
    EXTIx_IRQHANDLER(0);
}

/**
  * @brief  �ⲿ�ж���ڣ�ͨ��1
  * @param  ��
  * @retval ��
  */
void EXINT1_IRQHandler(void)
{
    EXTIx_IRQHANDLER(1);
}

/**
  * @brief  �ⲿ�ж���ڣ�ͨ��2
  * @param  ��
  * @retval ��
  */
void EXINT2_IRQHandler(void)
{
    EXTIx_IRQHANDLER(2);
}

/**
  * @brief  �ⲿ�ж���ڣ�ͨ��3
  * @param  ��
  * @retval ��
  */
void EXINT3_IRQHandler(void)
{
    EXTIx_IRQHANDLER(3);
}

/**
  * @brief  �ⲿ�ж���ڣ�ͨ��4
  * @param  ��
  * @retval ��
  */
void EXINT4_IRQHandler(void)
{
    EXTIx_IRQHANDLER(4);
}

/**
  * @brief  �ⲿ�ж���ڣ�ͨ��5-9
  * @param  ��
  * @retval ��
  */
void EXINT9_5_IRQHandler(void)
{
    EXTIx_IRQHANDLER(5);
    EXTIx_IRQHANDLER(6);
    EXTIx_IRQHANDLER(7);
    EXTIx_IRQHANDLER(8);
    EXTIx_IRQHANDLER(9);
}

void EXINT15_10_IRQHandler(void)
{
    EXTIx_IRQHANDLER(10);
    EXTIx_IRQHANDLER(11);
    EXTIx_IRQHANDLER(12);
    EXTIx_IRQHANDLER(13);
    EXTIx_IRQHANDLER(14);
    EXTIx_IRQHANDLER(15);
}
