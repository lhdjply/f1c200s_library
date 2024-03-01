#ifndef __LCD__H
#define __LCD__H

#include "sys.h"
#include "rtthread.h"
#include "lvgl/lvgl.h"

//以下提供了几种屏幕配置，不一定适配你的屏幕，最好根据屏幕的数据手册进行修改

// LCD驱动参数设置
//4.3寸 480*272
// #define LCD_FREQ 9000000 //9Mhz 屏幕时钟
// #define MY_DISP_HOR_RES 480 //屏幕水平分辨率
// #define MY_DISP_VER_RES 272 //屏幕垂直分辨率

// #define LCD_HOR_PULSE_WIDTH 4 // 水平脉宽
// #define LCD_HOR_BACK_PORCH 43 // 水平后廊
// #define LCD_HOR_FRONT_PORCH 8 // 水平前廊

// #define LCD_VER_PULSE_WIDTH 4 // 垂直脉宽
// #define LCD_VER_BACK_PORCH 12 // 垂直后廊
// #define LCD_VER_FRONT_PORCH 8 // 垂直前廊

//4.3寸 800*480
#define LCD_FREQ 30000000 //30Mhz 屏幕时钟
#define MY_DISP_HOR_RES 800 //屏幕水平分辨率
#define MY_DISP_VER_RES 480 //屏幕垂直分辨率

#define LCD_HOR_PULSE_WIDTH 8 // 水平脉宽
#define LCD_HOR_BACK_PORCH 8 // 水平后廊
#define LCD_HOR_FRONT_PORCH 4 // 水平前廊

#define LCD_VER_PULSE_WIDTH 8 // 垂直脉宽
#define LCD_VER_BACK_PORCH 10 // 垂直后廊
#define LCD_VER_FRONT_PORCH 4 // 垂直前廊

//7寸 800*480
// #define LCD_FREQ 30000000 //30Mhz 屏幕时钟
// #define MY_DISP_HOR_RES 800 //屏幕水平分辨率
// #define MY_DISP_VER_RES 480 //屏幕垂直分辨率

// #define LCD_HOR_PULSE_WIDTH 1 // 水平脉宽
// #define LCD_HOR_BACK_PORCH 46 // 水平后廊
// #define LCD_HOR_FRONT_PORCH 210 // 水平前廊

// #define LCD_VER_PULSE_WIDTH 1 // 垂直脉宽
// #define LCD_VER_BACK_PORCH 23 // 垂直后廊
// #define LCD_VER_FRONT_PORCH 22 // 垂直前廊

void LCD_Config(void);
void LCD_SetBrightness(int32_t brightness);
void LCD_Color_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t * data);

#endif // !__LCD__H
