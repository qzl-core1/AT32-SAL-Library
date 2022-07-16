#ifndef __MPU6050_H
#define __MPU6050_H
#include "SAL.h"

class mpu6050
{
    public:
        mpu6050(SAL_I2C* hi2c,uint16_t rate);
        void begin();
        void get_Angle(float *x, float *y);
    private:
        SAL_I2C* i2c;
        uint16_t freq;
        float Kalman_Filter_x(float Accel, float Gyro);
        float Kalman_Filter_y(float Accel, float Gyro);
        void returnTemp(float *Temperature);
        void readGyro(short *gyroData);
        void readAcc(short *accData);
        void set_rate(uint16_t rate);
        void set_lpf(uint16_t lpf);
        
};

#endif
