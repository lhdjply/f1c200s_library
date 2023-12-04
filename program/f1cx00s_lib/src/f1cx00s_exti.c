#include "f1cx00s_exti.h"

void EXTI_Init(EXTI_TypeDef * EXTIx, EXTI_InitTypeDef * EXTI_InitStruct)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if(((EXTI_InitStruct->EXTI_Line) & (1 << i)) != 0)
    {
      switch(i)
      {
        case 0 ... 7:
          EXTIx->CFG0 = EXTIx->CFG0 & (~(0x0f << (i * 4)));
          EXTIx->CFG0 = EXTIx->CFG0 | (EXTI_InitStruct->EXTI_Trigger << (i * 4));
          EXTIx->CTRL = EXTIx->CTRL & (~(1 << i));
          EXTIx->CTRL = EXTIx->CTRL | (EXTI_InitStruct->EXTI_LineCmd << i);
          break;
        case 8 ... 15:
          EXTIx->CFG1 = EXTIx->CFG1 & (~(0x0f << ((i - 8) * 4)));
          EXTIx->CFG1 = EXTIx->CFG1 | (EXTI_InitStruct->EXTI_Trigger << ((i - 8) * 4));
          EXTIx->CTRL = EXTIx->CTRL & (~(1 << i));
          EXTIx->CTRL = EXTIx->CTRL | (EXTI_InitStruct->EXTI_LineCmd << i);
          break;
        case 16 ... 23:
          EXTIx->CFG2 = EXTIx->CFG2 & (~(0x0f << ((i - 16) * 4)));
          EXTIx->CFG2 = EXTIx->CFG2 | (EXTI_InitStruct->EXTI_Trigger << ((i - 16) * 4));
          EXTIx->CTRL = EXTIx->CTRL & (~(1 << i));
          EXTIx->CTRL = EXTIx->CTRL | (EXTI_InitStruct->EXTI_LineCmd << i);
          break;
        case 24 ... 31:
          EXTIx->CFG3 = EXTIx->CFG3 & (~(0x0f << ((i - 24) * 4)));
          EXTIx->CFG3 = EXTIx->CFG3 | (EXTI_InitStruct->EXTI_Trigger << ((i - 16) * 4));
          EXTIx->CTRL = EXTIx->CTRL & (~(1 << i));
          EXTIx->CTRL = EXTIx->CTRL | (EXTI_InitStruct->EXTI_LineCmd << i);
          break;
        default:
          break;
      }
    }
  }
}

FlagStatus EXTI_GetFlagStatus(EXTI_TypeDef * EXTIx, uint32_t EXTI_Line)
{
  if(EXTIx->STA && EXTI_Line != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

void EXTI_ClearFlag(EXTI_TypeDef * EXTIx, uint32_t EXTI_Line)
{
  EXTIx->STA = EXTI_Line;
}
