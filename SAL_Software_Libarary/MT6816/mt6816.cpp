#include "mt6816.h"

mt6816::mt6816(SAL_SPI* hspi,Pin_TypeDef pin)
{
    spi = hspi;
    Pin = pin;
}

void mt6816::begin()
{
    SAL_GPIO_Init(Pin,OUTPUT,PULL_NONE);
}

uint8_t mt6816::read_regist(uint8_t reg)
{
    uint8_t data;    
    SAL_GPIO_Write_Pin(Pin,0);
    data = spi->read(reg|0x80);
    SAL_GPIO_Write_Pin(Pin,1);
    return data;
}

uint16_t mt6816::read_raw_date(void)
{
   uint8_t data[2];
   uint16_t Read_Rgister;
   data[0] = read_regist(0x03);
   data[1] = read_regist(0x04);
   Read_Rgister = data[0]<<8|data[1]; // 把两个uint8 合并为 uint16
   Read_Rgister = Read_Rgister>>2;

   return Read_Rgister;
}

float mt6816::get_Angle(void)
{
    uint16_t angledata=0;
    float radian = 0;
    angledata = read_raw_date();
    radian = angledata*1.0f/16384*360*2;
    return radian;
}
