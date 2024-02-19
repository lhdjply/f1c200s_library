#ifndef __F1CX00S_SPI__H
#define __F1CX00S_SPI__H

#include "f1cx00s.h"

#define SPI_Mode_Slave ((uint32_t)(0 << 1))
#define SPI_Mode_Master ((uint32_t)(1 << 1))

#define SPI_CPOL_Low ((uint32_t)(1 << 1))
#define SPI_CPOL_High ((uint32_t)(0 << 1))

#define SPI_CPHA_1Edge ((uint32_t)(1 << 0))
#define SPI_CPHA_2Edge ((uint32_t)(0 << 0))

#define SPI_NSS_Soft ((uint32_t)(0 << 6))
#define SPI_NSS_Hard ((uint32_t)(1 << 6))

#define SPI_BaudRatePrescaler_2 0
#define SPI_BaudRatePrescaler_4 1
#define SPI_BaudRatePrescaler_8 3
#define SPI_BaudRatePrescaler_16 7
#define SPI_BaudRatePrescaler_32 15
#define SPI_BaudRatePrescaler_64 31
#define SPI_BaudRatePrescaler_128 63
#define SPI_BaudRatePrescaler_256 127

#define SPI_FirstBit_MSB ((uint32_t)(0 << 12))
#define SPI_FirstBit_LSB ((uint32_t)(1 << 12))

typedef struct
{
  uint16_t SPI_Mode;
  uint16_t SPI_CPOL;
  uint16_t SPI_CPHA;
  uint16_t SPI_NSS;
  uint16_t SPI_BaudRatePrescaler;
  uint16_t SPI_FirstBit;
} SPI_InitTypeDef;

void SPI_DeInit(SPI_TypeDef * SPIx);
void SPI_Init(SPI_TypeDef * SPIx, SPI_InitTypeDef * SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef * SPIx, FunctionalState NewState);
void SPI_TransmitData8(SPI_TypeDef * SPIx, uint8_t TxData);
uint8_t SPI_ReceiveData8(SPI_TypeDef * SPIx);

#endif
