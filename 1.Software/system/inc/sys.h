#ifndef SYSTEM_SYS_H_
#define SYSTEM_SYS_H_

#include "f1cx00s_conf.h"

typedef struct
{
  volatile uint8_t bit0 : 1;
  volatile uint8_t bit1 : 1;
  volatile uint8_t bit2 : 1;
  volatile uint8_t bit3 : 1;
  volatile uint8_t bit4 : 1;
  volatile uint8_t bit5 : 1;
  volatile uint8_t bit6 : 1;
  volatile uint8_t bit7 : 1;
} BIT8;

typedef struct
{
  volatile uint16_t bit0 : 1;
  volatile uint16_t bit1 : 1;
  volatile uint16_t bit2 : 1;
  volatile uint16_t bit3 : 1;
  volatile uint16_t bit4 : 1;
  volatile uint16_t bit5 : 1;
  volatile uint16_t bit6 : 1;
  volatile uint16_t bit7 : 1;
  volatile uint16_t bit8 : 1;
  volatile uint16_t bit9 : 1;
  volatile uint16_t bit10 : 1;
  volatile uint16_t bit11 : 1;
  volatile uint16_t bit12 : 1;
  volatile uint16_t bit13 : 1;
  volatile uint16_t bit14 : 1;
  volatile uint16_t bit15 : 1;
} BIT16;

typedef struct
{
  volatile uint32_t bit0 : 1;
  volatile uint32_t bit1 : 1;
  volatile uint32_t bit2 : 1;
  volatile uint32_t bit3 : 1;
  volatile uint32_t bit4 : 1;
  volatile uint32_t bit5 : 1;
  volatile uint32_t bit6 : 1;
  volatile uint32_t bit7 : 1;
  volatile uint32_t bit8 : 1;
  volatile uint32_t bit9 : 1;
  volatile uint32_t bit10 : 1;
  volatile uint32_t bit11 : 1;
  volatile uint32_t bit12 : 1;
  volatile uint32_t bit13 : 1;
  volatile uint32_t bit14 : 1;
  volatile uint32_t bit15 : 1;
  volatile uint32_t bit16 : 1;
  volatile uint32_t bit17 : 1;
  volatile uint32_t bit18 : 1;
  volatile uint32_t bit19 : 1;
  volatile uint32_t bit20 : 1;
  volatile uint32_t bit21 : 1;
  volatile uint32_t bit22 : 1;
  volatile uint32_t bit23 : 1;
  volatile uint32_t bit24 : 1;
  volatile uint32_t bit25 : 1;
  volatile uint32_t bit26 : 1;
  volatile uint32_t bit27 : 1;
  volatile uint32_t bit28 : 1;
  volatile uint32_t bit29 : 1;
  volatile uint32_t bit30 : 1;
  volatile uint32_t bit31 : 1;
} BIT32;

// IO口地址映射
#define GPIOA_ODR_Addr ((BIT32 *)&GPIOA->DATA)
#define GPIOB_ODR_Addr ((BIT32 *)&GPIOB->DATA)
#define GPIOC_ODR_Addr ((BIT32 *)&GPIOC->DATA)
#define GPIOD_ODR_Addr ((BIT32 *)&GPIOD->DATA)
#define GPIOE_ODR_Addr ((BIT32 *)&GPIOE->DATA)
#define GPIOF_ODR_Addr ((BIT32 *)&GPIOF->DATA)

#define GPIOA_IDR_Addr ((BIT32 *)&GPIOA->DATA)
#define GPIOB_IDR_Addr ((BIT32 *)&GPIOB->DATA)
#define GPIOC_IDR_Addr ((BIT32 *)&GPIOC->DATA)
#define GPIOD_IDR_Addr ((BIT32 *)&GPIOD->DATA)
#define GPIOE_IDR_Addr ((BIT32 *)&GPIOE->DATA)
#define GPIOF_IDR_Addr ((BIT32 *)&GPIOF->DATA)

// IO口操作,只对单一的IO口!
// 确保n的值小于16!
#define PAout(n) (GPIOA_ODR_Addr->bit##n) // 输出
#define PAin(n) (GPIOA_IDR_Addr->bit##n)  // 输入

#define PBout(n) (GPIOB_ODR_Addr->bit##n) // 输出
#define PBin(n) (GPIOB_IDR_Addr->bit##n)  // 输入

#define PCout(n) (GPIOC_ODR_Addr->bit##n) // 输出
#define PCin(n) (GPIOC_IDR_Addr->bit##n)  // 输入

#define PDout(n) (GPIOD_ODR_Addr->bit##n) // 输出
#define PDin(n) (GPIOD_IDR_Addr->bit##n)  // 输入

#define PEout(n) (GPIOE_ODR_Addr->bit##n) // 输出
#define PEin(n) (GPIOE_IDR_Addr->bit##n)  // 输入

#define PFout(n) (GPIOF_ODR_Addr->bit##n) // 输出
#define PFin(n) (GPIOF_IDR_Addr->bit##n)  // 输入

#endif /* SYSTEM_SYS_H_ */
