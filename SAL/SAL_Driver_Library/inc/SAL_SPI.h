#ifndef __SAL_SPI_H
#define __SAL_SPI_H
#include "SAL.h"

class SAL_SPI
{
    public:
        SAL_SPI(spi_type* spi);
        void begin();
        void begin(SPI_CLOCK_MODE clock_mode,SPI_DATA_FRAME data_frame,DIV_FREQ div_freq);
        void set_clock(SPI_CLOCK_MODE clock_mode);
        void set_data_frame(SPI_DATA_FRAME data_frame);
        void set_div(DIV_FREQ div_freq);
        void write(uint16_t data);
        void write(uint8_t* data,uint32_t length);
        void write_regist(uint8_t reg,uint8_t data);
        void write_regist(uint8_t reg,uint16_t len,uint8_t* data);
        uint8_t read(uint8_t reg);
        uint8_t transmit(uint8_t reg);
        uint16_t transmit16(uint16_t data);
        void read(uint8_t reg,uint16_t len,uint8_t* data);
    private:
        spi_type* spi;
        spi_init_type spi_init_struct;
        
};
extern SAL_SPI SPI;
extern SAL_SPI SPI_2;

#endif
