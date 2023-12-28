// UTF-8
#include "myresource.h"

Pagepwmtest pagepwmtest;
extern DATA mydata;

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_obj_del(pagepwmtest.view);
    lv_obj_clear_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

static void Slider_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_VALUE_CHANGED)
  {
    mydata.lcd_brightness = lv_slider_get_value(pagepwmtest.brightness_slider);
    LCD_SetBrightness(mydata.lcd_brightness);
  }
}

void Pagepwmtest_Init(void)
{
  pagepwmtest.view = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(pagepwmtest.view);
  lv_obj_set_size(pagepwmtest.view, LV_PCT(100), LV_PCT(100));

  pagepwmtest.back_btn = lv_btn_create(pagepwmtest.view);
  lv_obj_set_size(pagepwmtest.back_btn, 120, 50);
  lv_obj_align(pagepwmtest.back_btn, LV_ALIGN_TOP_LEFT, LV_PCT(2), LV_PCT(2));
  lv_obj_add_event_cb(pagepwmtest.back_btn, Back_Button_Event, LV_EVENT_CLICKED, NULL);

  pagepwmtest.back_btn_label = lv_label_create(pagepwmtest.back_btn);
  lv_obj_center(pagepwmtest.back_btn_label);
  lv_label_set_text(pagepwmtest.back_btn_label, "back");

  pagepwmtest.brightness_label = lv_label_create(pagepwmtest.view);
  lv_obj_center(pagepwmtest.brightness_label);
  lv_label_set_text(pagepwmtest.brightness_label, "Control lcd brightness");

  pagepwmtest.brightness_slider = lv_slider_create(pagepwmtest.view);
  lv_slider_set_range(pagepwmtest.brightness_slider, 5, 100);
  lv_slider_set_value(pagepwmtest.brightness_slider,
                      mydata.lcd_brightness,
                      LV_ANIM_OFF);
  lv_obj_align_to(pagepwmtest.brightness_slider,
                  pagepwmtest.brightness_label,
                  LV_ALIGN_OUT_BOTTOM_MID,
                  0,
                  0);
  lv_obj_add_event_cb(pagepwmtest.brightness_slider, Slider_Event, LV_EVENT_VALUE_CHANGED, NULL);
}
