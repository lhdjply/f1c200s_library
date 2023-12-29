#ifndef PAGEUSBTEST_H
#define PAGEUSBTEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;

  lv_obj_t * usbh_msc_connect_state;
  lv_obj_t * usbh_msc_test_btn;
  lv_obj_t * usbh_msc_test_label;
  lv_obj_t * usbh_msc_write_file_tips;

  lv_timer_t * timer;
} Pageusbtest;

void Pageusbtest_Init(void);

#endif
