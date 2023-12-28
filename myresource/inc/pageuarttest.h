#ifndef PAGEUARTTEST_H
#define PAGEUARTTEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;
  lv_obj_t * clear_btn;
  lv_obj_t * clear_btn_label;
  lv_obj_t * receive_label;
  lv_obj_t * receive_data;
  lv_obj_t * send_label;
  lv_obj_t * send_data;

  lv_obj_t * keyboard;

  lv_timer_t * timer;
} Pageuarttest;

void Pageuarttest_Init(void);

#endif
