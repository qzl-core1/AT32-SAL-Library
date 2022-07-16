# AT32-SAL-Library

​	为了降低AT32的学习难度,同时基于AT32的V2的库,提供基础像GPIO,SPI,I2C,TIME,USART这类通用外设的支持,创建出SAL库,并且努力给出对应的软件框架库

### 文件结构目录

- BSP:AT32对应的标准库
- Core:内核支持文件和DSP文件
- MDK:工程文件目录
- USER:main.c,中断和文件和时钟文件
- SAL:
  - SAL.c:用配置全局文件的头文件,有全局公用的时钟启动和延迟函数
  - src:SAL对上层软件架构统一的驱动源文件

### 2022/6/16

- 完成全局延迟函数设置
- 初步构建SAL_GPIO模块
  - SAL_GPIO_Init:初始化某个GPIO引脚
  - SAL_GPIO_Write_Pin:输出某个管脚的电平
  - SAL_GPIO_Read_Pin:读取某个管脚的电平

### 2022/6/19

- 完成SAL_USART模块,默认使用串口1-串口3
  - begin:初始化USART
  - stop:失能USART
  - attachInterrupt:绑定中断回调函数
  - hasNext:获得缓冲区剩余的空间
  - read:从缓冲区读入一个字符
  - write:向串口写入一个字符
  - printf:使用串口的printf

- 初步构建SAL_I2C模块

### 2022/6/20

- 初步完成i2c的启动,接收

### 2022/7/7

- 使用软件I2C库已经完成
- 完成硬件SPI
- 添加上层软件库
  - MPU6050:使用卡尔曼滤波
  - ICM20602:使用卡尔曼滤波

- 加入外部中断配置

#### 开始做出调整

- 为了加强SAL的移植性,开始做出隔离层,隔离层存在的意义在于对接底层代码和向上支持SAL库的库函数这样使得SAL的库函数只用直接依赖于隔离层.

### 2022/7/11

- 修复BUG
  - 修复MPU6050驱动库中应用i2c地址默认为SAL_I2C1

### 2022/7/13

- 软件库增加成员:
  - MT6816:14 bit 磁编码器,使用硬件spi

- SAL标准软件库中的规范
  - 所有文件中的英文必须小写
  - 必须以类为基础
  - 类名必须也是小写
  - 带有begin接口,用于开启引脚

### 2022、7、16

- 修改文件目录结构

  - Core:存放底层标准库,CMSIS的文件夹
  - MDK-ARM:用于存放启动文件和MDK编译日志文件
  - SAL:
    - SAL_Driver_Libarary：存放和软件层对接的文件
    - SAL_Middleware:存放底层接口,对接给Driver层

  - SAL_Software_Library:存放SAL支持的软件
  - USER:main.cpp和各种中断

- SAL_Middleware:
  - gpio.c:存放引脚初始化,引脚map数组
  - delay.c:存放全局延迟函数
  - exint.c:存放外部中断的相关函数
  - pwm.c:存放pwm输出的函数
  - timer.c:存放定时器初始化的相关函数

- 文件依赖关系:
  - pwm.c和timer.c还要exint.c都需要依赖gpio.c
  - SAL_Driver层中SAL_SPI和SAL_USART都直接依赖底层库函数，目前还没有找到很好的解耦方式
  - SAL.c依赖所有的SAL_Middleware文件

- 全局中断分组统一为 0-3 的抢占优先级, 0 - 3 的响应优先级