// UTF-8
#include "myresource.h"

Pagei2ctest pagei2ctest;
extern DATA mydata;
extern rt_sem_t rtc_settime_sem;

static void DateSet_msgbox_Init(void);
static void TimeSet_msgbox_Init(void);

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_timer_del(pagei2ctest.timer);
    lv_obj_del(pagei2ctest.view);
    lv_obj_clear_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

static void TIME_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);
  if(code == LV_EVENT_CLICKED)
  {
    if(target == pagei2ctest.set_date_btn)
    {
      DateSet_msgbox_Init();
    }
    else if(target == pagei2ctest.set_time_btn)
    {
      TimeSet_msgbox_Init();
    }
  }
}

static void Date_Msgbox_Btn_OK_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    mydata.real_time.year = lv_roller_get_selected(pagei2ctest.date_year_roller) + 2000;
    mydata.real_time.month = lv_roller_get_selected(pagei2ctest.date_month_roller) + 1;
    mydata.real_time.day = lv_roller_get_selected(pagei2ctest.date_day_roller) + 1;
    lv_msgbox_close(pagei2ctest.date_msgbox);
    rt_sem_release(rtc_settime_sem);
  }
}

static void Date_Msgbox_Btn_NO_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_msgbox_close(pagei2ctest.date_msgbox);
  }
}

static void Time_Msgbox_Btn_OK_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    mydata.real_time.hour = lv_roller_get_selected(pagei2ctest.time_hour_roller);
    mydata.real_time.minute = lv_roller_get_selected(pagei2ctest.time_minute_roller);
    mydata.real_time.second = lv_roller_get_selected(pagei2ctest.time_second_roller);
    lv_msgbox_close(pagei2ctest.time_msgbox);
    rt_sem_release(rtc_settime_sem);
  }
}

static void Time_Msgbox_Btn_NO_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_msgbox_close(pagei2ctest.time_msgbox);
  }
}

static void my_timer(lv_timer_t * timer)
{
  lv_label_set_text_fmt(pagei2ctest.real_time, "%d-%02d-%02d %02d:%02d:%02d",
                        mydata.real_time.year, mydata.real_time.month, mydata.real_time.day,
                        mydata.real_time.hour, mydata.real_time.minute, mydata.real_time.second);
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

  pagei2ctest.real_time = lv_label_create(pagei2ctest.view);
  lv_obj_center(pagei2ctest.real_time);
  lv_label_set_text_fmt(pagei2ctest.real_time, "%d-%02d-%02d %02d:%02d:%02d",
                        mydata.real_time.year, mydata.real_time.month, mydata.real_time.day,
                        mydata.real_time.hour, mydata.real_time.minute, mydata.real_time.second);

  pagei2ctest.set_date_btn = lv_btn_create(pagei2ctest.view);
  lv_obj_set_size(pagei2ctest.set_date_btn, 120, 50);
  lv_obj_align(pagei2ctest.set_date_btn, LV_ALIGN_BOTTOM_LEFT, LV_PCT(2), LV_PCT(-2));
  lv_obj_add_event_cb(pagei2ctest.set_date_btn, TIME_Event, LV_EVENT_CLICKED, NULL);

  pagei2ctest.set_date_btn_label = lv_label_create(pagei2ctest.set_date_btn);
  lv_obj_center(pagei2ctest.set_date_btn_label);
  lv_label_set_text(pagei2ctest.set_date_btn_label, "set date");

  pagei2ctest.set_time_btn = lv_btn_create(pagei2ctest.view);
  lv_obj_set_size(pagei2ctest.set_time_btn, 120, 50);
  lv_obj_align(pagei2ctest.set_time_btn, LV_ALIGN_BOTTOM_RIGHT, LV_PCT(-2), LV_PCT(-2));
  lv_obj_add_event_cb(pagei2ctest.set_time_btn, TIME_Event, LV_EVENT_CLICKED, NULL);

  pagei2ctest.set_time_btn_label = lv_label_create(pagei2ctest.set_time_btn);
  lv_obj_center(pagei2ctest.set_time_btn_label);
  lv_label_set_text(pagei2ctest.set_time_btn_label, "set time");

  pagei2ctest.timer = lv_timer_create(my_timer, 100, NULL);
}

static void DateSet_msgbox_Init(void)
{
  pagei2ctest.date_msgbox = lv_msgbox_create(NULL, NULL, NULL, NULL, NULL);
  lv_obj_remove_style_all(pagei2ctest.date_msgbox);
  lv_obj_set_size(pagei2ctest.date_msgbox, 320, 250);
  lv_obj_set_style_bg_color(pagei2ctest.date_msgbox, lv_color_make(0xee, 0xee, 0xee), LV_PART_MAIN);
  lv_obj_set_style_bg_opa(pagei2ctest.date_msgbox, LV_OPA_100, LV_PART_MAIN);
  lv_obj_set_style_radius(pagei2ctest.date_msgbox, 10, LV_PART_MAIN);
  lv_obj_align(pagei2ctest.date_msgbox, LV_ALIGN_BOTTOM_MID, 0, 0);

  pagei2ctest.date_msgbox_btn_ok = lv_btn_create(pagei2ctest.date_msgbox);
  lv_obj_set_size(pagei2ctest.date_msgbox_btn_ok, 120, 40);
  lv_obj_align(pagei2ctest.date_msgbox_btn_ok, LV_ALIGN_BOTTOM_LEFT, 10, -15);
  pagei2ctest.date_msgbox_btn_ok_text = lv_label_create(pagei2ctest.date_msgbox_btn_ok);
  lv_obj_add_event_cb(pagei2ctest.date_msgbox_btn_ok, Date_Msgbox_Btn_OK_Event, LV_EVENT_CLICKED, NULL);
  lv_label_set_text(pagei2ctest.date_msgbox_btn_ok_text, "yes");
  lv_obj_center(pagei2ctest.date_msgbox_btn_ok_text);

  pagei2ctest.date_msgbox_btn_no = lv_btn_create(pagei2ctest.date_msgbox);
  lv_obj_set_size(pagei2ctest.date_msgbox_btn_no, 120, 40);
  lv_obj_align(pagei2ctest.date_msgbox_btn_no, LV_ALIGN_BOTTOM_RIGHT, -10, -15);
  pagei2ctest.date_msgbox_btn_no_text = lv_label_create(pagei2ctest.date_msgbox_btn_no);
  lv_obj_add_event_cb(pagei2ctest.date_msgbox_btn_no, Date_Msgbox_Btn_NO_Event, LV_EVENT_CLICKED, NULL);
  lv_label_set_text(pagei2ctest.date_msgbox_btn_no_text, "no");
  lv_obj_center(pagei2ctest.date_msgbox_btn_no_text);

  pagei2ctest.date_year_roller = lv_roller_create(pagei2ctest.date_msgbox);
  lv_roller_set_options(pagei2ctest.date_year_roller,
                        "2000\n"
                        "2001\n"
                        "2002\n"
                        "2003\n"
                        "2004\n"
                        "2005\n"
                        "2006\n"
                        "2007\n"
                        "2008\n"
                        "2009\n"
                        "2010\n"
                        "2011\n"
                        "2012\n"
                        "2013\n"
                        "2014\n"
                        "2015\n"
                        "2016\n"
                        "2017\n"
                        "2018\n"
                        "2019\n"
                        "2020\n"
                        "2021\n"
                        "2022\n"
                        "2023\n"
                        "2024\n"
                        "2025\n"
                        "2026\n"
                        "2027\n"
                        "2028\n"
                        "2029\n"
                        "2030\n"
                        "2031\n"
                        "2032\n"
                        "2033\n"
                        "2034\n"
                        "2035\n"
                        "2036\n"
                        "2037\n"
                        "2038\n"
                        "2039\n"
                        "2040\n"
                        "2041\n"
                        "2042\n"
                        "2043\n"
                        "2044\n"
                        "2045\n"
                        "2046\n"
                        "2047\n"
                        "2048\n"
                        "2049\n"
                        "2050\n"
                        "2051\n"
                        "2052\n"
                        "2053\n"
                        "2054\n"
                        "2055\n"
                        "2056\n"
                        "2057\n"
                        "2058\n"
                        "2059\n"
                        "2060\n"
                        "2061\n"
                        "2062\n"
                        "2063\n"
                        "2064\n"
                        "2065\n"
                        "2066\n"
                        "2067\n"
                        "2068\n"
                        "2069\n"
                        "2070\n"
                        "2071\n"
                        "2072\n"
                        "2073\n"
                        "2074\n"
                        "2075\n"
                        "2076\n"
                        "2077\n"
                        "2078\n"
                        "2079\n"
                        "2080\n"
                        "2081\n"
                        "2082\n"
                        "2083\n"
                        "2084\n"
                        "2085\n"
                        "2086\n"
                        "2087\n"
                        "2088\n"
                        "2089\n"
                        "2090\n"
                        "2091\n"
                        "2092\n"
                        "2093\n"
                        "2094\n"
                        "2095\n"
                        "2096\n"
                        "2097\n"
                        "2098\n"
                        "2099",
                        LV_ROLLER_MODE_NORMAL);
  lv_roller_set_visible_row_count(pagei2ctest.date_year_roller, 4);
  lv_roller_set_selected(pagei2ctest.date_year_roller, mydata.real_time.year - 2000, LV_ANIM_OFF);
  lv_obj_set_width(pagei2ctest.date_year_roller, 80);
  lv_obj_align(pagei2ctest.date_year_roller, LV_ALIGN_TOP_LEFT, 20, 20);

  pagei2ctest.date_month_roller = lv_roller_create(pagei2ctest.date_msgbox);
  lv_roller_set_options(pagei2ctest.date_month_roller,
                        "1\n"
                        "2\n"
                        "3\n"
                        "4\n"
                        "5\n"
                        "6\n"
                        "7\n"
                        "8\n"
                        "9\n"
                        "10\n"
                        "11\n"
                        "12",
                        LV_ROLLER_MODE_NORMAL);
  lv_roller_set_visible_row_count(pagei2ctest.date_month_roller, 4);
  lv_roller_set_selected(pagei2ctest.date_month_roller, mydata.real_time.month - 1, LV_ANIM_OFF);
  lv_obj_set_width(pagei2ctest.date_month_roller, 80);
  lv_obj_align(pagei2ctest.date_month_roller, LV_ALIGN_TOP_MID, 0, 20);

  pagei2ctest.date_day_roller = lv_roller_create(pagei2ctest.date_msgbox);
  lv_roller_set_options(pagei2ctest.date_day_roller,
                        "1\n"
                        "2\n"
                        "3\n"
                        "4\n"
                        "5\n"
                        "6\n"
                        "7\n"
                        "8\n"
                        "9\n"
                        "10\n"
                        "11\n"
                        "12\n"
                        "13\n"
                        "14\n"
                        "15\n"
                        "16\n"
                        "17\n"
                        "18\n"
                        "19\n"
                        "20\n"
                        "21\n"
                        "22\n"
                        "23\n"
                        "24\n"
                        "25\n"
                        "26\n"
                        "27\n"
                        "28\n"
                        "29\n"
                        "30\n"
                        "31",
                        LV_ROLLER_MODE_NORMAL);
  lv_roller_set_selected(pagei2ctest.date_day_roller, mydata.real_time.day - 1, LV_ANIM_OFF);
  lv_roller_set_visible_row_count(pagei2ctest.date_day_roller, 4);
  lv_obj_set_width(pagei2ctest.date_day_roller, 80);
  lv_obj_align(pagei2ctest.date_day_roller, LV_ALIGN_TOP_RIGHT, -20, 20);
}

static void TimeSet_msgbox_Init(void)
{
  pagei2ctest.time_msgbox = lv_msgbox_create(NULL, NULL, NULL, NULL, NULL);
  lv_obj_remove_style_all(pagei2ctest.time_msgbox);
  lv_obj_set_size(pagei2ctest.time_msgbox, 320, 250);
  lv_obj_set_style_bg_color(pagei2ctest.time_msgbox, lv_color_make(0xee, 0xee, 0xee), LV_PART_MAIN);
  lv_obj_set_style_bg_opa(pagei2ctest.time_msgbox, LV_OPA_100, LV_PART_MAIN);
  lv_obj_set_style_radius(pagei2ctest.time_msgbox, 10, LV_PART_MAIN);
  lv_obj_align(pagei2ctest.time_msgbox, LV_ALIGN_BOTTOM_MID, 0, 0);

  pagei2ctest.time_msgbox_btn_ok = lv_btn_create(pagei2ctest.time_msgbox);
  lv_obj_set_size(pagei2ctest.time_msgbox_btn_ok, 120, 40);
  lv_obj_align(pagei2ctest.time_msgbox_btn_ok, LV_ALIGN_BOTTOM_LEFT, 10, -15);
  pagei2ctest.time_msgbox_btn_ok_text = lv_label_create(pagei2ctest.time_msgbox_btn_ok);
  lv_obj_add_event_cb(pagei2ctest.time_msgbox_btn_ok, Time_Msgbox_Btn_OK_Event, LV_EVENT_CLICKED, NULL);
  lv_label_set_text(pagei2ctest.time_msgbox_btn_ok_text, "yes");
  lv_obj_center(pagei2ctest.time_msgbox_btn_ok_text);

  pagei2ctest.time_msgbox_btn_no = lv_btn_create(pagei2ctest.time_msgbox);
  lv_obj_set_size(pagei2ctest.time_msgbox_btn_no, 120, 40);
  lv_obj_align(pagei2ctest.time_msgbox_btn_no, LV_ALIGN_BOTTOM_RIGHT, -10, -15);
  pagei2ctest.time_msgbox_btn_no_text = lv_label_create(pagei2ctest.time_msgbox_btn_no);
  lv_obj_add_event_cb(pagei2ctest.time_msgbox_btn_no, Time_Msgbox_Btn_NO_Event, LV_EVENT_CLICKED, NULL);
  lv_label_set_text(pagei2ctest.time_msgbox_btn_no_text, "no");
  lv_obj_center(pagei2ctest.time_msgbox_btn_no_text);

  pagei2ctest.time_hour_roller = lv_roller_create(pagei2ctest.time_msgbox);
  lv_roller_set_options(pagei2ctest.time_hour_roller,
                        "0\n"
                        "1\n"
                        "2\n"
                        "3\n"
                        "4\n"
                        "5\n"
                        "6\n"
                        "7\n"
                        "8\n"
                        "9\n"
                        "10\n"
                        "11\n"
                        "12\n"
                        "13\n"
                        "14\n"
                        "15\n"
                        "16\n"
                        "17\n"
                        "18\n"
                        "19\n"
                        "20\n"
                        "21\n"
                        "22\n"
                        "23",
                        LV_ROLLER_MODE_NORMAL);
  lv_roller_set_visible_row_count(pagei2ctest.time_hour_roller, 4);
  lv_roller_set_selected(pagei2ctest.time_hour_roller, mydata.real_time.hour, LV_ANIM_OFF);
  lv_obj_set_width(pagei2ctest.time_hour_roller, 80);
  lv_obj_align(pagei2ctest.time_hour_roller, LV_ALIGN_TOP_LEFT, 20, 20);

  pagei2ctest.time_minute_roller = lv_roller_create(pagei2ctest.time_msgbox);
  lv_roller_set_options(pagei2ctest.time_minute_roller,
                        "0\n"
                        "1\n"
                        "2\n"
                        "3\n"
                        "4\n"
                        "5\n"
                        "6\n"
                        "7\n"
                        "8\n"
                        "9\n"
                        "10\n"
                        "11\n"
                        "12\n"
                        "13\n"
                        "14\n"
                        "15\n"
                        "16\n"
                        "17\n"
                        "18\n"
                        "19\n"
                        "20\n"
                        "21\n"
                        "22\n"
                        "23\n"
                        "24\n"
                        "25\n"
                        "26\n"
                        "27\n"
                        "28\n"
                        "29\n"
                        "30\n"
                        "31\n"
                        "32\n"
                        "33\n"
                        "34\n"
                        "35\n"
                        "36\n"
                        "37\n"
                        "38\n"
                        "39\n"
                        "40\n"
                        "41\n"
                        "42\n"
                        "43\n"
                        "44\n"
                        "45\n"
                        "46\n"
                        "47\n"
                        "48\n"
                        "49\n"
                        "50\n"
                        "51\n"
                        "52\n"
                        "53\n"
                        "54\n"
                        "55\n"
                        "56\n"
                        "57\n"
                        "58\n"
                        "59",
                        LV_ROLLER_MODE_NORMAL);
  lv_roller_set_visible_row_count(pagei2ctest.time_minute_roller, 4);
  lv_roller_set_selected(pagei2ctest.time_minute_roller, mydata.real_time.minute, LV_ANIM_OFF);
  lv_obj_set_width(pagei2ctest.time_minute_roller, 80);
  lv_obj_align(pagei2ctest.time_minute_roller, LV_ALIGN_TOP_MID, 0, 20);

  pagei2ctest.time_second_roller = lv_roller_create(pagei2ctest.time_msgbox);
  lv_roller_set_options(pagei2ctest.time_second_roller,
                        "0\n"
                        "1\n"
                        "2\n"
                        "3\n"
                        "4\n"
                        "5\n"
                        "6\n"
                        "7\n"
                        "8\n"
                        "9\n"
                        "10\n"
                        "11\n"
                        "12\n"
                        "13\n"
                        "14\n"
                        "15\n"
                        "16\n"
                        "17\n"
                        "18\n"
                        "19\n"
                        "20\n"
                        "21\n"
                        "22\n"
                        "23\n"
                        "24\n"
                        "25\n"
                        "26\n"
                        "27\n"
                        "28\n"
                        "29\n"
                        "30\n"
                        "31\n"
                        "32\n"
                        "33\n"
                        "34\n"
                        "35\n"
                        "36\n"
                        "37\n"
                        "38\n"
                        "39\n"
                        "40\n"
                        "41\n"
                        "42\n"
                        "43\n"
                        "44\n"
                        "45\n"
                        "46\n"
                        "47\n"
                        "48\n"
                        "49\n"
                        "50\n"
                        "51\n"
                        "52\n"
                        "53\n"
                        "54\n"
                        "55\n"
                        "56\n"
                        "57\n"
                        "58\n"
                        "59",
                        LV_ROLLER_MODE_NORMAL);
  lv_roller_set_selected(pagei2ctest.time_second_roller, mydata.real_time.second, LV_ANIM_OFF);
  lv_roller_set_visible_row_count(pagei2ctest.time_second_roller, 4);
  lv_obj_set_width(pagei2ctest.time_second_roller, 80);
  lv_obj_align(pagei2ctest.time_second_roller, LV_ALIGN_TOP_RIGHT, -20, 20);
}
