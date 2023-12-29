#ifndef PAGESPITEST_H
#define PAGESPITEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;

  lv_obj_t * write_label;
  lv_obj_t * write_btn;
  lv_obj_t * write_btn_label;
  lv_obj_t * read_label;
  lv_obj_t * read_btn;
  lv_obj_t * read_btn_label;

  lv_obj_t * keyboard;
} Pagespitest;

void Pagespitest_Init(void);

#endif
