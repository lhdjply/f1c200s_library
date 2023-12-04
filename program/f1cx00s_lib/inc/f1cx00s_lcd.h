#ifndef __F1CX00S_LCD__H
#define __F1CX00S_LCD__H

#include "f1cx00s.h"

typedef enum
{
  VRAM_FORMAT_ARGB = 0,
  VRAM_FORMAT_RGB565,
  VRAM_FORMAT_RGB888,
} VRAM_FORMAT;

typedef struct
{
  uint32_t pixel_clock_hz;
  uint32_t width;
  uint32_t height;
  uint32_t h_front_porch;
  uint32_t h_back_porch;
  uint32_t h_sync_len;
  uint32_t v_front_porch;
  uint32_t v_back_porch;
  uint32_t v_sync_len;
  uint32_t h_sync_active;
  uint32_t v_sync_active;
  uint32_t den_active;
  uint32_t clk_active;
  uint32_t line_per_pixel;
  uint32_t rstdefe;
  uint32_t rstdebe;
  uint32_t rsttcon;
  uint32_t backcolor;
} LCD_CFG_Struct;

typedef struct
{
  uint8_t Layer_Num;
  uint32_t width;
  uint32_t height;
  uint32_t posx;
  uint32_t posy;
  uint32_t priority;
  uint32_t pipe;
  uint32_t alpha_value;
  uint32_t alpha_enable;
  uint32_t vram_format;
  uint16_t * vram;
} LCD_Layer_Struct;

void LCD_DeInit(void);
void LCD_BE_Clk_Divider(uint8_t divider);
void LCD_FE_Clk_Divider(uint8_t divider);
void LCD_TCON_Cmd(FunctionalState NewState);
void LCD_Init(LCD_CFG_Struct * cfg, LCD_Layer_Struct * lcd_layer);
void LCD_Layer_Cmd(LCD_Layer_Struct * lcd_layer, FunctionalState NewState);

#endif // __F1CX00S_LCD__H
