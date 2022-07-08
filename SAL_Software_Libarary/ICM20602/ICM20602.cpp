#include "ICM20602.h"
#define ICM20602_DEV_ADDR           (0x69)                                      // SA0�ӵأ�0x68 SA0������0x69 ģ��Ĭ������
#define ICM20602_SPI_W              (0x00)
#define ICM20602_SPI_R              (0x80)

#define ICM20602_XG_OFFS_TC_H       (0x04)
#define ICM20602_XG_OFFS_TC_L       (0x05)
#define ICM20602_YG_OFFS_TC_H       (0x07)
#define ICM20602_YG_OFFS_TC_L       (0x08)
#define ICM20602_ZG_OFFS_TC_H       (0x0A)
#define ICM20602_ZG_OFFS_TC_L       (0x0B)
#define ICM20602_SELF_TEST_X_ACCEL  (0x0D)
#define ICM20602_SELF_TEST_Y_ACCEL  (0x0E)
#define ICM20602_SELF_TEST_Z_ACCEL  (0x0F)
#define ICM20602_XG_OFFS_USRH       (0x13)
#define ICM20602_XG_OFFS_USRL       (0x14)
#define ICM20602_YG_OFFS_USRH       (0x15)
#define ICM20602_YG_OFFS_USRL       (0x16)
#define ICM20602_ZG_OFFS_USRH       (0x17)
#define ICM20602_ZG_OFFS_USRL       (0x18)
#define ICM20602_SMPLRT_DIV         (0x19)
#define ICM20602_CONFIG             (0x1A)
#define ICM20602_GYRO_CONFIG        (0x1B)
#define ICM20602_ACCEL_CONFIG       (0x1C)
#define ICM20602_ACCEL_CONFIG_2     (0x1D)
#define ICM20602_LP_MODE_CFG        (0x1E)
#define ICM20602_ACCEL_WOM_X_THR    (0x20)
#define ICM20602_ACCEL_WOM_Y_THR    (0x21)
#define ICM20602_ACCEL_WOM_Z_THR    (0x22)
#define ICM20602_FIFO_EN            (0x23)
#define ICM20602_FSYNC_INT          (0x36)
#define ICM20602_INT_PIN_CFG        (0x37)
#define ICM20602_INT_ENABLE         (0x38)
#define ICM20602_FIFO_WM_INT_STATUS (0x39)
#define ICM20602_INT_STATUS         (0x3A)
#define ICM20602_ACCEL_XOUT_H       (0x3B)
#define ICM20602_ACCEL_XOUT_L       (0x3C)
#define ICM20602_ACCEL_YOUT_H       (0x3D)
#define ICM20602_ACCEL_YOUT_L       (0x3E)
#define ICM20602_ACCEL_ZOUT_H       (0x3F)
#define ICM20602_ACCEL_ZOUT_L       (0x40)
#define ICM20602_TEMP_OUT_H         (0x41)
#define ICM20602_TEMP_OUT_L         (0x42)
#define ICM20602_GYRO_XOUT_H        (0x43)
#define ICM20602_GYRO_XOUT_L        (0x44)
#define ICM20602_GYRO_YOUT_H        (0x45)
#define ICM20602_GYRO_YOUT_L        (0x46)
#define ICM20602_GYRO_ZOUT_H        (0x47)
#define ICM20602_GYRO_ZOUT_L        (0x48)
#define ICM20602_SELF_TEST_X_GYRO   (0x50)
#define ICM20602_SELF_TEST_Y_GYRO   (0x51)
#define ICM20602_SELF_TEST_Z_GYRO   (0x52)
#define ICM20602_FIFO_WM_TH1        (0x60)
#define ICM20602_FIFO_WM_TH2        (0x61)
#define ICM20602_SIGNAL_PATH_RESET  (0x68)
#define ICM20602_ACCEL_INTEL_CTRL   (0x69)
#define ICM20602_USER_CTRL          (0x6A)
#define ICM20602_PWR_MGMT_1         (0x6B)
#define ICM20602_PWR_MGMT_2         (0x6C)
#define ICM20602_I2C_IF             (0x70)
#define ICM20602_FIFO_COUNTH        (0x72)
#define ICM20602_FIFO_COUNTL        (0x73)
#define ICM20602_FIFO_R_W           (0x74)
#define ICM20602_WHO_AM_I           (0x75)
#define ICM20602_XA_OFFSET_H        (0x77)
#define ICM20602_XA_OFFSET_L        (0x78)
#define ICM20602_YA_OFFSET_H        (0x7A)
#define ICM20602_YA_OFFSET_L        (0x7B)
#define ICM20602_ZA_OFFSET_H        (0x7D)
#define ICM20602_ZA_OFFSET_L        (0x7E)

ICM20602::ICM20602(SAL_SPI* hspi,Pin_TypeDef pin,int16_t set_freq)
{
    spi = hspi;
    cs = pin;
    freq = set_freq;
}

void ICM20602::begin()
{
    /* ��ʼ��Ƭѡ */
    SAL_GPIO_Init(this->cs,OUTPUT,PULL_UP);
    /* ��ʼ������ */ 
    if(this->icm20602_init()==0)
    {
        SAL_USART1.printf("ICM20602 init successfully!\r\n");
    }
    icm20602_get_offset();
}

uint8_t ICM20602::icm20602_read_register(uint8_t reg)
{
    uint8_t data = 0;
    SAL_GPIO_Write_Pin(cs, 0);
    data = spi->read(reg | ICM20602_SPI_R);
    SAL_GPIO_Write_Pin(cs, 1);
    return data;
}

void ICM20602::icm20602_read_registers(uint8_t reg, uint8_t *data, uint32_t len)
{
    SAL_GPIO_Write_Pin(cs, 0);
    spi->read(reg | ICM20602_SPI_R, len, data);
    SAL_GPIO_Write_Pin(cs, 1);
}

void ICM20602::icm20602_write_register(uint8_t reg, uint8_t data)
{
    SAL_GPIO_Write_Pin(cs, 0);
    spi->write_regist(reg | ICM20602_SPI_W, data);
    SAL_GPIO_Write_Pin(cs, 1);
}

uint8_t ICM20602::icm20602_self_check(void)
{
    uint8_t dat = 0, return_state = 0;
    uint8_t timeout_count = 0;

    while (0x12 != dat) // �ж� ID �Ƿ���ȷ
    {
        if (timeout_count ++ > 250)
        {
            return_state =  1;
            SAL_USART1.printf("ID read error\r\n", dat);

            break;
        }
        dat = icm20602_read_register(ICM20602_WHO_AM_I);
        SAL_Delay(10);
    }
    return return_state;
}

uint8_t ICM20602::icm20602_init(void)
{
    uint8_t val = 0x0, return_state = 0;
    uint16_t timeout_count = 0;

    do
    {
        if (icm20602_self_check())
        {
            // ��ô���� ICM20602 �Լ������ʱ�˳���
            // ���һ�½�����û������ ���û������ܾ��ǻ���
            return_state = 1;
            break;
        }

        icm20602_write_register(ICM20602_PWR_MGMT_1, 0x80);                     // ��λ�豸
        SAL_Delay(2);

        do                                                                      // �ȴ���λ�ɹ�
        {
            val = icm20602_read_register(ICM20602_PWR_MGMT_1);
            if (timeout_count ++ > 250)
            {
                // �������������˶�����Ϣ ������ʾ����λ��������
                // ��ô���� ICM20602 �Լ������ʱ�˳���
                // ���һ�½�����û������ ���û������ܾ��ǻ���
                SAL_USART1.printf("icm20602 reset error\r\n");
                return_state = 1;
                break;
            }
        }
        while (0x41 != val);
        if (1 == return_state)
            break;
        icm20602_write_register(ICM20602_INT_ENABLE,0x00);   //�ر��ж�ʹ��,������
        icm20602_write_register(ICM20602_FIFO_EN,0x00);   //�ر�FIFO
        icm20602_write_register(ICM20602_INT_PIN_CFG, 0x80);     // ����INT����Ϊ�͵�ƽ��Ч����©���
        icm20602_write_register(ICM20602_PWR_MGMT_1,     0x01);                 // ʱ������
        icm20602_write_register(ICM20602_PWR_MGMT_2,     0x00);                 // ���������Ǻͼ��ٶȼ�
        icm20602_write_register(ICM20602_CONFIG,         0x01);                 // 176HZ 1KHZ
        icm20602_write_register(ICM20602_SMPLRT_DIV,     0x07);                 // �������� SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
        icm20602_write_register(ICM20602_GYRO_CONFIG,    0x18);                 // ��2000 dps
        icm20602_write_register(ICM20602_ACCEL_CONFIG,   0x10);                 // ��8g
        icm20602_write_register(ICM20602_ACCEL_CONFIG_2, 0x03);                 // Average 4 samples   44.8HZ   //0x23 Average 16 samples
        // ICM20602_GYRO_CONFIG�Ĵ���
        // ����Ϊ:0x00 ����������Ϊ:��250 dps     ��ȡ�������������ݳ���131           ����ת��Ϊ������λ�����ݣ���λΪ����/s
        // ����Ϊ:0x08 ����������Ϊ:��500 dps     ��ȡ�������������ݳ���65.5          ����ת��Ϊ������λ�����ݣ���λΪ����/s
        // ����Ϊ:0x10 ����������Ϊ:��1000dps     ��ȡ�������������ݳ���32.8          ����ת��Ϊ������λ�����ݣ���λΪ����/s
        // ����Ϊ:0x18 ����������Ϊ:��2000dps     ��ȡ�������������ݳ���16.4          ����ת��Ϊ������λ�����ݣ���λΪ����/s

        // ICM20602_ACCEL_CONFIG�Ĵ���
        // ����Ϊ:0x00 ���ٶȼ�����Ϊ:��2g          ��ȡ���ļ��ٶȼ����� ����16384      ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        // ����Ϊ:0x08 ���ٶȼ�����Ϊ:��4g          ��ȡ���ļ��ٶȼ����� ����8192       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        // ����Ϊ:0x10 ���ٶȼ�����Ϊ:��8g          ��ȡ���ļ��ٶȼ����� ����4096       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        // ����Ϊ:0x18 ���ٶȼ�����Ϊ:��16g         ��ȡ���ļ��ٶȼ����� ����2048       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
    }
    while (0);
    return return_state;
}

/* ��ȡ��Ư */
void ICM20602::icm20602_get_offset(void)
{
    this->gyro_offset_x = 0;
    this->gyro_offset_y = 0;
    this->gyro_offset_z = 0;
    for(int i =0 ; i < 100 ; i++)
    {
        icm20602_get_gyro();
        this->gyro_offset_x += icm_gyro_x;
        this->gyro_offset_y += icm_gyro_y;
        this->gyro_offset_z += icm_gyro_z;
        SAL_Delay(5);
    }
    gyro_offset_x /= 100;
    gyro_offset_y /= 100;
    gyro_offset_z /= 100;
}

/* ��ȡ���ٶ� */
void ICM20602::icm20602_get_acc(void)
{
    uint8_t dat[6];

    icm20602_read_registers(ICM20602_ACCEL_XOUT_H, dat, 6);
    icm_acc_x = (int16_t)(((uint16_t)dat[0] << 8 | dat[1]));
    icm_acc_y = (int16_t)(((uint16_t)dat[2] << 8 | dat[3]));
    icm_acc_z = (int16_t)(((uint16_t)dat[4] << 8 | dat[5]));
    acc_x = (float)(icm_acc_x-gyro_offset_x) / 2048.0f;
    acc_y = (float)(icm_acc_y-gyro_offset_y)/ 2048.0f;
    acc_z = (float)(icm_acc_z-gyro_offset_z) / 2048.0f;
    if (acc_x > 32768)  acc_x -= 65536;            //��������ת��  Ҳ��ͨ��shortǿ������ת��
    if (acc_y > 32768)  acc_y -= 65536;            //��������ת��  Ҳ��ͨ��shortǿ������ת��
    if (acc_z > 32768)  acc_z -= 65536;            //��������ת��
}

/* ��ȡ������ */
void ICM20602::icm20602_get_gyro(void)
{
    uint8_t dat[6];

    icm20602_read_registers(ICM20602_GYRO_XOUT_H, dat, 6);
    icm_gyro_x = (int16_t)(((uint16_t)dat[0] << 8 | dat[1]));
    icm_gyro_y = (int16_t)(((uint16_t)dat[2] << 8 | dat[3]));
    icm_gyro_z = (int16_t)(((uint16_t)dat[4] << 8 | dat[5]));
    gyro_x = (float)icm_gyro_x;
    gyro_y = (float)icm_gyro_y;
    gyro_z = (float)icm_gyro_z;
    gyro_x /= 16.4f;
    gyro_y /= 16.4f;
    gyro_z /= 16.4f;
    if (gyro_x > 32768)  gyro_x -= 65536;            //��������ת��  Ҳ��ͨ��shortǿ������ת��
    if (gyro_y > 32768)  gyro_y -= 65536;            //��������ת��  Ҳ��ͨ��shortǿ������ת��
    if (gyro_z > 32768)  gyro_z -= 65536;            //��������ת��
}

/* x�Ῠ�����˲� */
float ICM20602::Kalman_Filter_x(float Accel, float Gyro)
{
//    static float angle_dot;
    static float angle;
    float dt = 1.0f / ((float)this->freq);   //ÿxms����һ���˲�
    float Q_angle = 0.001; // ����������Э����
    float Q_gyro = 0.003; //0.003 ����������Э���� ����������Э����Ϊһ��һ�����о���
    float R_angle = 0.5;    // ����������Э���� �Ȳ���ƫ��
    char  C_0 = 1;
    static float Q_bias, Angle_err;
    static float PCt_0, PCt_1, E;
    static float K_0, K_1, t_0, t_1;
    static float Pdot[4] = {0, 0, 0, 0};
    static float PP[2][2] = { { 1, 0 }, { 0, 1 } };
    angle += (Gyro - Q_bias) * dt; //�������
    Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��

    Pdot[1] = -PP[1][1];
    Pdot[2] = -PP[1][1];
    Pdot[3] = Q_gyro;
    PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
    PP[0][1] += Pdot[1] * dt;   // =����������Э����
    PP[1][0] += Pdot[2] * dt;
    PP[1][1] += Pdot[3] * dt;

    Angle_err = Accel - angle;  //zk-�������

    PCt_0 = C_0 * PP[0][0];
    PCt_1 = C_0 * PP[1][0];

    E = R_angle + C_0 * PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = C_0 * PP[0][1];

    PP[0][0] -= K_0 * t_0;       //����������Э����
    PP[0][1] -= K_0 * t_1;
    PP[1][0] -= K_1 * t_0;
    PP[1][1] -= K_1 * t_1;

    angle   += K_0 * Angle_err;  //�������
    Q_bias  += K_1 * Angle_err;  //�������
//    angle_dot   = Gyro - Q_bias;     //���ֵ(�������)��΢��=���ٶ�
    return angle;
}

float ICM20602::Kalman_Filter_y(float Accel, float Gyro)
{
//    static float angle_dot;
    static float angle;
    float dt = 1.0f / ((float)this->freq);   //ÿ5ms����һ���˲�
    float Q_angle = 0.001; // ����������Э����
    float Q_gyro = 0.003; //0.003 ����������Э���� ����������Э����Ϊһ��һ�����о���
    float R_angle = 0.5;    // ����������Э���� �Ȳ���ƫ��
    char  C_0 = 1;
    static float Q_bias, Angle_err;
    static float PCt_0, PCt_1, E;
    static float K_0, K_1, t_0, t_1;
    static float Pdot[4] = {0, 0, 0, 0};
    static float PP[2][2] = { { 1, 0 }, { 0, 1 } };
    angle += (Gyro - Q_bias) * dt; //�������
    Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��
    Pdot[1] = -PP[1][1];
    Pdot[2] = -PP[1][1];
    Pdot[3] = Q_gyro;
    PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
    PP[0][1] += Pdot[1] * dt;   // =����������Э����
    PP[1][0] += Pdot[2] * dt;
    PP[1][1] += Pdot[3] * dt;
    Angle_err = Accel - angle;  //zk-�������

    PCt_0 = C_0 * PP[0][0];
    PCt_1 = C_0 * PP[1][0];

    E = R_angle + C_0 * PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = C_0 * PP[0][1];

    PP[0][0] -= K_0 * t_0;       //����������Э����
    PP[0][1] -= K_0 * t_1;
    PP[1][0] -= K_1 * t_0;
    PP[1][1] -= K_1 * t_1;

    angle   += K_0 * Angle_err;    //�������
    Q_bias  += K_1 * Angle_err;  //�������
//    angle_dot   = Gyro - Q_bias;    //���ֵ(�������)��΢��=���ٶ�
    return angle;
}

void ICM20602::get_Angle(float *x, float *y)
{
    icm20602_get_acc();
    icm20602_get_gyro();
    Accel_Angle_x = atan2(acc_y, acc_z) * 180.0f / PI;
    Accel_Angle_y = atan2(acc_x, acc_z) * 180.0f / PI;
    *x = Kalman_Filter_x(Accel_Angle_x,gyro_x);
    *y = Kalman_Filter_y(Accel_Angle_y,gyro_y);
}

