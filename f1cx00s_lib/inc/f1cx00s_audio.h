#ifndef __F1CX00S_AUDIO__H
#define __F1CX00S_AUDIO__H

#include "f1cx00s.h"

typedef enum
{
  ADC_CHANNEL_FMINL = 0,
  ADC_CHANNEL_FMINR,
  ADC_CHANNEL_LINL
} ADC_CHANNEL;

uint32_t AUDIO_READ_ADC(ADC_CHANNEL channel);
void AUDIO_ADC_Init(void);

#endif
