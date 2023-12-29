#ifndef PAGEI2CTEST_H
#define PAGEI2CTEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;
  lv_obj_t * tip;
} Pagei2ctest;

void Pagei2ctest_Init(void);

#endif
