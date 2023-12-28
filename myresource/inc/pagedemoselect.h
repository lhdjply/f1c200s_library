#ifndef PAGEDEMOSELECT_H
#define PAGEDEMOSELECT_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;

  lv_obj_t * lv_demos;

  lv_obj_t * benchmark_btn;
  lv_obj_t * benchmark_label;

  lv_obj_t * keypad_encoder_btn;
  lv_obj_t * keypad_encoder_label;

  lv_obj_t * music_btn;
  lv_obj_t * music_label;

  lv_obj_t * stress_btn;
  lv_obj_t * stress_label;

  lv_obj_t * widgets_btn;
  lv_obj_t * widgets_label;

  lv_obj_t * library_test;

  lv_obj_t * gpio_test_btn;
  lv_obj_t * gpio_test_label;

  lv_obj_t * i2c_test_btn;
  lv_obj_t * i2c_test_label;

  lv_obj_t * pwm_test_btn;
  lv_obj_t * pwm_test_label;

  lv_obj_t * sdio_test_btn;
  lv_obj_t * sdio_test_label;

  lv_obj_t * spi_test_btn;
  lv_obj_t * spi_test_label;

  lv_obj_t * uart_test_btn;
  lv_obj_t * uart_test_label;

  lv_obj_t * usb_test_btn;
  lv_obj_t * usb_test_label;
} PageDemoSelect;

void PageDemoSelect_Init(void);

#endif
