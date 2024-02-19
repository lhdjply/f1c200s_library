#ifndef __F1CX00S_I2C__H
#define __F1CX00S_I2C__H

#include "f1cx00s.h"

typedef enum
{
  I2C_STAT_BUS_ERROR = 0x00,
  I2C_STAT_TX_START = 0x08,
  I2C_STAT_TX_RSTART = 0x10,
  I2C_STAT_TX_AW_ACK = 0x18,
  I2C_STAT_TX_AW_NAK = 0x20,
  I2C_STAT_TXD_ACK = 0x28,
  I2C_STAT_TXD_NAK = 0x30,
  I2C_STAT_LOST_ARB = 0x38,
  I2C_STAT_TX_AR_ACK = 0x40,
  I2C_STAT_TX_AR_NAK = 0x48,
  I2C_STAT_RXD_ACK = 0x50,
  I2C_STAT_RXD_NAK = 0x58,
  I2C_STAT_IDLE = 0xf8,
} I2C_STAT;

typedef enum
{
  I2C_REG_SIZE_8BIT = 0,
  I2C_REG_SIZE_16BIT,
} I2C_REG_SIZE;

typedef struct
{
  uint8_t SlaveAddress;
  uint32_t ClockSpeed;
} I2C_InitTypeDef;

void I2C_DeInit(I2C_TypeDef * I2Cx);
void I2C_Init(I2C_TypeDef * I2Cx, I2C_InitTypeDef * I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef * I2Cx, FunctionalState NewState);
void I2C_SetSlaveAddress(I2C_TypeDef * I2Cx, uint8_t SlaveAddress);
void I2C_Write_Reg(I2C_TypeDef * I2Cx, I2C_REG_SIZE Reg_Size, uint16_t Reg, uint8_t * Data, uint32_t data_len);
void I2C_Read_Reg(I2C_TypeDef * I2Cx, I2C_REG_SIZE Reg_Size, uint16_t Reg, uint8_t * Data, uint32_t data_len);

#endif
