#include "f1cx00s_spi.h"

void SPI_DeInit(SPI_TypeDef * SPIx)
{
  SPIx->GCR = SPIx->GCR | (1 << 31);
}

void SPI_Init(SPI_TypeDef * SPIx, SPI_InitTypeDef * SPI_InitStruct)
{
  SPIx->CCR = SPIx->CCR & (~0x10FF);
  SPIx->CCR = SPIx->CCR | SPI_InitStruct->SPI_BaudRatePrescaler | 0x1000;

  SPIx->GCR = SPIx->GCR & (~(1 << 1));
  SPIx->GCR = SPIx->GCR | SPI_InitStruct->SPI_Mode;

  SPIx->TCR = SPIx->TCR & (~0x1043);
  SPIx->TCR = SPIx->TCR |
              SPI_InitStruct->SPI_CPOL |
              SPI_InitStruct->SPI_CPHA |
              SPI_InitStruct->SPI_FirstBit |
              SPI_InitStruct->SPI_NSS | (1 << 2);

  SPIx->FCR = SPIx->FCR | (1 << 31) | (1 << 15);
}

void SPI_Cmd(SPI_TypeDef * SPIx, FunctionalState NewState)
{
  SPIx->GCR = SPIx->GCR & (~(1 << 0));
  SPIx->GCR = SPIx->GCR | NewState;
}

void SPI_TransmitData8(SPI_TypeDef * SPIx, uint8_t TxData)
{
  SPIx->MBC = 1;
  SPIx->MTC = 1;
  SPIx->BCC = 1;
  *((volatile uint8_t *)(&SPIx->TXD_DATA)) = TxData;
  SPIx->TCR |= 1 << 31;
}

uint8_t SPI_ReceiveData8(SPI_TypeDef * SPIx)
{
  return *((volatile uint8_t *)(&SPIx->RXD_DATA));
}
