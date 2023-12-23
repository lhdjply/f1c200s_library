#ifndef PAGEPWMTEST_H
#define PAGEPWMTEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;
  lv_obj_t * brightness_label;
  lv_obj_t * brightness_slider;
} Pagepwmtest;

void Pagepwmtest_Init(void);

#endif
