#ifndef __LCD__H
#define __LCD__H

#include "sys.h"
#include "rtthread.h"
#include "lvgl/lvgl.h"

#define LCD_EN PEout(5)

#define LCD_FREQ 30000000//30Mhz
#define MY_DISP_HOR_RES 800
#define MY_DISP_VER_RES 480

// LCD驱动参数设置
#define LCD_HOR_PULSE_WIDTH 8 // 水平脉宽
#define LCD_HOR_BACK_PORCH 8 // 水平后廊
#define LCD_HOR_FRONT_PORCH 4 // 水平前廊

#define LCD_VER_PULSE_WIDTH 8 // 垂直脉宽
#define LCD_VER_BACK_PORCH 10 // 垂直后廊
#define LCD_VER_FRONT_PORCH 4 // 垂直前廊

void LCD_Config(void);
void LCD_SetBrightness(int32_t brightness);
void LCD_Color_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lv_color_t * data);

#endif // !__LCD__H