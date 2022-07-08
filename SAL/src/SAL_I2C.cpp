#include "SAL_I2C.h"

#define I2C_DELAY 1  //I2C软件延迟倍数

/* 引脚选择 */
SAL_I2C::SAL_I2C(Pin_TypeDef SCL, Pin_TypeDef SDA)
{
    scl = SCL;
    sda = SDA;
}

/* 初始化i2c引脚 */
void SAL_I2C::begin(void)
{
    SAL_GPIO_Init(scl, OUTPUT, PULL_UP);
    SAL_GPIO_Init(sda, OUTPUT, PULL_UP);
    /*开始初始化*/
    gpio_init_type gpio_init_struct;
    /*默认初始化*/
    gpio_default_para_init(&gpio_init_struct);
    
    
    /* 初始化scl */
    gpio_type* GPIOX = GPIO_MAP[scl].GPIOX;
    uint16_t PINX = GPIO_MAP[scl].PinX;
    gpio_init_struct.gpio_pins = PINX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(GPIOX, &gpio_init_struct);
    
    /* 初始化sda */
    GPIOX = GPIO_MAP[sda].GPIOX;
    PINX = GPIO_MAP[sda].PinX;
    gpio_init_struct.gpio_pins = PINX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(GPIOX, &gpio_init_struct);
}

void SAL_I2C::I2C_SDA_HIGH()
{
    SAL_GPIO_Write_Pin(this->sda,1);
}

void SAL_I2C::I2C_SCL_HIGH()
{
    SAL_GPIO_Write_Pin(this->scl,1);
//    while(SAL_GPIO_Read_Pin(this->scl)==0);
}

void SAL_I2C::I2C_SDA_LOW()
{
    SAL_GPIO_Write_Pin(this->sda,0);
}

void SAL_I2C::I2C_SCL_LOW()
{
    SAL_GPIO_Write_Pin(this->scl,0);
}

uint8_t SAL_I2C::I2C_SDA_READ()
{
    return SAL_GPIO_Read_Pin(this->sda);
}


/* i2c引脚的delay */
void SAL_I2C::i2c_delay(uint16_t ns)
{
    for (int i = 0; i < 100 * ns; i++);
}

/* i2c引脚产生开始信号 */
void SAL_I2C::i2c_start(void)
{
  i2c_delay(I2C_DELAY);
  
  I2C_SDA_HIGH();
  i2c_delay(I2C_DELAY);
  I2C_SCL_HIGH();
  i2c_delay(I2C_DELAY);
  
  I2C_SDA_LOW();
  i2c_delay(I2C_DELAY);
  
  I2C_SCL_LOW();
}

/* i2c引脚产生停止信号 */
void SAL_I2C::i2c_stop(void)
{
  I2C_SCL_LOW();
  i2c_delay(I2C_DELAY);
  I2C_SDA_LOW();  
  i2c_delay(I2C_DELAY);
  
  I2C_SCL_HIGH();
  i2c_delay(I2C_DELAY);
  
  I2C_SDA_HIGH();
  i2c_delay(I2C_DELAY);
}

/* 等待应答 */
uint8_t SAL_I2C::wait_ack(void)
{
   int timeout = 100*I2C_DELAY;
  I2C_SCL_LOW();
  I2C_SDA_HIGH();  
  
  i2c_delay(I2C_DELAY);
  
  while(timeout)
  {
    if (I2C_SDA_READ() == 0)
    {
      I2C_SCL_HIGH(); 
      
      i2c_delay(I2C_DELAY); 
      
      I2C_SCL_LOW();
      
      return 0;
    }
    
    i2c_delay(I2C_DELAY);
    
    timeout--;
  }  

  I2C_SCL_HIGH(); 
  i2c_delay(I2C_DELAY);      

  I2C_SCL_LOW();
  
  i2c_delay(I2C_DELAY);  
  
  return 1;
}

/* 应答 */
void SAL_I2C::i2c_ack(void)
{
  I2C_SCL_LOW();
  I2C_SDA_LOW();
  i2c_delay(I2C_DELAY);
  
  I2C_SCL_HIGH();
  i2c_delay(I2C_DELAY);
  
  I2C_SCL_LOW();
}

/* 不产生应答 */
void SAL_I2C::i2c_Nack(void)
{
  I2C_SCL_LOW();
  I2C_SDA_HIGH();
  i2c_delay(I2C_DELAY);
  
  I2C_SCL_HIGH();
  i2c_delay(I2C_DELAY);
  
  I2C_SCL_LOW();
}

/* 发送一个字节 */
void SAL_I2C::send(uint8_t data)
{
  uint8_t i = 8;
  
  while (i--)
  {
    I2C_SCL_LOW();
    
    if (data & 0x80)
    {
      I2C_SDA_HIGH();    
    }
    else
    {
      I2C_SDA_LOW();    
    }    
    
    i2c_delay(I2C_DELAY);

    data <<= 1;
    
    I2C_SCL_HIGH();
    i2c_delay(I2C_DELAY);
  }
  
  I2C_SCL_LOW();
  I2C_SDA_HIGH();
}

/* 读取一个字节,ack=1,发送ack,否则发送nack */
uint8_t SAL_I2C::read(uint8_t ack)
{
  uint8_t i = 8;
  uint8_t byte = 0;

  I2C_SDA_HIGH();
  
  while (i--) 
  {
    byte <<= 1;
    
    I2C_SCL_LOW();
    i2c_delay(I2C_DELAY);
    
    I2C_SCL_HIGH();
    i2c_delay(I2C_DELAY);
    
    if (I2C_SDA_READ()) 
    {
      byte |= 0x01;
    }
  }
  
  if(ack==0) i2c_ack();
  else i2c_Nack();
  I2C_SCL_LOW();
  
  return byte;
}

uint8_t SAL_I2C::Write_Byte(uint8_t addr,uint8_t len,uint8_t* buf)
{
    uint8_t i;
    i2c_start();
    send(addr << 1); //发送器件地址
//    if(wait_ack())
//    {
//        i2c_stop();
//        return 1;
//    }
    wait_ack();
    for (i = 0; i < len; i++)
    {
        send(buf[i]);//发送数据
//        if(wait_ack())
//        {
//            i2c_stop();
//            return 1;
//        }
        wait_ack();
    }
    i2c_stop();
    return 0;
}

uint8_t SAL_I2C::Read_Byte(uint8_t addr,uint8_t len,uint8_t* buf)
{
  uint16_t i;
  
  i2c_start();

  send((addr<<1));

  if (wait_ack())
  {
    i2c_stop();
    
    return 1;
  }

  for (i = 0; i < len; i++) 
  {
    
    if (i < (len - 1))
    {
      buf[i] = read(0);
    }
    else
    {
      buf[i] = read(1); 
    }
  }
  
  i2c_stop();
  
  return 0;
}


uint8_t SAL_I2C::Write_Mem_one_Byte(uint8_t addr,uint8_t reg,uint8_t byte)
{
    return this->Write_Mem_Byte(addr,reg,1,&byte);
}

/* i2c连续写,0表示正常,1错误 */
uint8_t SAL_I2C::Write_Mem_Byte(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    uint8_t i;
    i2c_start();
    send(addr << 1); //发送器件地址
//    if(wait_ack())
//    {
//        i2c_stop();
//        return 1;
//    }
    wait_ack();
    send(reg);
//    if(wait_ack())
//    {
//        i2c_stop();
//        return 1;
//    }
    wait_ack();
    for (i = 0; i < len; i++)
    {
        send(buf[i]);//发送数据
//        if(wait_ack())
//        {
//            i2c_stop();
//            return 1;
//        }
        wait_ack();
    }
    i2c_stop();
    return 0;
}

uint8_t SAL_I2C::Read_Mem_one_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t result = 0;
    this->Read_Mem_Byte(addr,reg,1,&result);
    return result;
}

/* 连续读,0表示正常,1错误 */
uint8_t SAL_I2C::Read_Mem_Byte(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    i2c_start();
    send(addr << 1); //发送器件地址
    if (wait_ack())
    {
        i2c_stop();
        return 1;
    }
    send(reg); //发送寄存器地址
    if (wait_ack())
    {
        i2c_stop();
        return 1;
    }
    i2c_start();
    send((addr << 1) | 1);
    if (wait_ack())
    {
        i2c_stop();
        return 1;
    }
    for (int i = 0; i < len; i++) 
    {
        if (i < (len - 1))
            buf[i] = read(0);
        else
            buf[i] = read(1);

    }
    i2c_stop();
    return 0;
}


SAL_I2C SAL_I2C1(PD4, PD5);





