#ifndef PAGEMAIN_H
#define PAGEMAIN_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * gpio_test_btn;
  lv_obj_t * i2c_test_btn;
  lv_obj_t * pwm_test_btn;
  lv_obj_t * sdio_test_btn;
  lv_obj_t * spi_test_btn;
  lv_obj_t * uart_test_btn;
  lv_obj_t * usb_test_btn;
} PageMain;

void PageMain_Init(void);

#endif
