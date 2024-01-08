#include "task.h"

DATA mydata;
rt_sem_t rtc_settime_sem, sdio_test_sem, usbh_msc_test_sem;

void LED_task(void * p)
{
  LED_Init();
  while(1)
  {
    LED = !LED;
    delay_ms(500);
  }
}

void BUZZER_task(void * p)
{
  BUZZER_Init();
}

void W25QXX_task(void * p)
{
  W25QXX_Init();
}

void RTC_task(void * p)
{
  rt_err_t err;
  rtc_settime_sem = rt_sem_create("rtc_settime_sem", 0, RT_IPC_FLAG_FIFO);
  SD3031_Init();
  Get_SD3031_Time(&mydata.real_time);
  while(1)
  {
    err = rt_sem_take(rtc_settime_sem, 300);
    if(err == RT_EOK)
    {
      Set_SD3031_Time(&mydata.real_time);
    }
    else
    {
      Get_SD3031_Time(&mydata.real_time);
    }
  }
}

void UART_task(void * p)
{
  UART1_Init();
  My_Printf("F1C200S demo test!\r\n");
  My_Printf("---------------------------\r\n");
}

void SDIO_task(void * p)
{
  const char * sdio_test_text = "This the sdio test demo!";
  UINT bw;
  FATFS * fs;
  FIL * file;
  sdio_test_sem = rt_sem_create("sdio_test_sem", 0, RT_IPC_FLAG_FIFO);
  SD_Init(SDIO0);
  while(1)
  {
    rt_sem_take(sdio_test_sem, RT_WAITING_FOREVER);
    fs = (FATFS *)rt_malloc(sizeof(FATFS));
    file = (FIL *)rt_malloc(sizeof(FIL));
    mydata.sd_res = f_mount(fs, "0:/", 0);
    if(mydata.sd_res == FR_OK)
    {
      mydata.sd_res = f_open(file, "0:/sdio_test.txt", FA_CREATE_ALWAYS | FA_WRITE);
      if(mydata.sd_res == FR_OK)
      {
        mydata.sd_res = f_write(file, sdio_test_text, strlen(sdio_test_text), &bw);
        f_close(file);
        if(mydata.sd_res == FR_OK)
        {
          mydata.sd_write_ok_flag = 1;
        }
      }
      else
      {
        f_close(file);
      }
    }
    f_mount(NULL, "0:/", 0);
    rt_free(fs);
    rt_free(file);
  }
}

void USB_task(void * p)
{
  delay_ms(1000);
#if TEST_USB_MODE == TEST_USB_MODE_HOST
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
    mydata.usb_res =  f_mount(fs, "1:/", 0);
    if(mydata.usb_res == FR_OK)
    {
      mydata.usb_res = f_open(file, "1:/usbh_msc_test.txt", FA_CREATE_ALWAYS | FA_WRITE);
      if(mydata.usb_res == FR_OK)
      {
        mydata.usb_res = f_write(file, usbh_msc_test_text, strlen(usbh_msc_test_text), &bw);
        f_close(file);
        if(mydata.usb_res == FR_OK)
        {
          mydata.usb_write_ok_flag = 1;
        }
      }
      else
      {
        f_close(file);
      }
    }
    f_mount(NULL, "1:/", 0);
    rt_free(fs);
    rt_free(file);
  }
#else
  usbd_msc_init();
#endif
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
