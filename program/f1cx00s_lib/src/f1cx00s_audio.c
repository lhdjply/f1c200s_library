#include "f1cx00s_audio.h"
#include "delay.h"

uint32_t AUDIO_READ_ADC(ADC_CHANNEL channel)
{
  uint32_t mixerReg = AUDIO->ADC_MIXER_CTRL & ~(0x1f << 8);
  switch(channel)
  {
    case ADC_CHANNEL_FMINL:
      AUDIO->ADC_MIXER_CTRL = mixerReg | (1 << 12);
      break;
    case ADC_CHANNEL_FMINR:
      AUDIO->ADC_MIXER_CTRL = mixerReg | (1 << 11);
      break;
    case ADC_CHANNEL_LINL:
      AUDIO->ADC_MIXER_CTRL = mixerReg | (1 << 10);
      break;
    default:
      break;
  }
  const uint32_t WAIT_STABLE = 400;
  delay_us(WAIT_STABLE); // wait for internal filter to be stable

  // FIFO flush
  AUDIO->ADC_FIFOC |= (1 << 0);
  while(((AUDIO->ADC_FIFOS >> 23) & 1) == 0)
  {
  }

  // by default, 0V = -24000 and VRA = 0.
  // make 0V = 0 and vreference = 65535.
  uint32_t val = (AUDIO->ADC_RXDATA >> 16) + 0x00007fff;
  return val;
}

void AUDIO_ADC_Init(void)
{
  CCU_BUS2_GatingClockCmd(CCU_BUS2Gating_AUDIO_CODEC, ENABLE);
  CCU->AUDIO_CODEC_CLK = 0x1 << 31;
  CCU->PLL_AUDIO_CTRL |= (0x1 << 31);
  CCU_BUS2_GatingResetCmd(CCU_BUS2Gating_AUDIO_CODEC, ENABLE);

  uint32_t regVal =
    (0 << 29)    // 48kHz，make higher for better speed
    | (1 << 28)  // digital enable
    | (0 << 24)  // mode 0
    | (0 << 17)  // delay after enable
    | (0 << 16)  // delay function
    | (0xf << 8) // default
    | (0 << 7)   // stereo
    | (0 << 6);  // 16-bit
  AUDIO->ADC_FIFOC = regVal;

  regVal =
    (1 << 31)   // analog enable
    | (3 << 24) // mic gain
    | (0 << 21) // linein gain
    | (3 << 16) // adc gain = 0
    | (1 << 14) // COS slop time
    | (0 << 8)  // all mute
    | (4 << 0); // default
  AUDIO->ADC_MIXER_CTRL = regVal;
}