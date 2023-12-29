#ifndef PAGESDIOTEST_H
#define PAGESDIOTEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;

  lv_obj_t * sdio_write_file_btn;
  lv_obj_t * sdio_write_file_btn_label;
  lv_obj_t * sdio_write_file_tips;

  lv_timer_t * timer;
} Pagesdiotest;

void Pagesdiotest_Init(void);

#endif
