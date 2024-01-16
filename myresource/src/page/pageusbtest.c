// UTF-8
#include "myresource.h"

Pageusbtest pageusbtest;
extern DATA mydata;
extern rt_sem_t usbh_msc_test_sem;

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
#if TEST_USB_MODE==TEST_USB_MODE_HOST
    lv_timer_delete(pageusbtest.timer);
#endif
    lv_obj_delete(pageusbtest.view);
    lv_obj_remove_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

#if TEST_USB_MODE==TEST_USB_MODE_HOST
static void Test_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    rt_sem_release(usbh_msc_test_sem);
    mydata.usb_write_ok_flag = 0;
  }
}

static void my_timer(lv_timer_t * timer)
{
  if(mounted_flag == true)
  {
    lv_obj_remove_state(pageusbtest.usbh_msc_test_btn, LV_STATE_DISABLED);
    lv_obj_set_style_text_color(pageusbtest.usbh_msc_connect_state,
                                lv_palette_main(LV_PALETTE_BLUE),
                                LV_PART_MAIN);
    lv_label_set_text(pageusbtest.usbh_msc_connect_state, "usbh msc connect state:connect");
  }
  else
  {
    lv_obj_add_state(pageusbtest.usbh_msc_test_btn, LV_STATE_DISABLED);
    lv_obj_set_style_text_color(pageusbtest.usbh_msc_connect_state,
                                lv_palette_main(LV_PALETTE_RED),
                                LV_PART_MAIN);
    lv_label_set_text(pageusbtest.usbh_msc_connect_state, "usbh msc connect state:disconnect");
  }

  if(mydata.usb_write_ok_flag == 1)
  {
    lv_label_set_text_fmt(pageusbtest.usbh_msc_write_file_tips, "tips:file write sucess");
  }
  else
  {
    if(mydata.usb_res == FR_OK)
    {
      lv_label_set_text_fmt(pageusbtest.usbh_msc_write_file_tips, "tips:%d", mydata.usb_res);
    }
    else
    {
      lv_label_set_text_fmt(pageusbtest.usbh_msc_write_file_tips, "tips_error:%d", mydata.usb_res);
    }
  }
}
#endif

void Pageusbtest_Init(void)
{
  pageusbtest.view = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(pageusbtest.view);
  lv_obj_set_size(pageusbtest.view, LV_PCT(100), LV_PCT(100));

  pageusbtest.back_btn = lv_button_create(pageusbtest.view);
  lv_obj_set_size(pageusbtest.back_btn, 120, 50);
  lv_obj_align(pageusbtest.back_btn, LV_ALIGN_TOP_LEFT, LV_PCT(2), LV_PCT(2));
  lv_obj_add_event_cb(pageusbtest.back_btn, Back_Button_Event, LV_EVENT_CLICKED, NULL);

  pageusbtest.back_btn_label = lv_label_create(pageusbtest.back_btn);
  lv_obj_center(pageusbtest.back_btn_label);
  lv_label_set_text(pageusbtest.back_btn_label, "back");
#if TEST_USB_MODE==TEST_USB_MODE_HOST
  mydata.usb_res = FR_OK;
  mydata.usb_write_ok_flag = 0;

  pageusbtest.usbh_msc_view = lv_obj_create(pageusbtest.view);
  lv_obj_set_size(pageusbtest.usbh_msc_view, LV_PCT(90), LV_PCT(70));
  lv_obj_set_style_pad_row(pageusbtest.usbh_msc_view, 0, LV_PART_MAIN);
  lv_obj_set_flex_flow(pageusbtest.usbh_msc_view, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(pageusbtest.usbh_msc_view,
                        LV_FLEX_ALIGN_START,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_align(pageusbtest.usbh_msc_view, LV_ALIGN_BOTTOM_MID, 0, LV_PCT(-5));

  pageusbtest.usb_mode_tips = lv_label_create(pageusbtest.usbh_msc_view);
  lv_obj_set_width(pageusbtest.usb_mode_tips, LV_PCT(100));
  lv_label_set_text(pageusbtest.usb_mode_tips,
                    "Current usb mode is host mode.If you want to change mode to device mode,\
please #define TEST_USB_MODE TEST_USB_MODE_DEVICE in user/common.h");

  pageusbtest.usbh_msc_connect_state = lv_label_create(pageusbtest.usbh_msc_view);
  if(mounted_flag == true)
  {
    lv_obj_set_style_text_color(pageusbtest.usbh_msc_connect_state,
                                lv_palette_main(LV_PALETTE_BLUE),
                                LV_PART_MAIN);
    lv_label_set_text(pageusbtest.usbh_msc_connect_state, "usbh msc connect state:connect");
  }
  else
  {
    lv_obj_set_style_text_color(pageusbtest.usbh_msc_connect_state,
                                lv_palette_main(LV_PALETTE_RED),
                                LV_PART_MAIN);
    lv_label_set_text(pageusbtest.usbh_msc_connect_state, "usbh msc connect state:disconnect");
  }

  pageusbtest.usbh_msc_test_btn = lv_button_create(pageusbtest.usbh_msc_view);
  lv_obj_set_width(pageusbtest.usbh_msc_test_btn, 150);
  lv_obj_add_event_cb(pageusbtest.usbh_msc_test_btn, Test_Event, LV_EVENT_CLICKED, NULL);
  if(mounted_flag == true)
  {
    lv_obj_remove_state(pageusbtest.usbh_msc_test_btn, LV_STATE_DISABLED);
  }
  else
  {
    lv_obj_add_state(pageusbtest.usbh_msc_test_btn, LV_STATE_DISABLED);
  }

  pageusbtest.usbh_msc_test_label = lv_label_create(pageusbtest.usbh_msc_test_btn);
  lv_obj_center(pageusbtest.usbh_msc_test_label);
  lv_label_set_text(pageusbtest.usbh_msc_test_label, "usbh msc test");

  pageusbtest.usbh_msc_write_file_tips = lv_label_create(pageusbtest.usbh_msc_view);
  lv_label_set_text_fmt(pageusbtest.usbh_msc_write_file_tips, "tips:%d", mydata.usb_res);
  pageusbtest.timer = lv_timer_create(my_timer, 100, NULL);
#else
  pageusbtest.usb_mode_tips = lv_label_create(pageusbtest.view);
  lv_obj_set_width(pageusbtest.usb_mode_tips, LV_PCT(90));
  lv_label_set_text(pageusbtest.usb_mode_tips,
                    "Current usb mode is device mode.If you want to change mode to host mode,\
please #define TEST_USB_MODE TEST_USB_MODE_HOST in user/common.h");
  lv_obj_center(pageusbtest.usb_mode_tips);
#endif
}
