#ifndef __F1CX00S_GPIO__H
#define __F1CX00S_GPIO__H

#include "f1cx00s.h"

#define GPIO_Pin_0 ((uint32_t)0x00000001)  /*!< Pin 0 selected */
#define GPIO_Pin_1 ((uint32_t)0x00000002)  /*!< Pin 1 selected */
#define GPIO_Pin_2 ((uint32_t)0x00000004)  /*!< Pin 2 selected */
#define GPIO_Pin_3 ((uint32_t)0x00000008)  /*!< Pin 3 selected */
#define GPIO_Pin_4 ((uint32_t)0x00000010)  /*!< Pin 4 selected */
#define GPIO_Pin_5 ((uint32_t)0x00000020)  /*!< Pin 5 selected */
#define GPIO_Pin_6 ((uint32_t)0x00000040)  /*!< Pin 6 selected */
#define GPIO_Pin_7 ((uint32_t)0x00000080)  /*!< Pin 7 selected */
#define GPIO_Pin_8 ((uint32_t)0x00000100)  /*!< Pin 8 selected */
#define GPIO_Pin_9 ((uint32_t)0x00000200)  /*!< Pin 9 selected */
#define GPIO_Pin_10 ((uint32_t)0x00000400) /*!< Pin 10 selected */
#define GPIO_Pin_11 ((uint32_t)0x00000800) /*!< Pin 11 selected */
#define GPIO_Pin_12 ((uint32_t)0x00001000) /*!< Pin 12 selected */
#define GPIO_Pin_13 ((uint32_t)0x00002000) /*!< Pin 13 selected */
#define GPIO_Pin_14 ((uint32_t)0x00004000) /*!< Pin 14 selected */
#define GPIO_Pin_15 ((uint32_t)0x00008000) /*!< Pin 15 selected */
#define GPIO_Pin_16 ((uint32_t)0x00010000) /*!< Pin 16 selected */
#define GPIO_Pin_17 ((uint32_t)0x00020000) /*!< Pin 17 selected */
#define GPIO_Pin_18 ((uint32_t)0x00040000) /*!< Pin 18 selected */
#define GPIO_Pin_19 ((uint32_t)0x00080000) /*!< Pin 19 selected */
#define GPIO_Pin_20 ((uint32_t)0x00100000) /*!< Pin 20 selected */
#define GPIO_Pin_21 ((uint32_t)0x00200000) /*!< Pin 21 selected */
#define GPIO_Pin_22 ((uint32_t)0x00400000) /*!< Pin 22 selected */
#define GPIO_Pin_23 ((uint32_t)0x00800000) /*!< Pin 23 selected */
#define GPIO_Pin_24 ((uint32_t)0x01000000) /*!< Pin 24 selected */
#define GPIO_Pin_25 ((uint32_t)0x02000000) /*!< Pin 25 selected */
#define GPIO_Pin_26 ((uint32_t)0x04000000) /*!< Pin 26 selected */
#define GPIO_Pin_27 ((uint32_t)0x08000000) /*!< Pin 27 selected */
#define GPIO_Pin_28 ((uint32_t)0x10000000) /*!< Pin 28 selected */
#define GPIO_Pin_29 ((uint32_t)0x20000000) /*!< Pin 29 selected */
#define GPIO_Pin_30 ((uint32_t)0x40000000) /*!< Pin 30 selected */
#define GPIO_Pin_31 ((uint32_t)0x80000000) /*!< Pin 31 selected */

#define GPIO_PinSource0 0
#define GPIO_PinSource1 1
#define GPIO_PinSource2 2
#define GPIO_PinSource3 3
#define GPIO_PinSource4 4
#define GPIO_PinSource5 5
#define GPIO_PinSource6 6
#define GPIO_PinSource7 7
#define GPIO_PinSource8 8
#define GPIO_PinSource9 9
#define GPIO_PinSource10 10
#define GPIO_PinSource11 11
#define GPIO_PinSource12 12
#define GPIO_PinSource13 13
#define GPIO_PinSource14 14
#define GPIO_PinSource15 15
#define GPIO_PinSource16 16
#define GPIO_PinSource17 17
#define GPIO_PinSource18 18
#define GPIO_PinSource19 19
#define GPIO_PinSource20 20
#define GPIO_PinSource21 21
#define GPIO_PinSource22 22
#define GPIO_PinSource23 23
#define GPIO_PinSource24 24
#define GPIO_PinSource25 25
#define GPIO_PinSource26 26
#define GPIO_PinSource27 27
#define GPIO_PinSource28 28
#define GPIO_PinSource29 28
#define GPIO_PinSource30 30
#define GPIO_PinSource31 31

#define GPIO_AF_PA0_TP_X1 2
#define GPIO_AF_PA0_DA_BCLK 4
#define GPIO_AF_PA0_UART1_RTS 5
#define GPIO_AF_PA0_SPI1_CS 6

#define GPIO_AF_PA1_TP_X2 (2 << 4)
#define GPIO_AF_PA1_DA_LRCK (4 << 4)
#define GPIO_AF_PA1_UART1_CTS (5 << 4)
#define GPIO_AF_PA1_SPI1_MOSI (6 << 4)

#define GPIO_AF_PA2_TP_Y1 (2 << 8)
#define GPIO_AF_PA2_PWM0 (3 << 8)
#define GPIO_AF_PA2_DA_IN (4 << 8)
#define GPIO_AF_PA2_UART1_RX (5 << 8)
#define GPIO_AF_PA2_SPI1_CLK (6 << 8)

#define GPIO_AF_PA3_TP_Y2 (2 << 12)
#define GPIO_AF_PA3_IR_RX (3 << 12)
#define GPIO_AF_PA3_DA_OUT (4 << 12)
#define GPIO_AF_PA3_UART1_TX (5 << 12)
#define GPIO_AF_PA3_SPI1_MISO (6 << 12)

#define GPIO_AF_PB3_DDR_REF_D (2 << 12)
#define GPIO_AF_PB3_IR_RX (3 << 12)

#define GPIO_AF_PC0_SPI0_CLK 2
#define GPIO_AF_PC0_SDC1_CLK 3

#define GPIO_AF_PC1_SPI0_CS (2 << 4)
#define GPIO_AF_PC1_SDC1_CMD (3 << 4)

#define GPIO_AF_PC2_SPI0_MISO (2 << 8)
#define GPIO_AF_PC2_SDC1_D0 (3 << 8)

#define GPIO_AF_PC3_SPI0_MOSI (2 << 12)
#define GPIO_AF_PC3_UART0_TX (3 << 12)

#define GPIO_AF_PD0_LCD_D2 2
#define GPIO_AF_PD0_I2C0_SDA 3
#define GPIO_AF_PD0_RSB_SDA 4
#define GPIO_AF_PD0_EINTD0 6

#define GPIO_AF_PD1_LCD_D3 (2 << 4)
#define GPIO_AF_PD1_UART1_RTS (3 << 4)
#define GPIO_AF_PD1_EINTD1 (6 << 4)

#define GPIO_AF_PD2_LCD_D4 (2 << 8)
#define GPIO_AF_PD2_UART1_CTS (3 << 8)
#define GPIO_AF_PD2_EINTD2 (6 << 8)

#define GPIO_AF_PD3_LCD_D5 (2 << 12)
#define GPIO_AF_PD3_UART1_RX (3 << 12)
#define GPIO_AF_PD3_EINTD3 (6 << 12)

#define GPIO_AF_PD4_LCD_D6 (2 << 16)
#define GPIO_AF_PD4_UART1_TX (3 << 16)
#define GPIO_AF_PD4_EINTD4 (6 << 16)

#define GPIO_AF_PD5_LCD_D7 (2 << 20)
#define GPIO_AF_PD5_I2C1_SCK (3 << 20)
#define GPIO_AF_PD5_EINTD5 (6 << 20)

#define GPIO_AF_PD6_LCD_D10 (2 << 24)
#define GPIO_AF_PD6_I2C1_SDA (3 << 24)
#define GPIO_AF_PD6_EINTD6 (6 << 24)

#define GPIO_AF_PD7_LCD_D11 (2 << 28)
#define GPIO_AF_PD7_DA_MCLK (3 << 28)
#define GPIO_AF_PD7_EINTD7 (6 << 28)

#define GPIO_AF_PD8_LCD_D12 2
#define GPIO_AF_PD8_DA_BCLK 3
#define GPIO_AF_PD8_EINTD8 6

#define GPIO_AF_PD9_LCD_D13 (2 << 4)
#define GPIO_AF_PD9_DA_LRCK (3 << 4)
#define GPIO_AF_PD9_EINTD9 (6 << 4)

#define GPIO_AF_PD10_LCD_D14 (2 << 8)
#define GPIO_AF_PD10_DA_IN (3 << 8)
#define GPIO_AF_PD10_EINTD10 (6 << 8)

#define GPIO_AF_PD11_LCD_D15 (2 << 12)
#define GPIO_AF_PD11_DA_OUT (3 << 12)
#define GPIO_AF_PD11_EINTD11 (6 << 12)

#define GPIO_AF_PD12_LCD_D18 (2 << 16)
#define GPIO_AF_PD12_I2C0_SCK (3 << 16)
#define GPIO_AF_PD12_RSB_SCK (4 << 16)
#define GPIO_AF_PD12_EINTD12 (6 << 16)

#define GPIO_AF_PD13_LCD_D19 (2 << 20)
#define GPIO_AF_PD13_UART2_TX (3 << 20)
#define GPIO_AF_PD13_EINTD13 (6 << 20)

#define GPIO_AF_PD14_LCD_D20 (2 << 24)
#define GPIO_AF_PD14_UART2_RX (3 << 24)
#define GPIO_AF_PD14_EINTD14 (6 << 24)

#define GPIO_AF_PD15_LCD_D21 (2 << 28)
#define GPIO_AF_PD15_UART2_RTS (3 << 28)
#define GPIO_AF_PD15_I2C2_SCK (4 << 28)
#define GPIO_AF_PD15_EINTD15 (6 << 28)

#define GPIO_AF_PD16_LCD_D22 2
#define GPIO_AF_PD16_UART2_CTS 3
#define GPIO_AF_PD16_I2C2_SDA 4
#define GPIO_AF_PD16_EINTD16 6

#define GPIO_AF_PD17_LCD_D23 (2 << 4)
#define GPIO_AF_PD17_OWA_OUT (3 << 4)
#define GPIO_AF_PD17_EINTD17 (6 << 4)

#define GPIO_AF_PD18_LCD_CLK (2 << 8)
#define GPIO_AF_PD18_SPI0_CS (3 << 8)
#define GPIO_AF_PD18_EINTD18 (6 << 8)

#define GPIO_AF_PD19_LCD_DE (2 << 12)
#define GPIO_AF_PD19_SPI0_MOSI (3 << 12)
#define GPIO_AF_PD19_EINTD19 (6 << 12)

#define GPIO_AF_PD20_LCD_HSYNC (2 << 16)
#define GPIO_AF_PD20_SPI0_CLK (3 << 16)
#define GPIO_AF_PD20_EINTD20 (6 << 16)

#define GPIO_AF_PD21_LCD_VSYNC (2 << 20)
#define GPIO_AF_PD21_SPI0_MISO (3 << 20)
#define GPIO_AF_PD21_EINTD21 (6 << 20)

#define GPIO_AF_PE0_CSI_HSYNC 2
#define GPIO_AF_PE0_LCD_D0 3
#define GPIO_AF_PE0_I2C2_SCK 4
#define GPIO_AF_PE0_UART0_RX 5
#define GPIO_AF_PE0_EINTE0 6

#define GPIO_AF_PE1_CSI_VSYNC (2 << 4)
#define GPIO_AF_PE1_LCD_D1 (3 << 4)
#define GPIO_AF_PE1_I2C2_SDA (4 << 4)
#define GPIO_AF_PE1_UART0_TX (5 << 4)
#define GPIO_AF_PE1_EINTE1 (6 << 4)

#define GPIO_AF_PE2_CSI_PCLK (2 << 8)
#define GPIO_AF_PE2_LCD_D8 (3 << 8)
#define GPIO_AF_PE2_CLK_OUT (4 << 8)
#define GPIO_AF_PE2_EINTE2 (6 << 8)

#define GPIO_AF_PE3_CSI_D0 (2 << 12)
#define GPIO_AF_PE3_ULCD_D9 (3 << 12)
#define GPIO_AF_PE3_DA_BCLK (4 << 12)
#define GPIO_AF_PE3_RSB_SCK (5 << 12)
#define GPIO_AF_PE3_EINTE3 (6 << 12)

#define GPIO_AF_PE4_CSI_D1 (2 << 16)
#define GPIO_AF_PE4_LCD_D16 (3 << 16)
#define GPIO_AF_PE4_DA_LRCK (4 << 16)
#define GPIO_AF_PE4_RSB_SDA (5 << 16)
#define GPIO_AF_PE4_EINTE4 (6 << 16)

#define GPIO_AF_PE5_CSI_D2 (2 << 20)
#define GPIO_AF_PE5_LCD_D17 (3 << 20)
#define GPIO_AF_PE5_DA_IN (4 << 20)
#define GPIO_AF_PE5_EINTE5 (6 << 20)

#define GPIO_AF_PE6_CSI_D3 (2 << 24)
#define GPIO_AF_PE6_PWM1 (3 << 24)
#define GPIO_AF_PE6_DA_OUT (4 << 24)
#define GPIO_AF_PE6_OWA_OUT (5 << 24)
#define GPIO_AF_PE6_EINTE6 (6 << 24)

#define GPIO_AF_PE7_CSI_D4 (2 << 28)
#define GPIO_AF_PE7_UART2_TX (3 << 28)
#define GPIO_AF_PE7_SPI1_CS (4 << 28)
#define GPIO_AF_PE7_EINTE7 (6 << 28)

#define GPIO_AF_PE8_CSI_D5 2
#define GPIO_AF_PE8_UART2_RX 3
#define GPIO_AF_PE8_SPI1_MOSI 4
#define GPIO_AF_PE8_EINTE8 6

#define GPIO_AF_PE9_CSI_D6 (2 << 4)
#define GPIO_AF_PE9_UART2_RTS (3 << 4)
#define GPIO_AF_PE9_SPI1_CLK (4 << 4)
#define GPIO_AF_PE9_EINTE9 (6 << 4)

#define GPIO_AF_PE10_CSI_D7 (2 << 8)
#define GPIO_AF_PE10_UART2_CTS (3 << 8)
#define GPIO_AF_PE10_SPI1_MISO (4 << 8)
#define GPIO_AF_PE10_EINTE10 (6 << 8)

#define GPIO_AF_PE11_CLK_OUT (2 << 12)
#define GPIO_AF_PE11_I2C0_SCK (3 << 12)
#define GPIO_AF_PE11_IR_RX (4 << 12)
#define GPIO_AF_PE11_EINTE11 (6 << 12)

#define GPIO_AF_PE12_DA_MCLK (2 << 16)
#define GPIO_AF_PE12_I2C0_SDA (3 << 16)
#define GPIO_AF_PE12_PWM0 (4 << 16)
#define GPIO_AF_PE12_EINTE12 (6 << 16)

#define GPIO_AF_PF0_SDC0_D1 2
#define GPIO_AF_PF0_DBG_MS 3
#define GPIO_AF_PF0_IR_RX 4
#define GPIO_AF_PF0_EINTF0 6

#define GPIO_AF_PF1_SDC0_D0 (2 << 4)
#define GPIO_AF_PF1_DBG_DI (3 << 4)
#define GPIO_AF_PF1_EINTF1 (6 << 4)

#define GPIO_AF_PF2_SDC0_CLK (2 << 8)
#define GPIO_AF_PF2_UART0_RX (3 << 8)
#define GPIO_AF_PF2_EINTF2 (6 << 8)

#define GPIO_AF_PF3_SDC0_CMD (2 << 12)
#define GPIO_AF_PF3_DBG_DO (3 << 12)
#define GPIO_AF_PF3_EINTF3 (6 << 12)

#define GPIO_AF_PF4_SDC0_D3 (2 << 16)
#define GPIO_AF_PF4_UART0_TX (3 << 16)
#define GPIO_AF_PF4_EINTF4 (6 << 16)

#define GPIO_AF_PF5_SDC0_D2 (2 << 20)
#define GPIO_AF_PF5_DBG_CK (3 << 20)
#define GPIO_AF_PF5_PWM1 (4 << 20)
#define GPIO_AF_PF5_EINTF5 (6 << 20)

typedef enum
{
  GPIO_Mode_IN = 0x00,  /*!< GPIO Input Mode */
  GPIO_Mode_OUT = 0x01, /*!< GPIO Output Mode */
  GPIO_Mode_AF = 0x02,  /*!< GPIO Alternate function Mode */
  GPIO_Mode_AN = 0x03   /*!< GPIO Analog Mode */
} GPIOMode_TypeDef;

typedef enum
{
  GPIO_DriveCurrent_Level0 = 0x00,
  GPIO_DriveCurrent_Level1 = 0x01,
  GPIO_DriveCurrent_Level2 = 0x02,
  GPIO_DriveCurrent_Level3 = 0x03,
} GPIODriveCurrent_TypeDef;

typedef enum
{
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP = 0x01,
  GPIO_PuPd_DOWN = 0x02
} GPIOPuPd_TypeDef;

typedef struct
{
  uint32_t GPIO_Pin;
  GPIOMode_TypeDef GPIO_Mode;
  GPIODriveCurrent_TypeDef GPIO_DriveCurrent;
  GPIOPuPd_TypeDef GPIO_PuPd;
} GPIO_InitTypeDef;

typedef enum
{
  Bit_RESET = 0,
  Bit_SET
} BitAction;

void GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef * GPIO_InitStruct);
void GPIO_WriteBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin, BitAction BitVal);
void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);
void GPIO_AF_Remap(GPIO_TypeDef * GPIOx, uint32_t GPIO_PinSourceNum, uint32_t GPIO_AF_FUN);

#endif
