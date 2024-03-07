#include "f1cx00s_i2c.h"
#include "f1cx00s_ccu.h"

void I2C_DeInit(I2C_TypeDef * I2Cx)
{
  I2Cx->SRST |= 0x01;
}

void I2C_Init(I2C_TypeDef * I2Cx, I2C_InitTypeDef * I2C_InitStruct)
{
  uint64_t pclk = APB_Get_clk();
  int64_t freq, delta, best = 0x7fffffffffffffffLL;
  int tm = 5, tn = 0;
  int m, n;

  for(n = 0; n <= 7; n++)
  {
    for(m = 0; m <= 15; m++)
    {
      freq = pclk / (10 * (m + 1) * (1 << n));
      delta = I2C_InitStruct->ClockSpeed - freq;
      if(delta >= 0 && delta < best)
      {
        tm = m;
        tn = n;
        best = delta;
      }
      if(best == 0)
        break;
    }
  }
  I2Cx->ADDR = I2C_InitStruct->SlaveAddress;
  I2Cx->XADDR = 0;
  I2Cx->CCR = ((tm & 0xf) << 3) | ((tn & 0x7) << 0);
}

void I2C_Cmd(I2C_TypeDef * I2Cx, FunctionalState NewState)
{
  I2Cx->CNTR = (NewState << 6) | (1 << 4);
}

void I2C_SetSlaveAddress(I2C_TypeDef * I2Cx, uint8_t SlaveAddress)
{
  I2Cx->ADDR = SlaveAddress;
}

static int I2C_Wait_Status(I2C_TypeDef * I2Cx)
{
  uint16_t timeout = 0;
  while(!(I2Cx->CNTR & (1 << 3)))
  {
    timeout++;
    if(timeout >= 300)
    {
      return -1;
    }
  }
  return I2Cx->STAT;
}

static int I2C_Start(I2C_TypeDef * I2Cx)
{
  uint16_t timeout = 0;
  I2Cx->CNTR = (1 << 7) | (1 << 6) | (1 << 5) | (1 << 2);
  while(!(I2Cx->CNTR & (1 << 5)))
  {
    timeout++;
    if(timeout >= 300)
    {
      return -1;
    }
  }
  return I2C_Wait_Status(I2Cx);
}

static int I2C_Stop(I2C_TypeDef * I2Cx)
{
  uint16_t timeout = 0;
  I2Cx->CNTR = (I2Cx->CNTR | (1 << 4)) & ~((1 << 7) | (1 << 3));
  while(!(I2Cx->CNTR & (1 << 4)))
  {
    timeout++;
    if(timeout >= 300)
    {
      return -1;
    }
  }
  return 0;
}

static int I2C_Send_Data(I2C_TypeDef * I2Cx, uint8_t Data)
{
  I2Cx->DATA = Data;
  I2Cx->CNTR = I2Cx->CNTR & (~(1 << 3));
  return I2C_Wait_Status(I2Cx);
}

static int I2C_Receive_Data(I2C_TypeDef * I2Cx, uint8_t * Data, uint32_t data_len)
{
  uint8_t * p = Data;
  uint32_t len = data_len;
  if(I2C_Send_Data(I2Cx, (uint8_t)(I2Cx->ADDR << 1 | 1)) == -1)
  {
    return -1;
  }
  while(len > 0)
  {
    switch(I2C_Wait_Status(I2Cx))
    {
      case I2C_STAT_TX_AR_ACK:
        if(len == 1)
        {
          I2Cx->CNTR = I2Cx->CNTR & ~((1 << 3) | (1 << 2));
        }
        else
        {
          I2Cx->CNTR = I2Cx->CNTR & ~(1 << 3);
        }
        break;
      case I2C_STAT_RXD_ACK:
        *p++ = I2Cx->DATA;
        len--;
        if(len == 1)
        {
          I2Cx->CNTR = I2Cx->CNTR & ~((1 << 3) | (1 << 2));
        }
        else
        {
          I2Cx->CNTR = I2Cx->CNTR & ~(1 << 3);
        }
        break;
      case I2C_STAT_RXD_NAK:
        *p++ = I2Cx->DATA;
        len--;
        break;
      default:
        return -1;
    }
  }
  return 0;
}

void I2C_Write_Reg(I2C_TypeDef * I2Cx, I2C_REG_SIZE Reg_Size, uint16_t Reg, uint8_t * Data, uint32_t data_len)
{
  uint32_t i;
  I2C_Start(I2Cx);
  I2C_Send_Data(I2Cx, (uint8_t)(I2Cx->ADDR << 1));
  if(Reg_Size == I2C_REG_SIZE_8BIT)
  {
    I2C_Send_Data(I2Cx, Reg);
  }
  else
  {
    I2C_Send_Data(I2Cx, Reg >> 8);
    I2C_Send_Data(I2Cx, Reg);
  }
  for(i = 0; i < data_len; i++)
  {
    I2C_Send_Data(I2Cx, Data[i]);
  }
  I2C_Stop(I2Cx);
}

void I2C_Read_Reg(I2C_TypeDef * I2Cx, I2C_REG_SIZE Reg_Size, uint16_t Reg, uint8_t * Data, uint32_t data_len)
{
  I2C_Start(I2Cx);
  I2C_Send_Data(I2Cx, (uint8_t)(I2Cx->ADDR << 1));
  if(Reg_Size == I2C_REG_SIZE_8BIT)
  {
    I2C_Send_Data(I2Cx, Reg);
  }
  else
  {
    I2C_Send_Data(I2Cx, Reg >> 8);
    I2C_Send_Data(I2Cx, Reg);
  }
  I2C_Start(I2Cx);
  I2C_Receive_Data(I2Cx, Data, data_len);
  I2C_Stop(I2Cx);
}
