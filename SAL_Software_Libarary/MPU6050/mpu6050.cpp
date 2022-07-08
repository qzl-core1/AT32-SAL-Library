#include "mpu6050.h"


#define MPU6050_ADDR                0x68   //设备地址
#define MPU6050_RA_SMPLRT_DIV       0x19
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C

#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_PWR_MGMT_2       0x6C

#define MPU_INT_EN_REG              0x38     //中断使能寄存器

#define MPU6050_WHO_AM_I            0x75     //MPU6050标识寄存器
#define MPU6050_GYRO_OUT            0x43     //MPU6050陀螺仪数据寄存器地址
#define MPU6050_ACC_OUT             0x3B     //MPU6050加速度数据寄存器地址

#define MPU6050_RA_TEMP_OUT_H       0x41     //温度输出高位寄存器

MPU6050::MPU6050(SAL_I2C *hi2c, uint16_t rate)
{
    this->i2c = hi2c;
    this->freq = rate;
}
/* x轴卡尔曼滤波 */
float MPU6050::Kalman_Filter_x(float Accel, float Gyro)
{
//    static float angle_dot;
    static float angle;
    float dt = 1.0f / ((float)this->freq);   //每xms进行一次滤波
    float Q_angle = 0.001; // 过程噪声的协方差
    float Q_gyro = 0.003; //0.003 过程噪声的协方差 过程噪声的协方差为一个一行两列矩阵
    float R_angle = 0.5;    // 测量噪声的协方差 既测量偏差
    char  C_0 = 1;
    static float Q_bias, Angle_err;
    static float PCt_0, PCt_1, E;
    static float K_0, K_1, t_0, t_1;
    static float Pdot[4] = {0, 0, 0, 0};
    static float PP[2][2] = { { 1, 0 }, { 0, 1 } };
    angle += (Gyro - Q_bias) * dt; //先验估计
    Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

    Pdot[1] = -PP[1][1];
    Pdot[2] = -PP[1][1];
    Pdot[3] = Q_gyro;
    PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
    PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
    PP[1][0] += Pdot[2] * dt;
    PP[1][1] += Pdot[3] * dt;

    Angle_err = Accel - angle;  //zk-先验估计

    PCt_0 = C_0 * PP[0][0];
    PCt_1 = C_0 * PP[1][0];

    E = R_angle + C_0 * PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = C_0 * PP[0][1];

    PP[0][0] -= K_0 * t_0;       //后验估计误差协方差
    PP[0][1] -= K_0 * t_1;
    PP[1][0] -= K_1 * t_0;
    PP[1][1] -= K_1 * t_1;

    angle   += K_0 * Angle_err;  //后验估计
    Q_bias  += K_1 * Angle_err;  //后验估计
//    angle_dot   = Gyro - Q_bias;     //输出值(后验估计)的微分=角速度
    return angle;
}

/* y轴卡尔曼滤波 */
float MPU6050::Kalman_Filter_y(float Accel, float Gyro)
{
//    static float angle_dot;
    static float angle;
    float dt = 1.0f / ((float)this->freq);   //每5ms进行一次滤波
    float Q_angle = 0.001; // 过程噪声的协方差
    float Q_gyro = 0.003; //0.003 过程噪声的协方差 过程噪声的协方差为一个一行两列矩阵
    float R_angle = 0.5;    // 测量噪声的协方差 既测量偏差
    char  C_0 = 1;
    static float Q_bias, Angle_err;
    static float PCt_0, PCt_1, E;
    static float K_0, K_1, t_0, t_1;
    static float Pdot[4] = {0, 0, 0, 0};
    static float PP[2][2] = { { 1, 0 }, { 0, 1 } };
    angle += (Gyro - Q_bias) * dt; //先验估计
    Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
    Pdot[1] = -PP[1][1];
    Pdot[2] = -PP[1][1];
    Pdot[3] = Q_gyro;
    PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
    PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
    PP[1][0] += Pdot[2] * dt;
    PP[1][1] += Pdot[3] * dt;
    Angle_err = Accel - angle;  //zk-先验估计

    PCt_0 = C_0 * PP[0][0];
    PCt_1 = C_0 * PP[1][0];

    E = R_angle + C_0 * PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = C_0 * PP[0][1];

    PP[0][0] -= K_0 * t_0;       //后验估计误差协方差
    PP[0][1] -= K_0 * t_1;
    PP[1][0] -= K_1 * t_0;
    PP[1][1] -= K_1 * t_1;

    angle   += K_0 * Angle_err;    //后验估计
    Q_bias  += K_1 * Angle_err;  //后验估计
//    angle_dot   = Gyro - Q_bias;    //输出值(后验估计)的微分=角速度
    return angle;
}

/* 返回温度 */
void MPU6050::returnTemp(float *Temperature)
{
    short temp3;
    uint8_t buf[2];
    SAL_I2C1.Read_Mem_Byte(MPU6050_ADDR, MPU6050_RA_TEMP_OUT_H, 2, buf);
    temp3 = (buf[0] << 8) | buf[1];
    *Temperature = ((double) temp3 / 340.0) + 36.53;
}

/* 读取角速度 */
void MPU6050::readGyro(short *gyroData)
{
    uint8_t buf[6];
    SAL_I2C1.Read_Mem_Byte(MPU6050_ADDR, MPU6050_GYRO_OUT, 6, buf);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}


/* 读取加速度 */
void MPU6050::readAcc(short *accData)
{
    uint8_t buf[6];
    SAL_I2C1.Read_Mem_Byte(MPU6050_ADDR, MPU6050_ACC_OUT, 6, buf);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}


/* 获取角度 */
void MPU6050::get_Angle(float *x, float *y)
{
    float Accel_Y, Accel_Z, Accel_X, Accel_Angle_x, Accel_Angle_y, Gyro_X, Gyro_Z, Gyro_Y;
    float Temperature;
    short gyroData[3];
    short accData[3];
    returnTemp(&Temperature);
    readGyro(gyroData);
    readAcc(accData);
    Gyro_X = (float)gyroData[0];
    Gyro_Y = (float)gyroData[1];
    Gyro_Z = (float)gyroData[2];
    Accel_X = (float)accData[0];
    Accel_Y = (float)accData[1];
    Accel_Z = (float)accData[2];
    if (Gyro_X > 32768)  Gyro_X -= 65536;            //数据类型转换  也可通过short强制类型转换
    if (Gyro_Y > 32768)  Gyro_Y -= 65536;            //数据类型转换  也可通过short强制类型转换
    if (Gyro_Z > 32768)  Gyro_Z -= 65536;            //数据类型转换
    if (Accel_X > 32768) Accel_X -= 65536;           //数据类型转换
    if (Accel_Y > 32768) Accel_Y -= 65536;           //数据类型转换
    if (Accel_Z > 32768) Accel_Z -= 65536;           //数据类型转换
    Accel_Angle_x = atan2(Accel_Y, Accel_Z) * 180.0f / PI; //计算倾角，转换单位为度
    Accel_Angle_y = atan2(Accel_X, Accel_Z) * 180.0f / PI; //计算倾角，转换单位为度
    Gyro_X = Gyro_X / 16.4f;                          //陀螺仪量程转换，量程±2000°/s对应灵敏度16.4，可查手册
    Gyro_Y = Gyro_Y / 16.4f;                          //陀螺仪量程转换
    *x = -Kalman_Filter_x(Accel_Angle_x, Gyro_X); //卡尔曼滤波
    *y = -Kalman_Filter_y(Accel_Angle_y, Gyro_Y);//更新平衡倾角
}

void MPU6050::set_lpf(uint16_t lpf)
{
    uint8_t data = 0;
    if (lpf >= 188)data = 1;
    else if (lpf >= 98)data = 2;
    else if (lpf >= 42)data = 3;
    else if (lpf >= 20)data = 4;
    else if (lpf >= 10)data = 5;
    else data = 6;
    (this->i2c)->Write_Mem_one_Byte(MPU6050_ADDR, MPU6050_RA_CONFIG, data);
}

void MPU6050::set_rate(uint16_t rate)
{
    uint8_t data;
    if (rate > 1000)rate = 1000;
    if (rate < 4)rate = 4;
    data = 1000 / rate - 1;
    (this->i2c)->Write_Mem_one_Byte(MPU6050_ADDR, MPU6050_RA_SMPLRT_DIV, data); //值得设置,设置频率
    this->set_lpf(data / 2);
}

void MPU6050::begin()
{
    int i = 0, j = 0;
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 1000; j++);
    }
    (this->i2c)->Write_Mem_one_Byte(MPU6050_ADDR, MPU6050_RA_PWR_MGMT_1, 0x01);
     this->set_rate(freq);
    (this->i2c)->Write_Mem_one_Byte(MPU6050_ADDR, MPU_INT_EN_REG, 0x01);//中断使能
    (this->i2c)->Write_Mem_one_Byte(MPU6050_ADDR, MPU6050_RA_ACCEL_CONFIG, 0x00); //加速度设置
    (this->i2c)->Write_Mem_one_Byte(MPU6050_ADDR, MPU6050_RA_GYRO_CONFIG, 0x18);  //陀螺仪设置
}
