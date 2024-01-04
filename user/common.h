#ifndef USER_COMMON_H_
#define USER_COMMON_H_

#include "rtthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "sdcard.h"
#include "w25qxx.h"
#include "lcd.h"
#include "wdog.h"
#include "myresource.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_port_fs.h"
#include "usbh_msc_config.h"
#include "usbd_msc_config.h"
#include "ff.h"

#define SET_RX_Len 500
#define SET_TX_Len 500

#define TEST_USB_MODE_HOST 0
#define TEST_USB_MODE_DEVICE 1
#define TEST_USB_MODE TEST_USB_MODE_HOST

typedef struct
{
  uint8_t lcd_brightness;
  FRESULT sd_res;
  uint8_t sd_write_ok_flag;
#if TEST_USB_MODE==TEST_USB_MODE_HOST
  FRESULT usb_res;
  uint8_t usb_write_ok_flag;
#endif
} DATA;

typedef struct
{
  uint32_t count;
  uint32_t len;
  uint32_t time;
  uint8_t receiving_flag;
  uint8_t receive_complete_flag;
  uint8_t RXD_BUF[SET_RX_Len];
  uint8_t TXD_BUF[SET_TX_Len];
} UART_DATA; // 串口数据

#endif /* USER_COMMON_H_ */
