// UTF-8
#include "myresource.h"

Pageuarttest pageuarttest;
extern UART_DATA uart_Data;

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_timer_delete(pageuarttest.timer);
    lv_obj_delete(pageuarttest.view);
    lv_obj_remove_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

static void Clear_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_textarea_set_text(pageuarttest.receive_data, "");
  }
}

static void Edit_Event(lv_event_t * e)
{
  lv_obj_t * target = lv_event_get_target(e);
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_FOCUSED)
  {
    if(target == pageuarttest.receive_data)
    {
      lv_obj_remove_state(target, LV_STATE_FOCUSED);
    }
    else if(target == pageuarttest.send_data)
    {
      lv_obj_set_height(pageuarttest.view,  LV_PCT(52));
      lv_obj_set_height(pageuarttest.receive_data, LV_PCT(77));
      lv_obj_set_height(pageuarttest.send_data, LV_PCT(58));
      pageuarttest.keyboard = lv_keyboard_create(lv_scr_act());
      lv_obj_set_size(pageuarttest.keyboard, LV_PCT(100), LV_PCT(48));
      lv_keyboard_set_mode(pageuarttest.keyboard, LV_KEYBOARD_MODE_TEXT_LOWER);
      lv_keyboard_set_textarea(pageuarttest.keyboard, target);
      lv_obj_scroll_to_view_recursive(target, LV_ANIM_ON);
    }
  }
  else if(code == LV_EVENT_DEFOCUSED || code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
  {
    if(target == pageuarttest.send_data)
    {
      if(code == LV_EVENT_READY)
      {
        My_Printf("%s", lv_textarea_get_text(target));
      }
      lv_obj_delete(pageuarttest.keyboard);
      lv_indev_wait_release(lv_indev_active());
      lv_indev_reset(lv_indev_active(), target);
      lv_obj_set_height(pageuarttest.view, LV_PCT(100));
      lv_obj_set_height(pageuarttest.receive_data, LV_PCT(40));
      lv_obj_set_height(pageuarttest.send_data, LV_PCT(30));
      lv_obj_remove_state(target, LV_STATE_FOCUSED);
    }
  }
}

static void my_timer(lv_timer_t * timer)
{
  if(uart_Data.receive_complete_flag == 1)
  {
    lv_textarea_add_text(pageuarttest.receive_data, (char *)uart_Data.RXD_BUF);
    uart_Data.receive_complete_flag = 0;
  }
}

void Pageuarttest_Init(void)
{
  pageuarttest.view = lv_obj_create(lv_screen_active());
  lv_obj_remove_style_all(pageuarttest.view);
  lv_obj_set_size(pageuarttest.view, LV_PCT(100), LV_PCT(100));

  pageuarttest.back_btn = lv_button_create(pageuarttest.view);
  lv_obj_set_size(pageuarttest.back_btn, 120, 50);
  lv_obj_align(pageuarttest.back_btn, LV_ALIGN_TOP_LEFT, LV_PCT(2), LV_PCT(2));
  lv_obj_add_event_cb(pageuarttest.back_btn, Back_Button_Event, LV_EVENT_CLICKED, NULL);

  pageuarttest.back_btn_label = lv_label_create(pageuarttest.back_btn);
  lv_obj_center(pageuarttest.back_btn_label);
  lv_label_set_text(pageuarttest.back_btn_label, "back");

  pageuarttest.clear_btn = lv_button_create(pageuarttest.view);
  lv_obj_set_size(pageuarttest.clear_btn, 120, 50);
  lv_obj_align(pageuarttest.clear_btn, LV_ALIGN_TOP_RIGHT, LV_PCT(-2), LV_PCT(2));
  lv_obj_add_event_cb(pageuarttest.clear_btn, Clear_Event, LV_EVENT_CLICKED, NULL);

  pageuarttest.clear_btn_label = lv_label_create(pageuarttest.clear_btn);
  lv_obj_center(pageuarttest.clear_btn_label);
  lv_label_set_text(pageuarttest.clear_btn_label, "clear");

  pageuarttest.receive_label = lv_label_create(pageuarttest.view);
  lv_label_set_text(pageuarttest.receive_label, "receive data");
  lv_obj_align_to(pageuarttest.receive_label,
                  pageuarttest.back_btn,
                  LV_ALIGN_OUT_BOTTOM_LEFT,
                  0,
                  5);

  pageuarttest.receive_data = lv_textarea_create(pageuarttest.view);
  lv_obj_set_size(pageuarttest.receive_data, LV_PCT(95), LV_PCT(40));
  lv_obj_align_to(pageuarttest.receive_data,
                  pageuarttest.receive_label,
                  LV_ALIGN_OUT_BOTTOM_LEFT,
                  0,
                  5);
  lv_textarea_set_cursor_click_pos(pageuarttest.receive_data, false);
  lv_obj_add_event_cb(pageuarttest.receive_data, Edit_Event, LV_EVENT_ALL, NULL);

  pageuarttest.send_label = lv_label_create(pageuarttest.view);
  lv_label_set_text(pageuarttest.send_label, "send data");
  lv_obj_align_to(pageuarttest.send_label,
                  pageuarttest.receive_data,
                  LV_ALIGN_OUT_BOTTOM_LEFT,
                  0,
                  5);

  pageuarttest.send_data = lv_textarea_create(pageuarttest.view);
  lv_obj_set_size(pageuarttest.send_data, LV_PCT(95), LV_PCT(30));
  lv_obj_align_to(pageuarttest.send_data,
                  pageuarttest.send_label,
                  LV_ALIGN_OUT_BOTTOM_LEFT,
                  0,
                  5);
  lv_obj_add_event_cb(pageuarttest.send_data, Edit_Event, LV_EVENT_ALL, NULL);

  pageuarttest.timer = lv_timer_create(my_timer, 100, NULL);
}
