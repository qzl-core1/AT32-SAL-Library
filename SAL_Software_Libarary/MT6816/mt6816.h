#ifndef __MT6816_H
#define __MT6816_H
#include "SAL.h"

class mt6816
{
    public:
        mt6816(SAL_SPI* hspi,Pin_TypeDef pin);
        void begin(void);
        float get_Angle(void);
    private:
        SAL_SPI* spi;
        Pin_TypeDef Pin;
        uint8_t read_regist(uint8_t reg);
        uint16_t read_raw_date(void);
};

#endif
