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