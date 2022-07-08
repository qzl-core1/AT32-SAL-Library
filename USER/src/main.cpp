#include "SAL.h"
#include "mpu6050.h"
#include "ICM20602.h"
float x, y;
ICM20602 icm(&SPI_2,PD9,500);

void clkout_config(void)
{
   crm_clocks_freq_type crm_clocks_freq_struct;
    /*获取系统时钟*/
  crm_clocks_freq_get(&crm_clocks_freq_struct);
  /*是能timer1的时钟*/
  crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);

  /* systemclock/24000/10= 500hz,freq = sysfrq/((div+1)*(pr+1))*/
  tmr_base_init(TMR1, 4, (crm_clocks_freq_struct.ahb_freq / 10000) - 1);
  /*设置计数模式*/
  tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);

  /*溢出中断是能*/
  tmr_interrupt_enable(TMR1, TMR_OVF_INT, TRUE);

  /* 中断分组 */
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 0, 0);

  /*开始计数*/
  tmr_counter_enable(TMR1, TRUE);
}

int main()
{
    SAL_Init();
    SAL_USART1.begin(115200);
    SPI_2.begin(SPI_MODE_0,Date_FRAME2,DIV_128);
    icm.begin();
    clkout_config();
    while (1)
    {
        SAL_USART1.printf("ang:%.3f,%.3f\n",x,y);
//        SAL_USART1.printf("gyro:%.1f,%.1f,%.1f\n",icm.gyro_x,icm.gyro_y,icm.gyro_z);
    }
}
extern "C" {
void TMR1_OVF_TMR10_IRQHandler(void)
{
  if(tmr_flag_get(TMR1, TMR_OVF_FLAG) != RESET)
  {
    icm.get_Angle(&x,&y);
    tmr_flag_clear(TMR1, TMR_OVF_FLAG);
  }
}
}
