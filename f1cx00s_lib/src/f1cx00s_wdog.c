#include "f1cx00s_wdog.h"

static const uint8_t timeout_map[] = {0, 1, 2, 3, 4, 5, 6, 8, 10, 12, 14, 16};

void WDOG_Set_Mode(uint8_t mode)
{
  WDOG->CFG = mode & 0x03;
}

void WDOG_Feed(void)
{
  WDOG->CTRL = ((0x0A57 << 1) | 0x01);
}

void WDOG_Enable(void)
{
  WDOG->MODE |= 0x01;
}

void WDOG_Set_Value(uint8_t value)
{
  uint8_t i = 0, timeout = value;

  if(timeout > 16)
  {
    timeout = 16;
  }

  for(i = timeout / 2; i < 12; i++)
  {
    if(timeout <= timeout_map[i])
    {
      break;
    }
  }
  WDOG->MODE = (i & 0x0f) << 4;
}

uint8_t WDOG_Get_Value(void)
{
  return timeout_map[((WDOG->MODE >> 4) & 0xf)];
}
