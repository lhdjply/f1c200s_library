#ifndef PAGEI2CTEST_H
#define PAGEI2CTEST_H

#include "lvgl/lvgl.h"

typedef struct
{
  lv_obj_t * view;
  lv_obj_t * back_btn;
  lv_obj_t * back_btn_label;
  lv_obj_t * real_time;

  lv_obj_t * set_date_btn;
  lv_obj_t * set_date_btn_label;

  lv_obj_t * set_time_btn;
  lv_obj_t * set_time_btn_label;

  lv_obj_t * date_msgbox;
  lv_obj_t * date_msgbox_btn_ok;
  lv_obj_t * date_msgbox_btn_ok_text;
  lv_obj_t * date_msgbox_btn_no;
  lv_obj_t * date_msgbox_btn_no_text;
  lv_obj_t * date_year_roller;
  lv_obj_t * date_month_roller;
  lv_obj_t * date_day_roller;
  lv_obj_t * time_msgbox;
  lv_obj_t * time_msgbox_btn_ok;
  lv_obj_t * time_msgbox_btn_ok_text;
  lv_obj_t * time_msgbox_btn_no;
  lv_obj_t * time_msgbox_btn_no_text;
  lv_obj_t * time_hour_roller;
  lv_obj_t * time_minute_roller;
  lv_obj_t * time_second_roller;

  lv_timer_t * timer;
} Pagei2ctest;

void Pagei2ctest_Init(void);

#endif
