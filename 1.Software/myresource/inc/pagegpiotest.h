#ifndef PAGEGPIOTEST_H
#define PAGEGPIOTEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;
  lv_obj_t * buzzer_label;
  lv_obj_t * buzzer_swicth;
} Pagegpiotest;

void Pagegpiotest_Init(void);

#endif
