// UTF-8
#include "lv_demos.h"
#include "myresource.h"

PageDemoSelect pageDemoSelect;

static void lv_demo_create(void);
static void lv_librarytest_create(void);

static void Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);
  if(code == LV_EVENT_CLICKED)
  {
    if(target == pageDemoSelect.benchmark_btn)
    {
      lv_demo_benchmark();
      lv_obj_add_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
    }
    else if(target == pageDemoSelect.keypad_encoder_btn)
    {
      lv_demo_keypad_encoder();
      lv_obj_add_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
    }
    else if(target == pageDemoSelect.music_btn)
    {
      lv_demo_music();
      lv_obj_add_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
    }
    else if(target == pageDemoSelect.stress_btn)
    {
      lv_demo_stress();
      lv_obj_add_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
    }
    else if(target == pageDemoSelect.widgets_btn)
    {
      lv_demo_widgets();
      lv_obj_add_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
    }
    else if(target == pageDemoSelect.gpio_test_btn)
    {
      Pagegpiotest_Init();
      lv_obj_add_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
    }
    else if(target == pageDemoSelect.pwm_test_btn)
    {
      Pagepwmtest_Init();
      lv_obj_add_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
    }
    else if(target == pageDemoSelect.uart_test_btn)
    {
      Pageuarttest_Init();
      lv_obj_add_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
    }
  }
}

void PageDemoSelect_Init(void)
{
  pageDemoSelect.view = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(pageDemoSelect.view);
  lv_obj_set_style_pad_all(pageDemoSelect.view, 10, LV_PART_MAIN);
  lv_obj_set_size(pageDemoSelect.view, LV_PCT(100), LV_PCT(100));

  lv_demo_create();
  lv_librarytest_create();
}

static void lv_demo_create(void)
{
  pageDemoSelect.lv_demos = lv_obj_create(pageDemoSelect.view);
  lv_obj_set_size(pageDemoSelect.lv_demos, LV_PCT(45), LV_PCT(95));
  lv_obj_align(pageDemoSelect.lv_demos, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_style_pad_row(pageDemoSelect.lv_demos, 10, LV_PART_MAIN);
  lv_obj_set_flex_flow(pageDemoSelect.lv_demos, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(pageDemoSelect.lv_demos,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);

  pageDemoSelect.benchmark_btn = lv_btn_create(pageDemoSelect.lv_demos);
  lv_obj_set_width(pageDemoSelect.benchmark_btn, LV_PCT(70));
  lv_obj_add_event_cb(pageDemoSelect.benchmark_btn, Button_Event, LV_EVENT_CLICKED, NULL);
  pageDemoSelect.benchmark_label = lv_label_create(pageDemoSelect.benchmark_btn);
  lv_label_set_text(pageDemoSelect.benchmark_label, "benchmark");
  lv_obj_center(pageDemoSelect.benchmark_label);

  pageDemoSelect.keypad_encoder_btn = lv_btn_create(pageDemoSelect.lv_demos);
  lv_obj_set_width(pageDemoSelect.keypad_encoder_btn, LV_PCT(70));
  lv_obj_add_event_cb(pageDemoSelect.keypad_encoder_btn, Button_Event, LV_EVENT_CLICKED, NULL);
  pageDemoSelect.keypad_encoder_label = lv_label_create(pageDemoSelect.keypad_encoder_btn);
  lv_label_set_text(pageDemoSelect.keypad_encoder_label, "keypad_encoder");
  lv_obj_center(pageDemoSelect.keypad_encoder_label);

  pageDemoSelect.music_btn = lv_btn_create(pageDemoSelect.lv_demos);
  lv_obj_set_width(pageDemoSelect.music_btn, LV_PCT(70));
  lv_obj_add_event_cb(pageDemoSelect.music_btn, Button_Event, LV_EVENT_CLICKED, NULL);
  pageDemoSelect.music_label = lv_label_create(pageDemoSelect.music_btn);
  lv_label_set_text(pageDemoSelect.music_label, "music");
  lv_obj_center(pageDemoSelect.music_label);

  pageDemoSelect.stress_btn = lv_btn_create(pageDemoSelect.lv_demos);
  lv_obj_set_width(pageDemoSelect.stress_btn, LV_PCT(70));
  lv_obj_add_event_cb(pageDemoSelect.stress_btn, Button_Event, LV_EVENT_CLICKED, NULL);
  pageDemoSelect.stress_label = lv_label_create(pageDemoSelect.stress_btn);
  lv_label_set_text(pageDemoSelect.stress_label, "stress");
  lv_obj_center(pageDemoSelect.stress_label);

  pageDemoSelect.widgets_btn = lv_btn_create(pageDemoSelect.lv_demos);
  lv_obj_set_width(pageDemoSelect.widgets_btn, LV_PCT(70));
  lv_obj_add_event_cb(pageDemoSelect.widgets_btn, Button_Event, LV_EVENT_CLICKED, NULL);
  pageDemoSelect.widgets_label = lv_label_create(pageDemoSelect.widgets_btn);
  lv_label_set_text(pageDemoSelect.widgets_label, "widgets");
  lv_obj_center(pageDemoSelect.widgets_label);
}

static void lv_librarytest_create(void)
{
  pageDemoSelect.library_test = lv_obj_create(pageDemoSelect.view);
  lv_obj_set_size(pageDemoSelect.library_test, LV_PCT(45), LV_PCT(95));
  lv_obj_align(pageDemoSelect.library_test, LV_ALIGN_RIGHT_MID, 0, 0);
  lv_obj_set_style_pad_row(pageDemoSelect.library_test, 10, LV_PART_MAIN);
  lv_obj_set_flex_flow(pageDemoSelect.library_test, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(pageDemoSelect.library_test,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);

  pageDemoSelect.gpio_test_btn = lv_btn_create(pageDemoSelect.library_test);
  lv_obj_set_width(pageDemoSelect.gpio_test_btn, LV_PCT(70));
  lv_obj_add_event_cb(pageDemoSelect.gpio_test_btn, Button_Event, LV_EVENT_CLICKED, NULL);
  pageDemoSelect.gpio_test_label = lv_label_create(pageDemoSelect.gpio_test_btn);
  lv_label_set_text(pageDemoSelect.gpio_test_label, "gpio test");
  lv_obj_center(pageDemoSelect.gpio_test_label);

  pageDemoSelect.i2c_test_btn = lv_btn_create(pageDemoSelect.library_test);
  lv_obj_set_width(pageDemoSelect.i2c_test_btn, LV_PCT(70));
  pageDemoSelect.i2c_test_label = lv_label_create(pageDemoSelect.i2c_test_btn);
  lv_label_set_text(pageDemoSelect.i2c_test_label, "i2c test");
  lv_obj_center(pageDemoSelect.i2c_test_label);

  pageDemoSelect.pwm_test_btn = lv_btn_create(pageDemoSelect.library_test);
  lv_obj_set_width(pageDemoSelect.pwm_test_btn, LV_PCT(70));
  lv_obj_add_event_cb(pageDemoSelect.pwm_test_btn, Button_Event, LV_EVENT_CLICKED, NULL);
  pageDemoSelect.pwm_test_label = lv_label_create(pageDemoSelect.pwm_test_btn);
  lv_label_set_text(pageDemoSelect.pwm_test_label, "pwm test");
  lv_obj_center(pageDemoSelect.pwm_test_label);

  pageDemoSelect.sdio_test_btn = lv_btn_create(pageDemoSelect.library_test);
  lv_obj_set_width(pageDemoSelect.sdio_test_btn, LV_PCT(70));
  pageDemoSelect.sdio_test_label = lv_label_create(pageDemoSelect.sdio_test_btn);
  lv_label_set_text(pageDemoSelect.sdio_test_label, "sdio test");
  lv_obj_center(pageDemoSelect.sdio_test_label);

  pageDemoSelect.spi_test_btn = lv_btn_create(pageDemoSelect.library_test);
  lv_obj_set_width(pageDemoSelect.spi_test_btn, LV_PCT(70));
  pageDemoSelect.spi_test_label = lv_label_create(pageDemoSelect.spi_test_btn);
  lv_label_set_text(pageDemoSelect.spi_test_label, "spi test");
  lv_obj_center(pageDemoSelect.spi_test_label);

  pageDemoSelect.uart_test_btn = lv_btn_create(pageDemoSelect.library_test);
  lv_obj_set_width(pageDemoSelect.uart_test_btn, LV_PCT(70));
  lv_obj_add_event_cb(pageDemoSelect.uart_test_btn, Button_Event, LV_EVENT_CLICKED, NULL);
  pageDemoSelect.uart_test_label = lv_label_create(pageDemoSelect.uart_test_btn);
  lv_label_set_text(pageDemoSelect.uart_test_label, "uart test");
  lv_obj_center(pageDemoSelect.uart_test_label);

  pageDemoSelect.usb_test_btn = lv_btn_create(pageDemoSelect.library_test);
  lv_obj_set_width(pageDemoSelect.usb_test_btn, LV_PCT(70));
  pageDemoSelect.usb_test_label = lv_label_create(pageDemoSelect.usb_test_btn);
  lv_label_set_text(pageDemoSelect.usb_test_label, "usb test");
  lv_obj_center(pageDemoSelect.usb_test_label);
}
