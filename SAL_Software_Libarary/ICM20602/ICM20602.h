#ifndef __ICM20602_H
#define __ICM20602_H
#include "SAL.h"
class icm20602
{
    public:
        icm20602(SAL_SPI* hspi,Pin_TypeDef pin,int16_t set_freq);
        void begin();
        void get_Angle(float *x, float *y);
        void get_Angle(float *x, float *y, float *z);
    private:
        SAL_SPI* spi;
        Pin_TypeDef cs;
        uint8_t icm20602_read_register(uint8_t reg);
        void icm20602_read_registers(uint8_t reg, uint8_t *data, uint32_t len);
        void icm20602_write_register(uint8_t reg, uint8_t data);
        uint8_t icm20602_self_check(void);
        uint8_t icm20602_init(void);
        void icm20602_get_acc(void);
        void icm20602_get_gyro(void);
        void icm20602_get_offset(void);
        float Kalman_Filter_x(float Accel, float Gyro);
        float Kalman_Filter_y(float Accel, float Gyro);
        float Kalman_Filter_z(float Accel, float Gyro);
        int16_t freq;
        int16_t icm_gyro_x , icm_gyro_y , icm_gyro_z , gyro_offset_x, gyro_offset_y , gyro_offset_z;// 三轴陀螺仪数据      gyro (陀螺仪)
        int16_t icm_acc_x , icm_acc_y , icm_acc_z;// 三轴加速度计数据    acc (accelerometer 加速度计)
        float acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z, Accel_Angle_y, Accel_Angle_x,Accel_Angle_z;
        
};

#endif

