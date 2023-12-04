#include "f1cx00s_pwm.h"

#define PWM_BIT(x, bit) ((1 << bit) << ((x)*15))

static const uint32_t prescaler_table[] =
{
  120,
  180,
  240,
  360,
  480,
  0,
  0,
  0,
  12000,
  24000,
  36000,
  48000,
  72000,
  0,
  0,
  0,
};
static volatile uint32_t * channel_period;
static void PWM_Config(PWM_InitTypeDef * PWM_InitStruct)
{
  uint64_t rate = 24000000; // hosc =24MHz //clk_get_rate(pwm->clk);
  uint64_t div;
  uint32_t prd, dty, gate;
  uint32_t prescaler = 0;
  uint32_t ctrl;

  if(PWM_InitStruct->channel == PWM_CHANNEL_0)
  {
    channel_period = &(PWM->CH0_PERIOD);
  }
  else
  {
    channel_period = &(PWM->CH1_PERIOD);
  }

  prescaler = 0xf;
  div = rate * PWM_InitStruct->period + 1000000000 / 2;
  div = div / 1000000000;
  if(div - 1 > 0xffff)
  {
    prescaler = 0;
  }

  if(prescaler == 0)
  {
    for(prescaler = 0; prescaler < 0xf; prescaler++)
    {
      if(!prescaler_table[prescaler])
        continue;
      div = rate;
      div = div / prescaler_table[prescaler];
      div = div * PWM_InitStruct->period;
      div = div / 1000000000;
      if(div - 1 <= 0xffff)
        break;
    }
    if(div - 1 > 0xffff)
    {
      return;
    }
  }
  prd = div;
  div *= PWM_InitStruct->duty_cycle;
  div = div / 100; // div / period;
  dty = div;

  gate = (PWM->CTRL & PWM_BIT(PWM_InitStruct->channel, 6)) ? 1 : 0;
  if(gate)
  {
    PWM->CTRL &= ~PWM_BIT(PWM_InitStruct->channel, 6);
  }
  ctrl = PWM->CTRL;
  ctrl &= ~(0xf << (PWM_InitStruct->channel * 15));
  ctrl |= (prescaler << (PWM_InitStruct->channel * 15));
  PWM->CTRL = ctrl;
  *channel_period = ((prd - 1) << 16) | (dty & 0xffff);
  if(gate)
  {
    PWM->CTRL |= PWM_BIT(PWM_InitStruct->channel, 6);
  }
  if(PWM_InitStruct->polarity)
  {
    PWM->CTRL |= PWM_BIT(PWM_InitStruct->channel, 5);
  }
  else
  {
    PWM->CTRL &= ~PWM_BIT(PWM_InitStruct->channel, 5);
  }
}

void PWM_Init(PWM_InitTypeDef * PWM_InitStruct)
{
  PWM->CTRL = PWM->CTRL & ~(0x3fff << (PWM_InitStruct->channel * 15));
  if(PWM_InitStruct->channel == PWM_CHANNEL_0)
  {
    PWM->CH0_PERIOD = 0;
  }
  else
  {
    PWM->CH1_PERIOD = 0;
  }
  PWM_Config(PWM_InitStruct);
}

void PWM_Cmd(uint8_t channel, FunctionalState NewState)
{
  uint32_t ctrl;

  ctrl = PWM->CTRL;
  if(NewState == ENABLE)
  {
    ctrl |= PWM_BIT(channel, 4);
    ctrl |= PWM_BIT(channel, 6);
  }
  else
  {
    ctrl &= ~PWM_BIT(channel, 4);
    ctrl &= ~PWM_BIT(channel, 6);
  }
  PWM->CTRL = ctrl;
}

void PWM_Set_Duty(uint8_t channel, uint8_t duty)
{
  uint32_t prd, duty_temp;
  if(channel == PWM_CHANNEL_0)
  {
    prd = (PWM->CH0_PERIOD >> 16) + 1;
    duty_temp = prd * duty / 100;
    PWM->CH0_PERIOD = ((prd - 1) << 16) | (duty_temp & 0xffff);
  }
  else
  {
    prd = (PWM->CH1_PERIOD >> 16) + 1;
    duty_temp = prd * duty / 100;
    PWM->CH1_PERIOD = ((prd - 1) << 16) | (duty_temp & 0xffff);
  }
}