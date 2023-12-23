#include "task.h"

DATA mydata;

void BUZZER_task(void * p)
{
  BUZZER_Init();
  while(1)
  {
    delay_ms(500);
  }
}

void LCD_task(void * p)
{
  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();
  mydata.lcd_brightness = 100;
  LCD_SetBrightness(mydata.lcd_brightness);
  PageDemoSelect_Init();
  while(1)
  {
    lv_task_handler();
    delay_ms(10);
  }
}

void WDOG_task(void * p)
{
  WDOG_Config();
  while(1)
  {
    WDOG_Feed();
    delay_ms(500);
  }
}
