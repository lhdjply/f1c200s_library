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
#include "usbh_core.h"
#include "usbh_msc.h"
#include "usb_musb_reg.h"

#define SET_RX_Len 500
#define SET_TX_Len 500

typedef struct
{
  rt_sem_t sem;
  rt_mutex_t mutex;
  uint32_t count;
  uint32_t len;
  uint32_t time;
  uint8_t flag;
  uint8_t RXD_BUF[SET_RX_Len];
  uint8_t TXD_BUF[SET_TX_Len];
} UART_DATA; // 串口数据

#endif /* USER_COMMON_H_ */
