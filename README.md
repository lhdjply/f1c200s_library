# 项目简介

该项目是为全志F1C100S/F1C200S所编写的库函数，编写风格模仿STM32标准库，使得从STM32过来的人更容易上手。项目已经移植了 `cherryusb`、`fatfs`、`lvgl`、`rt-thread`。

# 准备工作

## 操作系统

windows、linux

## 编辑环境

推荐使用的编辑环境为**VSCode**([下载地址链接](https://code.visualstudio.com/))，是一个运行于MacOS X、Windows和Linux之上的，针对于编写现代Web和云应用的跨平台源代码编辑器；VSCode免费而且功能强大，对JavaScript和NodeJS的支持非常好，自带很多功能，例如代码格式化，代码智能提示补全、Emmet插件等。

### VSCode推荐插件

* **C/C++**：编写C/C++必需的插件。

* **Chinese (Simplified) (简体中文) Language Pack for Visual Studio Code**：VSCode中文插件。

* **Git Graph**：可图形化查看git历史文件。

* **vscode-pdf**：可在VSCode中直接浏览PDF文件。

* **vscode-yarkdown**：可进行浏览以及编辑markdown文件。

* **Task Buttons**：可在vscode下方直接生成任务按钮，方便操作。

## 编译器

该项目编译器为**arm-none-eabi-gcc**([下载地址链接](https://developer.arm.com/downloads/-/gnu-rm))

linux平台可直接通过终端下载

```shell
sudo apt-get update
sudo apt-get install gcc-arm-none-eabi
```

# 编译与下载

## 编译

在VSCode的菜单栏中依次点击 `终端-运行任务-编译`。如果有安装插件`Task Buttons`，可在VSCode下方直接点击编译。

## 重新编译

在VSCode的菜单栏中依次点击 `终端-运行任务-重新编译`。如果有安装插件`Task Buttons`，可在VSCode下方直接点击重新编译。

## 下载

下载前，需将板子进入**FEL**模式，然后在VSCode的菜单栏中依次点击 `终端-运行任务-下载`。如果有安装插件`Task Buttons`，可在VSCode下方直接点击下载。

**注意：** linux需要安装libusb

```shell
sudo apt-get update
sudo apt install pkg-config libusb-1.0-0-dev zlib1g-dev binutils libfdt-dev 
```

# 文件夹介绍

|文件夹|简介|
|-|-|
|.gitee|gitee平台issue和pr模板|
|.github|github平台issue和pr模板，以及ci检查|
|.vscode|VSCode配置文件|
|bootloader|bootloader文件|
|dsp|dsp库（例如`arm_mean_f32`)|
|f1cx00s_lib|模仿**stm32**风格写的库函数|
|hardware|外设初始化|
|myresoure|界面左边为lvgl官方例子，界面右边为库函数测试例子。其中库函数例子外设初始化以及功能函数已在`hardware`，界面例子包括 `gpio`、`i2c`、`pwm`、`sdio`、`spi`、`uart`、`usb`。|
|pcb|使用嘉立创EDA专业版进行绘制，项目例子都基于该线路板进行编写。|
|system|任务文件，以及延迟等等|
|third_party|第三方库，包含`cherryusb`、`fatfs`、`lvgl`、`rt-thread`|
|tools|下载程序工具，code-format工具（需要安装astyle)|
|user|main函数，链接脚本|

# 库函数使用说明

## CCU

主要用于初始化各外设时钟，例如 `串口`、`SPI`、`I2C`等等。

例如

```c
CCU_BUS2_GatingClockCmd(CCU_BUS2Gating_UART1, ENABLE);
CCU_BUS2_GatingResetCmd(CCU_BUS2Gating_UART1, ENABLE);
```

## EXTI

初始化

```c
void EXTI_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    
    GPIO_AF_Remap(GPIOE, GPIO_PinSource3, GPIO_AF_PE3_EINTE3);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line_3;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(EXTIE, &EXTI_InitStructure);
    
    rt_hw_interrupt_install(PIOE_INTERRUPT, EXTIE_IRQHandler, NULL, "exite_irq");
    rt_hw_interrupt_umask(PIOE_INTERRUPT);
}
```

中断

```c
void EXTIE_IRQHandler(int irqno, void *param)
{
  if (EXTI_GetFlagStatus(EXTIE, EXTI_Line_3) == SET)
  {
    /* 
        your code
    */
    EXTI_ClearFlag(EXTIE, EXTI_Line_3);
  }
}
```

## GPIO

初始化

```c
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}
```

置0

```c
GPIO_ResetBits(GPIOE, GPIO_Pin_5);
```

置1

```c
GPIO_SetBits(GPIOE, GPIO_Pin_5);
```

## I2C

初始化

```c
void I2C_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    
    CCU_BUS2_GatingClockCmd(CCU_BUS2Gating_I2C0, ENABLE);
    CCU_BUS2_GatingResetCmd(CCU_BUS2Gating_I2C0, ENABLE);
    
    GPIO_AF_Remap(GPIOE, GPIO_PinSource11, GPIO_AF_PE11_I2C0_SCK);
    GPIO_AF_Remap(GPIOE, GPIO_PinSource12, GPIO_AF_PE12_I2C0_SDA);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    I2C_DeInit(I2C0);
    I2C_InitStructure.SlaveAddress = I2C_ADDR;
    I2C_InitStructure.ClockSpeed = 400 * 1000;
    I2C_Init(I2C0, &I2C_InitStructure);
    
    I2C_Cmd(I2C0, ENABLE);
}
```

写操作

```c
I2C_Write_Reg(GT911_I2C, I2C_REG_SIZE_16BIT, reg, buf, len);
```

读操作

```c
I2C_Read_Reg(GT911_I2C, I2C_REG_SIZE_16BIT, reg, buf, len);
```

## LCD

例子查看[hardware/src/lcd.c](./hardware/src/lcd.c)。

如需修改屏幕参数，请在[hardware/inc/lcd.h](./hardware/inc/lcd.h)中修改。

```c
#define LCD_FREQ 30000000//30Mhz
#define MY_DISP_HOR_RES 800
#define MY_DISP_VER_RES 480

// LCD驱动参数设置
#define LCD_HOR_PULSE_WIDTH 8 // 水平脉宽
#define LCD_HOR_BACK_PORCH 8 // 水平后廊
#define LCD_HOR_FRONT_PORCH 4 // 水平前廊

#define LCD_VER_PULSE_WIDTH 8 // 垂直脉宽
#define LCD_VER_BACK_PORCH 10 // 垂直后廊
#define LCD_VER_FRONT_PORCH 4 // 垂直前廊
```

## PWM

初始化

```c
void PWM_Config(void)
{
    PWM_InitTypeDef PWM_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_AF_Remap(GPIOE, GPIO_PinSource6, GPIO_AF_PE6_PWM1);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    PWM_InitStructure.channel = PWM_CHANNEL_1;
    PWM_InitStructure.duty_cycle = 0;
    PWM_InitStructure.period = 463000; // 2160hz :1000000000/463000
    PWM_InitStructure.polarity = 1;
    PWM_Init(&PWM_InitStructure);
    
    PWM_Cmd(PWM_CHANNEL_1, ENABLE);
}
```

修改PWM占空比

```c
PWM_Set_Duty(PWM_CHANNEL_1, value);
```

## SDIO

初始化例子可查看[hardware/src/sdcard.c](./hardware/src/sdcard.c)。需移植`FATFS`进行使用，移植例子[third_party/fatfs/diskio.c](./third_party/fatfs/diskio.c)。

## SPI

初始化

```c
void SPI_Config(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    CCU_BUS0_GatingClockCmd(CCU_BUS0Gating_SPI0, ENABLE);
    CCU_BUS0_GatingResetCmd(CCU_BUS0Gating_SPI0, ENABLE);
    
    GPIO_AF_Remap(GPIOC, GPIO_PinSource0, GPIO_AF_PC0_SPI0_CLK);
    GPIO_AF_Remap(GPIOC, GPIO_PinSource2, GPIO_AF_PC2_SPI0_MISO);
    GPIO_AF_Remap(GPIOC, GPIO_PinSource3, GPIO_AF_PC3_SPI0_MOSI);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    /*W25QXX_CS*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    W25QXX_CS = 1;
    
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI0, &SPI_InitStructure);
    
    SPI_Cmd(SPI0, ENABLE); // 使能SPI外设
}
```

写操作

```c
SPI_TransmitData8(SPI0, TxData);
```

读操作

```c
SPI_ReceiveData8(SPI0);
```

## UART

初始化

```c
void UART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    UART_InitTypeDef UART_InitStructure;
    
    GPIO_AF_Remap(GPIOA, GPIO_PinSource2, GPIO_AF_PA2_UART1_RX);
    GPIO_AF_Remap(GPIOA, GPIO_PinSource3, GPIO_AF_PA3_UART1_TX);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    CCU_BUS2_GatingClockCmd(CCU_BUS2Gating_UART1, ENABLE);
    CCU_BUS2_GatingResetCmd(CCU_BUS2Gating_UART1, ENABLE);
    
    UART_InitStructure.UART_BaudRate = 115200;
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;
    UART_InitStructure.UART_StopBits = UART_StopBits_1;
    UART_InitStructure.UART_Parity = UART_Parity_No;
    UART_Init(UART1, &UART_InitStructure);
    
    UART_ITConfig(UART1, UART_IT_ERBFI, ENABLE);
    
    rt_hw_interrupt_install(UART1_INTERRUPT, UART1_IRQHandler, NULL, "uart1_irq");
    rt_hw_interrupt_umask(UART1_INTERRUPT);
}
```

写操作

```c
for(uint16_t i = 0; i < strlen((char *)uart_Data.TXD_BUF); i++)
{
  UART_SendData(UART1, uart_Data.TXD_BUF[i]);
  while(UART_Get_Status(UART1, UART_USR_TFNF) != SET)
  {
  }
}
```

读操作

```c
UART_ReceiveData(UART1);
```

## USB

使用USB功能，需要配合`Cherryusb`进行使用。

### 主机

使用主机前，请在[user/common.h](./user/common.h)中定义

```c
#define TEST_USB_MODE TEST_USB_MODE_HOST
```

初始化例子可查看[hardware/src/usbh_msc_config.c](./hardware/src/usbh_msc_config.c)。主机还需移植`FATFS`进行使用，移植例子[third_party/fatfs/diskio.c](./third_party/fatfs/diskio.c)。

### 设备

使用设备前，请在[user/common.h](./user/common.h)中定义

```c
#define TEST_USB_MODE TEST_USB_MODE_DEVICE
```

初始化例子可查看[hardware/src/usbd_msc_config.c](./hardware/src/usbd_msc_config.c)。

## WDOG

初始化

```c
void WDOG_Config(void)
{
    WDOG_Set_Mode(WDOG_RST_MODE);
    WDOG_Set_Value(1);//喂狗周期为1s
    WDOG_Enable();
}
```

喂狗

```c
WDOG_Feed();
```