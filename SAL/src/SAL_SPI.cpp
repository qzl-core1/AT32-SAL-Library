#include "SAL_SPI.h"

SAL_SPI::SAL_SPI(spi_type *spi)
{
    this->spi = spi;
    spi_default_para_init(&spi_init_struct);
    spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;//全双工
    spi_init_struct.master_slave_mode = SPI_MODE_MASTER; //主机
    spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_2;//二分频
    spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;//最高位在前
    spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;//8位数据模式
    spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW;//时钟极性位0
    spi_init_struct.clock_phase = SPI_CLOCK_PHASE_1EDGE;//一个边沿
    spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;//软件片选
}

void SAL_SPI::begin()
{
    spi_type *hspi = this->spi;
    if (hspi == SPI1)
    {
        crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
        SAL_GPIO_Init(PA5, PIN_MUX, PULL_UP); //SCL
        SAL_GPIO_Init(PA6, INPUT, PULL_UP); //MISO
        SAL_GPIO_Init(PA7, PIN_MUX, PULL_UP); //MOSI
    }
    else if (hspi == SPI2)
    {
        crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
        SAL_GPIO_Init(PB13, PIN_MUX, PULL_UP); //SCL
        SAL_GPIO_Init(PB14, PIN_MUX, PULL_UP); //MISO
        SAL_GPIO_Init(PB15, PIN_MUX, PULL_UP); //MOSI
    }
    spi_init(hspi, &spi_init_struct);//初始化寄存器
    spi_enable(hspi, TRUE);
}

void SAL_SPI::begin(SPI_CLOCK_MODE clock_mode,SPI_DATA_FRAME data_frame,DIV_FREQ div_freq)
{
    spi_type *hspi = this->spi;
    if (hspi == SPI1)
    {
        crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
        SAL_GPIO_Init(PA5, PIN_MUX, PULL_UP); //SCL
        SAL_GPIO_Init(PA6, INPUT, PULL_UP); //MISO
        SAL_GPIO_Init(PA7, PIN_MUX, PULL_UP); //MOSI
    }
    else if (hspi == SPI2)
    {
        crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
        SAL_GPIO_Init(PB13, PIN_MUX, PULL_UP); //SCL
        SAL_GPIO_Init(PB14, PIN_MUX, PULL_UP); //MISO
        SAL_GPIO_Init(PB15, PIN_MUX, PULL_UP); //MOSI
    }
    this->set_clock(clock_mode);
    this->set_data_frame(data_frame);
    this->set_div(div_freq);
    spi_init(hspi, &spi_init_struct);//初始化寄存器
    spi_enable(hspi, TRUE);
}


/*
    设置SPI的时钟模式
    SPI_MODE_0,  LOW phase  1 edge
    SPI_MODE_1,  LOW phase  2 edge
    SPI_MODE_2,  HIGH phase  1 edge
    SPI_MODE_3   HIGH phase  2 edge
*/
void SAL_SPI::set_clock(SPI_CLOCK_MODE clock_mode)
{
    spi_clock_polarity_type clock_polarity;
    spi_clock_phase_type clock_phase;
    switch (clock_mode)
    {
    case 0:
        clock_polarity = SPI_CLOCK_POLARITY_LOW;
        clock_phase = SPI_CLOCK_PHASE_1EDGE;
        break;
    case 1:
        clock_polarity = SPI_CLOCK_POLARITY_LOW;
        clock_phase = SPI_CLOCK_PHASE_2EDGE;
        break;
    case 2:
        clock_polarity = SPI_CLOCK_POLARITY_HIGH;
        clock_phase = SPI_CLOCK_PHASE_1EDGE;
        break;
    case 3:
        clock_polarity = SPI_CLOCK_POLARITY_HIGH;
        clock_phase = SPI_CLOCK_PHASE_2EDGE;
        break;
    }
    this->spi_init_struct.clock_phase = clock_phase;
    this->spi_init_struct.clock_polarity = clock_polarity;
}


/* 
    设置SPI的数据格式
    Date_FRAME1,   8bit LSB
    Date_FRAME2,   8bit MSB
    Date_FRAME3,   16bit LSB
    Date_FRAME4,   16bit MSB

*/
void SAL_SPI::set_data_frame(SPI_DATA_FRAME data_frame)
{
    spi_first_bit_type first_bit;
    spi_frame_bit_num_type bit_num;
    switch (data_frame)
    {
    case 0:
        first_bit = SPI_FIRST_BIT_LSB;
        bit_num = SPI_FRAME_8BIT;
        break;
    case 1:
        first_bit = SPI_FIRST_BIT_MSB;
        bit_num = SPI_FRAME_8BIT;
        break;
    case 2:
        first_bit = SPI_FIRST_BIT_LSB;
        bit_num = SPI_FRAME_16BIT;
        break;
    case 3:
        first_bit = SPI_FIRST_BIT_MSB;
        bit_num = SPI_FRAME_16BIT;
        break;
    }
    this->spi_init_struct.first_bit_transmission = first_bit;
    this->spi_init_struct.frame_bit_num = bit_num;
}

/* 设置SPI_SCK分频系数 */
void SAL_SPI::set_div(DIV_FREQ div_freq)
{
    spi_mclk_freq_div_type freq;
    switch (div_freq)
    {
    case DIV_2:
        freq = SPI_MCLK_DIV_2;
        break;
    case DIV_4:
        freq = SPI_MCLK_DIV_4;
        break;
    case DIV_8:
        freq = SPI_MCLK_DIV_8;
        break;
    case DIV_16:
        freq = SPI_MCLK_DIV_16;
        break;
    case DIV_32:
        freq = SPI_MCLK_DIV_32;
        break;
    case DIV_64:
        freq = SPI_MCLK_DIV_64;
        break;
    case DIV_128:
        freq = SPI_MCLK_DIV_128;
        break;
    }
    this->spi_init_struct.mclk_freq_division = freq;
}


/* SPI写入一个字节 */
void SAL_SPI::write(uint16_t data)
{
    /*REST表示发送寄存器非空,等待发送寄存器*/
    while (spi_i2s_flag_get(this->spi, SPI_I2S_TDBE_FLAG) == RESET);
    spi_i2s_data_transmit(this->spi, data);
    /*REST表示寄存器空闲*/
    while (spi_i2s_flag_get(this->spi, SPI_I2S_BF_FLAG) == TRUE);
}


/* SPI连续写入多个字节 */
void SAL_SPI::write(uint8_t *data, uint32_t length)
{
    while (length--)
    {
        this->write(*data++);
    }
    /*REST表示发送寄存器非空,等待发送寄存器*/
    while (spi_i2s_flag_get(this->spi, SPI_I2S_TDBE_FLAG) == RESET);
    /*REST表示寄存器空闲*/
    while (spi_i2s_flag_get(this->spi, SPI_I2S_BF_FLAG) == TRUE);
}

/* 向某个寄存器写入数据 */
void SAL_SPI::write_regist(uint8_t reg, uint8_t data)
{
    this->write(reg);
    this->write(data);
}

/* 向某个寄存器写入多个数据 */
void SAL_SPI::write_regist(uint8_t reg, uint16_t len, uint8_t *data)
{
    this->write(reg);
    this->write(data, len);
}

/* 从某个寄存器读取数据 */
uint8_t SAL_SPI::read(uint8_t reg)
{
    volatile uint16_t vn = spi_i2s_data_receive(this->spi);
    this->write(reg);

    while (spi_i2s_flag_get(this->spi, SPI_I2S_RDBF_FLAG) == RESET);
    vn = spi_i2s_data_receive(this->spi);

    this->write(0xff00);

    while (spi_i2s_flag_get(this->spi, SPI_I2S_RDBF_FLAG) == RESET);
    vn = spi_i2s_data_receive(this->spi);

    return (uint8_t)vn;
}

/* 从某个寄存器中读取多个数据 */
void SAL_SPI::read(uint8_t reg, uint16_t len, uint8_t *data)
{
    volatile uint16_t vn = spi_i2s_data_receive(this->spi);//直接读,目前还没有还没有问题
    this->write(reg);//发送寄存器地址

    while (spi_i2s_flag_get(this->spi, SPI_I2S_RDBF_FLAG) == RESET);//等待rdbf置位
    vn = spi_i2s_data_receive(this->spi);//这是无用数据,不知道原因

    for(int i = 0; i < len ; i++)
    {
        while(spi_i2s_flag_get(this->spi, SPI_I2S_TDBE_FLAG) == RESET);
        spi_i2s_data_transmit(this->spi, 0xff00);//引导scl时钟产生
        while(spi_i2s_flag_get(this->spi, SPI_I2S_RDBF_FLAG) == RESET); //等待接收为满
        vn = (uint8_t)spi_i2s_data_receive(this->spi); //接收
        data[i] = vn;
    }
}

SAL_SPI SPI(SPI1);
SAL_SPI SPI_2(SPI2);





