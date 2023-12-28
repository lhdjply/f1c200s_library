#include "task.h"

DATA mydata;
rt_sem_t usbh_msc_test_sem;

void BUZZER_task(void * p)
{
  BUZZER_Init();
  while(1)
  {
    delay_ms(500);
  }
}

void UART_task(void * p)
{
  UART2_Init();
  My_Printf("F1C200S demo test!\r\n");
  My_Printf("---------------------------\r\n");
}

void USB_task(void * p)
{
  const char * usbh_msc_test_text = "This the usbh msc test demo!";
  UINT bw;
  FATFS * fs;
  FIL * file;
  usbh_msc_test_sem = rt_sem_create("usbh_msc_test_sem", 0, RT_IPC_FLAG_FIFO);
  usbh_initialize();
  while(1)
  {
    rt_sem_take(usbh_msc_test_sem, RT_WAITING_FOREVER);
    fs = (FATFS *)rt_malloc(sizeof(FATFS));
    file = (FIL *)rt_malloc(sizeof(FIL));
    f_mount(fs, "1:/", 0);
    f_open(file, "1:/usbh_msc_test.txt", FA_CREATE_ALWAYS | FA_WRITE);
    f_write(file, usbh_msc_test_text, strlen(usbh_msc_test_text), &bw);
    f_close(file);
    f_mount(NULL, "1:/", 0);
    rt_free(fs);
    rt_free(file);
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
