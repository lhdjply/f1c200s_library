#include "f1cx00s_gpio.h"

void GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef * GPIO_InitStruct)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if(((GPIO_InitStruct->GPIO_Pin) & (1 << i)) != 0)
    {
      switch(i)
      {
        case 0 ... 7:
          if((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT))
          {
            GPIOx->CFG0 = GPIOx->CFG0 & (~(7 << (i * 4)));
            GPIOx->CFG0 = GPIOx->CFG0 | (GPIO_InitStruct->GPIO_Mode << (i * 4));
          }
          GPIOx->DRV0 = GPIOx->DRV0 & (~(3 << (i * 2)));
          GPIOx->DRV0 = GPIOx->DRV0 | (GPIO_InitStruct->GPIO_DriveCurrent << (i * 2));
          GPIOx->PUL0 = GPIOx->PUL0 & (~(3 << (i * 2)));
          GPIOx->PUL0 = GPIOx->PUL0 | (GPIO_InitStruct->GPIO_PuPd << (i * 2));
          break;
        case 8 ... 15:
          if((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT))
          {
            GPIOx->CFG1 = GPIOx->CFG1 & (~(7 << ((i - 8) * 4)));
            GPIOx->CFG1 = GPIOx->CFG1 | (GPIO_InitStruct->GPIO_Mode << ((i - 8) * 4));
          }
          GPIOx->DRV0 = GPIOx->DRV0 & (~(3 << (i * 2)));
          GPIOx->DRV0 = GPIOx->DRV0 | (GPIO_InitStruct->GPIO_DriveCurrent << (i * 2));
          GPIOx->PUL0 = GPIOx->PUL0 & (~(3 << (i * 2)));
          GPIOx->PUL0 = GPIOx->PUL0 | (GPIO_InitStruct->GPIO_PuPd << (i * 2));
          break;
        case 16 ... 23:
          if((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT))
          {
            GPIOx->CFG2 = GPIOx->CFG2 & (~(7 << ((i - 16) * 4)));
            GPIOx->CFG2 = GPIOx->CFG2 | (GPIO_InitStruct->GPIO_Mode << ((i - 16) * 4));
          }
          GPIOx->DRV1 = GPIOx->DRV1 & (~(3 << ((i - 16) * 2)));
          GPIOx->DRV1 = GPIOx->DRV1 | (GPIO_InitStruct->GPIO_DriveCurrent << ((i - 16) * 2));
          GPIOx->PUL1 = GPIOx->PUL1 & (~(3 << ((i - 16) * 2)));
          GPIOx->PUL1 = GPIOx->PUL1 | (GPIO_InitStruct->GPIO_PuPd << ((i - 16) * 2));
          break;
        case 24 ... 31:
          if((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT))
          {
            GPIOx->CFG3 = GPIOx->CFG3 & (~(7 << ((i - 24) * 4)));
            GPIOx->CFG3 = GPIOx->CFG3 | (GPIO_InitStruct->GPIO_Mode << ((i - 24) * 4));
          }
          GPIOx->DRV1 = GPIOx->DRV1 & (~(3 << ((i - 16) * 2)));
          GPIOx->DRV1 = GPIOx->DRV1 | (GPIO_InitStruct->GPIO_DriveCurrent << ((i - 16) * 2));
          GPIOx->PUL1 = GPIOx->PUL1 & (~(3 << ((i - 16) * 2)));
          GPIOx->PUL1 = GPIOx->PUL1 | (GPIO_InitStruct->GPIO_PuPd << ((i - 16) * 2));
          break;
        default:
          break;
      }
    }
  }
}

void GPIO_WriteBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin, BitAction BitVal)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if((GPIO_Pin & (1 << i)) != 0)
    {
      GPIOx->DATA = GPIOx->DATA & (~(1 << i));
      GPIOx->DATA = GPIOx->DATA | (BitVal << i);
    }
  }
}

void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
  GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET);
}

void GPIO_ResetBits(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
  GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET);
}

void GPIO_AF_Remap(GPIO_TypeDef * GPIOx, uint32_t GPIO_PinSourceNum, uint32_t GPIO_AF_FUN)
{
  switch(GPIO_PinSourceNum)
  {
    case 0 ... 7:
      GPIOx->CFG0 = GPIOx->CFG0 & (~(7 << (GPIO_PinSourceNum * 4)));
      GPIOx->CFG0 = GPIOx->CFG0 | (GPIO_AF_FUN);
      break;
    case 8 ... 15:
      GPIOx->CFG1 = GPIOx->CFG1 & (~(7 << ((GPIO_PinSourceNum - 8) * 4)));
      GPIOx->CFG1 = GPIOx->CFG1 | (GPIO_AF_FUN);
      break;
    case 16 ... 23:
      GPIOx->CFG2 = GPIOx->CFG2 & (~(7 << ((GPIO_PinSourceNum - 16) * 4)));
      GPIOx->CFG2 = GPIOx->CFG2 | (GPIO_AF_FUN);
      break;
    case 24 ... 31:
      GPIOx->CFG3 = GPIOx->CFG3 & (~(7 << ((GPIO_PinSourceNum - 23) * 4)));
      GPIOx->CFG3 = GPIOx->CFG3 | (GPIO_AF_FUN);
      break;
    default:
      break;
  }
}
