#ifndef PAGESDIOTEST_H
#define PAGESDIOTEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;

  lv_obj_t * sdio_test_btn;
  lv_obj_t * sdio_test_label;
} Pagesdiotest;

void Pagesdiotest_Init(void);

#endif
