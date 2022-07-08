/* 
    注意:
    该i2c库是软件i2c,考虑大多数场景下i2c都是低速场景,没必要使用硬件i2c,所以该库在移植时直接依赖于SAL_GPIO
*/
#ifndef __SAL_I2C_H
#define __SAL_I2C_H
#include "SAL.h"

class SAL_I2C
{
    public:
        SAL_I2C(Pin_TypeDef SCL,Pin_TypeDef SDA);
        void begin(void);
        void i2c_start(void);
        void i2c_stop(void);
        void send(uint8_t data);
        uint8_t read(uint8_t ack);
        uint8_t wait_ack(void);
        void i2c_ack(void);
        void i2c_Nack(void);
        uint8_t Write_Byte(uint8_t addr,uint8_t len,uint8_t* buf);
        uint8_t Read_Byte(uint8_t addr,uint8_t len,uint8_t* buf);
        uint8_t Read_Mem_one_Byte(uint8_t addr,uint8_t reg);
        uint8_t Write_Mem_one_Byte(uint8_t addr,uint8_t reg,uint8_t byte);
        uint8_t Write_Mem_Byte(uint8_t addr,uint8_t reg,uint8_t len,uint8_t* buf);
        uint8_t Read_Mem_Byte(uint8_t addr,uint8_t reg,uint8_t len,uint8_t* buf);
    
    private:
        Pin_TypeDef scl;
        Pin_TypeDef sda;
        void i2c_delay(uint16_t ns);
        void I2C_SDA_HIGH();
        void I2C_SCL_HIGH();
        void I2C_SDA_LOW();
        void I2C_SCL_LOW();
        uint8_t I2C_SDA_READ();
};
extern SAL_I2C SAL_I2C1;
#endif 
