// UTF-8
#include "myresource.h"

Pagespitest pagespitest;

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_obj_del(pagespitest.view);
    lv_obj_clear_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

static void Button_Event(lv_event_t * e)
{
  const char * WriteBuff = "1234567890";
  char ReadBuff[20];
  lv_obj_t * target = lv_event_get_target(e);
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    if(target == pagespitest.write_btn)
    {
      W25QXX_Write((uint8_t *)WriteBuff, 0xF00000, 10);
    }
    else if(target == pagespitest.read_btn)
    {
      W25QXX_Read((uint8_t *)ReadBuff, 0xF00000, 10);
      ReadBuff[10] = 0;
      lv_label_set_text_fmt(pagespitest.read_label, "read data:%s", ReadBuff);
      lv_obj_align_to(pagespitest.read_label,
                      pagespitest.write_btn,
                      LV_ALIGN_OUT_BOTTOM_MID,
                      0,
                      0);
    }
  }
}

void Pagespitest_Init(void)
{
  pagespitest.view = lv_obj_create(lv_screen_active());
  lv_obj_remove_style_all(pagespitest.view);
  lv_obj_set_size(pagespitest.view, LV_PCT(100), LV_PCT(100));

  pagespitest.back_btn = lv_button_create(pagespitest.view);
  lv_obj_set_size(pagespitest.back_btn, 120, 50);
  lv_obj_align(pagespitest.back_btn, LV_ALIGN_TOP_LEFT, LV_PCT(2), LV_PCT(2));
  lv_obj_add_event_cb(pagespitest.back_btn, Back_Button_Event, LV_EVENT_CLICKED, NULL);

  pagespitest.back_btn_label = lv_label_create(pagespitest.back_btn);
  lv_obj_center(pagespitest.back_btn_label);
  lv_label_set_text(pagespitest.back_btn_label, "back");

  pagespitest.spi_view = lv_obj_create(pagespitest.view);
  lv_obj_set_size(pagespitest.spi_view, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_style_pad_row(pagespitest.spi_view, 0, LV_PART_MAIN);
  lv_obj_set_flex_flow(pagespitest.spi_view, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(pagespitest.spi_view,
                        LV_FLEX_ALIGN_START,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_align(pagespitest.spi_view, LV_ALIGN_BOTTOM_MID, 0, LV_PCT(-5));

  pagespitest.write_label = lv_label_create(pagespitest.spi_view);
  lv_label_set_text(pagespitest.write_label, "write data:""1234567890""(address:0xF00000)");

  pagespitest.write_btn = lv_button_create(pagespitest.spi_view);
  lv_obj_set_size(pagespitest.write_btn, 120, 50);
  lv_obj_add_event_cb(pagespitest.write_btn, Button_Event, LV_EVENT_CLICKED, NULL);

  pagespitest.write_btn_label = lv_label_create(pagespitest.write_btn);
  lv_label_set_text(pagespitest.write_btn_label, "write data");
  lv_obj_center(pagespitest.write_btn_label);

  pagespitest.read_label = lv_label_create(pagespitest.spi_view);
  lv_label_set_text(pagespitest.read_label, "read data:");

  pagespitest.read_btn = lv_button_create(pagespitest.spi_view);
  lv_obj_set_size(pagespitest.read_btn, 120, 50);
  lv_obj_add_event_cb(pagespitest.read_btn, Button_Event, LV_EVENT_CLICKED, NULL);

  pagespitest.read_btn_label = lv_label_create(pagespitest.read_btn);
  lv_label_set_text(pagespitest.read_btn_label, "read data");
  lv_obj_center(pagespitest.read_btn_label);
}
