#include "wdog.h"

void WDOG_Config(void)
{
  WDOG_Set_Mode(WDOG_RST_MODE);
  WDOG_Set_Value(1);//喂狗周期为1s
  WDOG_Enable();
  WDOG_Feed();
}
