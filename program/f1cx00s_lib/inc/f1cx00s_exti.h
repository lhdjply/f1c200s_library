#ifndef __F1CX00S_EXTI__H
#define __F1CX00S_EXTI__H

#include "f1cx00s.h"

#define EXTI_Line_0 ((uint32_t)0x00000001)
#define EXTI_Line_1 ((uint32_t)0x00000002)
#define EXTI_Line_2 ((uint32_t)0x00000004)
#define EXTI_Line_3 ((uint32_t)0x00000008)
#define EXTI_Line_4 ((uint32_t)0x00000010)
#define EXTI_Line_5 ((uint32_t)0x00000020)
#define EXTI_Line_6 ((uint32_t)0x00000040)
#define EXTI_Line_7 ((uint32_t)0x00000080)
#define EXTI_Line_8 ((uint32_t)0x00000100)
#define EXTI_Line_9 ((uint32_t)0x00000200)
#define EXTI_Line_10 ((uint32_t)0x00000400)
#define EXTI_Line_11 ((uint32_t)0x00000800)
#define EXTI_Line_12 ((uint32_t)0x00001000)
#define EXTI_Line_13 ((uint32_t)0x00002000)
#define EXTI_Line_14 ((uint32_t)0x00004000)
#define EXTI_Line_15 ((uint32_t)0x00008000)
#define EXTI_Line_16 ((uint32_t)0x00010000)
#define EXTI_Line_17 ((uint32_t)0x00020000)
#define EXTI_Line_18 ((uint32_t)0x00040000)
#define EXTI_Line_19 ((uint32_t)0x00080000)
#define EXTI_Line_20 ((uint32_t)0x00100000)
#define EXTI_Line_21 ((uint32_t)0x00200000)
#define EXTI_Line_22 ((uint32_t)0x00400000)
#define EXTI_Line_23 ((uint32_t)0x00800000)
#define EXTI_Line_24 ((uint32_t)0x01000000)
#define EXTI_Line_25 ((uint32_t)0x02000000)
#define EXTI_Line_26 ((uint32_t)0x04000000)
#define EXTI_Line_27 ((uint32_t)0x08000000)
#define EXTI_Line_28 ((uint32_t)0x10000000)
#define EXTI_Line_29 ((uint32_t)0x20000000)
#define EXTI_Line_30 ((uint32_t)0x40000000)
#define EXTI_Line_31 ((uint32_t)0x80000000)

typedef enum
{
  EXTI_Trigger_Rising = 0,
  EXTI_Trigger_Falling,
  EXTI_Trigger_HighLevel,
  EXTI_Trigger_LowLevel,
  EXTI_Trigger_Rising_Falling,
} EXTITrigger_TypeDef;

typedef struct
{
  uint32_t EXTI_Line;
  EXTITrigger_TypeDef EXTI_Trigger;
  FunctionalState EXTI_LineCmd;
} EXTI_InitTypeDef;

void EXTI_Init(EXTI_TypeDef * EXTIx, EXTI_InitTypeDef * EXTI_InitStruct);
FlagStatus EXTI_GetFlagStatus(EXTI_TypeDef * EXTIx, uint32_t EXTI_Line);
void EXTI_ClearFlag(EXTI_TypeDef * EXTIx, uint32_t EXTI_Line);

#endif
