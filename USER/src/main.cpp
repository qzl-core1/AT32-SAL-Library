#include "SAL.h"
#include "mpu6050.h"
#include "icm20602.h"
#include "mt6816.h"

icm20602 icm(&SPI_2,PB12,200);

float x,y,z;

void test()
{
    icm.get_Angle(&x,&y,&z);
}

int main()
{
    SAL_Init();
    SAL_USART1.begin(115200);
    SPI_2.begin();
    icm.begin();
    SAL_Timer_Init(TIMER4,test,23999,49,0,3);
//    __pwm_init(PA2,23999,49);
//    __pwm_write(PA15,25);
    while (1)
    {
        SAL_USART1.printf("ang:%.2f,%.2f,%.2f\n",x,y,z);
    }
}
