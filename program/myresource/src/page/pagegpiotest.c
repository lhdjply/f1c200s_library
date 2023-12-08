// UTF-8
#include "myresource.h"

Pagegpiotest pagegpiotest;
extern PageDemoSelect pageDemoSelect;

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    BUZZER = 0; // GPIO_ResetBits(GPIOE, GPIO_Pin_4);
    lv_obj_del(pagegpiotest.view);
    lv_obj_clear_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

static void Switch_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED)
  {
    if(lv_obj_has_state(target, LV_STATE_CHECKED))
    {
      BUZZER = 1; // GPIO_SetBits(GPIOE, GPIO_Pin_4);
    }
    else
    {
      BUZZER = 0; // GPIO_ResetBits(GPIOE, GPIO_Pin_4);
    }
  }
}

void Pagegpiotest_Init(void)
{
  pagegpiotest.view = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(pagegpiotest.view);
  lv_obj_set_size(pagegpiotest.view, LV_PCT(100), LV_PCT(100));

  pagegpiotest.back_btn = lv_btn_create(pagegpiotest.view);
  lv_obj_set_size(pagegpiotest.back_btn, 120, 50);
  lv_obj_align(pagegpiotest.back_btn, LV_ALIGN_TOP_LEFT, LV_PCT(2), LV_PCT(2));
  lv_obj_add_event_cb(pagegpiotest.back_btn, Back_Button_Event, LV_EVENT_CLICKED, NULL);

  pagegpiotest.back_btn_label = lv_label_create(pagegpiotest.back_btn);
  lv_obj_center(pagegpiotest.back_btn_label);
  lv_label_set_text(pagegpiotest.back_btn_label, "back");

  pagegpiotest.buzzer_label = lv_label_create(pagegpiotest.view);
  lv_obj_center(pagegpiotest.buzzer_label);
  lv_label_set_text(pagegpiotest.buzzer_label, "Control buzzer");

  pagegpiotest.buzzer_swicth = lv_switch_create(pagegpiotest.view);
  lv_obj_set_size(pagegpiotest.buzzer_swicth, 150, 50);
  lv_obj_align_to(pagegpiotest.buzzer_swicth,
                  pagegpiotest.buzzer_label,
                  LV_ALIGN_OUT_BOTTOM_MID,
                  0,
                  0);
  lv_obj_add_event_cb(pagegpiotest.buzzer_swicth, Switch_Event, LV_EVENT_VALUE_CHANGED, NULL);
}
