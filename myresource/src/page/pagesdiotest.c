// UTF-8
#include "myresource.h"

Pagesdiotest pagesdiotest;
extern DATA mydata;
extern rt_sem_t sdio_test_sem;

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_timer_del(pagesdiotest.timer);
    lv_obj_del(pagesdiotest.view);
    lv_obj_clear_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

static void Test_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    mydata.sd_write_ok_flag = 0;
    rt_sem_release(sdio_test_sem);
  }
}

static void my_timer(lv_timer_t * timer)
{
  if(SD_DETECT == 0)
  {
    lv_obj_clear_state(pagesdiotest.sdio_write_file_btn, LV_STATE_DISABLED);
    lv_obj_set_style_text_color(pagesdiotest.sdio_connect_state,
                                lv_palette_main(LV_PALETTE_BLUE),
                                LV_PART_MAIN);
    lv_label_set_text(pagesdiotest.sdio_connect_state, "sdcard connect state:connect");
  }
  else
  {
    lv_obj_add_state(pagesdiotest.sdio_write_file_btn, LV_STATE_DISABLED);
    lv_obj_set_style_text_color(pagesdiotest.sdio_connect_state,
                                lv_palette_main(LV_PALETTE_RED),
                                LV_PART_MAIN);
    lv_label_set_text(pagesdiotest.sdio_connect_state, "sdcard connect state:disconnect");
  }

  if(mydata.sd_write_ok_flag == 1)
  {
    lv_label_set_text_fmt(pagesdiotest.sdio_write_file_tips, "tips:file write sucess");
  }
  else
  {
    if(mydata.sd_res == FR_OK)
    {
      lv_label_set_text_fmt(pagesdiotest.sdio_write_file_tips, "tips:%d", mydata.sd_res);
    }
    else
    {
      lv_label_set_text_fmt(pagesdiotest.sdio_write_file_tips, "tips_error:%d", mydata.sd_res);
    }
  }
}

void Pagesdiotest_Init(void)
{
  mydata.sd_res = FR_OK;
  mydata.sd_write_ok_flag = 0;

  pagesdiotest.view = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(pagesdiotest.view);
  lv_obj_set_size(pagesdiotest.view, LV_PCT(100), LV_PCT(100));

  pagesdiotest.back_btn = lv_btn_create(pagesdiotest.view);
  lv_obj_set_size(pagesdiotest.back_btn, 120, 50);
  lv_obj_align(pagesdiotest.back_btn, LV_ALIGN_TOP_LEFT, LV_PCT(2), LV_PCT(2));
  lv_obj_add_event_cb(pagesdiotest.back_btn, Back_Button_Event, LV_EVENT_CLICKED, NULL);

  pagesdiotest.back_btn_label = lv_label_create(pagesdiotest.back_btn);
  lv_obj_center(pagesdiotest.back_btn_label);
  lv_label_set_text(pagesdiotest.back_btn_label, "back");

  pagesdiotest.sdio_view = lv_obj_create(pagesdiotest.view);
  lv_obj_set_width(pagesdiotest.sdio_view, LV_PCT(90));
  lv_obj_set_style_pad_row(pagesdiotest.sdio_view, 0, LV_PART_MAIN);
  lv_obj_set_flex_flow(pagesdiotest.sdio_view, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(pagesdiotest.sdio_view,
                        LV_FLEX_ALIGN_START,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_align(pagesdiotest.sdio_view, LV_ALIGN_BOTTOM_MID, 0, LV_PCT(-5));

  pagesdiotest.sdio_connect_state = lv_label_create(pagesdiotest.sdio_view);
  if(SD_DETECT == 0)
  {
    lv_obj_set_style_text_color(pagesdiotest.sdio_connect_state,
                                lv_palette_main(LV_PALETTE_BLUE),
                                LV_PART_MAIN);
    lv_label_set_text(pagesdiotest.sdio_connect_state, "sdcard connect state:connect");
  }
  else
  {
    lv_obj_set_style_text_color(pagesdiotest.sdio_connect_state,
                                lv_palette_main(LV_PALETTE_RED),
                                LV_PART_MAIN);
    lv_label_set_text(pagesdiotest.sdio_connect_state, "sdcard connect state:disconnect");
  }

  pagesdiotest.sdio_write_file_btn = lv_btn_create(pagesdiotest.sdio_view);
  lv_obj_set_width(pagesdiotest.sdio_write_file_btn, 150);
  lv_obj_add_event_cb(pagesdiotest.sdio_write_file_btn, Test_Event, LV_EVENT_CLICKED, NULL);
  if(SD_DETECT == 0)
  {
    lv_obj_clear_state(pagesdiotest.sdio_write_file_btn, LV_STATE_DISABLED);
  }
  else
  {
    lv_obj_add_state(pagesdiotest.sdio_write_file_btn, LV_STATE_DISABLED);
  }

  pagesdiotest.sdio_write_file_btn_label = lv_label_create(pagesdiotest.sdio_write_file_btn);
  lv_obj_center(pagesdiotest.sdio_write_file_btn_label);
  lv_label_set_text(pagesdiotest.sdio_write_file_btn_label, "sdio write file");

  pagesdiotest.sdio_write_file_tips = lv_label_create(pagesdiotest.sdio_view);
  lv_label_set_text_fmt(pagesdiotest.sdio_write_file_tips, "tips:%d", mydata.sd_res);

  pagesdiotest.timer = lv_timer_create(my_timer, 100, NULL);
}
