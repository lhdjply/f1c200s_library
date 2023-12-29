// UTF-8
#include "myresource.h"

Pagei2ctest pagei2ctest;

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_obj_del(pagei2ctest.view);
    lv_obj_clear_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

void Pagei2ctest_Init(void)
{
  pagei2ctest.view = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(pagei2ctest.view);
  lv_obj_set_size(pagei2ctest.view, LV_PCT(100), LV_PCT(100));

  pagei2ctest.back_btn = lv_btn_create(pagei2ctest.view);
  lv_obj_set_size(pagei2ctest.back_btn, 120, 50);
  lv_obj_align(pagei2ctest.back_btn, LV_ALIGN_TOP_LEFT, LV_PCT(2), LV_PCT(2));
  lv_obj_add_event_cb(pagei2ctest.back_btn, Back_Button_Event, LV_EVENT_CLICKED, NULL);

  pagei2ctest.back_btn_label = lv_label_create(pagei2ctest.back_btn);
  lv_obj_center(pagei2ctest.back_btn_label);
  lv_label_set_text(pagei2ctest.back_btn_label, "back");

  pagei2ctest.tip = lv_label_create(pagei2ctest.view);
  lv_obj_center(pagei2ctest.tip);
  lv_label_set_text(pagei2ctest.tip, "Please see the hardware/gt911.c");
}
