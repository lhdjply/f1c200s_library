#ifndef __F1CX00S_PWM__H
#define __F1CX00S_PWM__H

#include "f1cx00s.h"

#define PWM_CHANNEL_0 0
#define PWM_CHANNEL_1 1

typedef struct
{
  uint8_t channel;
  uint8_t duty_cycle;
  uint32_t period;
  uint8_t polarity;
} PWM_InitTypeDef;

void PWM_Init(PWM_InitTypeDef * PWM_InitStruct);
void PWM_Cmd(uint8_t channel, FunctionalState NewState);
void PWM_Set_Duty(uint8_t channel, uint8_t duty);

#endif // !__F1CX00S_PWM__H
