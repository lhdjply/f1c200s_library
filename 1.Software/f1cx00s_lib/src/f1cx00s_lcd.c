#include "f1cx00s_lcd.h"
#include "f1cx00s_ccu.h"

void LCD_DeInit(void)
{
  for(int i = 0x0800; i < 0x1000; i += 4)
  {
    *((volatile uint32_t *)(DEBE_BASE + i)) = 0;
  }
}

// divider：0-15
void LCD_BE_Clk_Divider(uint8_t divider)
{
  CCU->BE_CLK = CCU->BE_CLK & 0xfffffff0;
  CCU->BE_CLK = CCU->BE_CLK | divider;
}

// divider：0-15
void LCD_FE_Clk_Divider(uint8_t divider)
{
  CCU->FE_CLK = CCU->FE_CLK & 0xfffffff0;
  CCU->FE_CLK = CCU->FE_CLK | divider;
}

void LCD_TCON_Cmd(FunctionalState NewState)
{
  if(NewState == DISABLE)
  {
    TCON->CTRL = 0;
    TCON->INT0 = 0;
    TCON->CLK_CTRL = TCON->CLK_CTRL & ~(0xf << 28);
    TCON->TCON0_IO_CTRL1 = 0xffffffff;
    TCON->TCON1_IO_CTRL1 = 0xffffffff;
  }
  else
  {
    TCON->CTRL = TCON->CTRL | (1 << 31);
  }
}

static void Layer_Config(LCD_Layer_Struct * pdat)
{
  DEBE->LAY_SIZE[pdat->Layer_Num] = (((pdat->height) - 1) << 16) | (((pdat->width) - 1) << 0);
  DEBE->LAY_CODNT[pdat->Layer_Num] = ((pdat->posy) << 16) | (((pdat->posx)) << 0);
  DEBE->LAY_FB_ADDR[pdat->Layer_Num] = (uint32_t)(pdat->vram) << 3;
  if(pdat->vram_format == VRAM_FORMAT_ARGB)
  {
    DEBE->LAY_ATT_CTRL_REG1[pdat->Layer_Num] = 0x09 << 8;
    DEBE->LAY_LINEWIDTH[pdat->Layer_Num] = pdat->width * 32;
  }
  else if(pdat->vram_format == VRAM_FORMAT_RGB565)
  {
    DEBE->LAY_ATT_CTRL_REG1[pdat->Layer_Num] = 0x05 << 8;
    DEBE->LAY_LINEWIDTH[pdat->Layer_Num] = pdat->width * 16;
  }
  else
  {
    DEBE->LAY_ATT_CTRL_REG1[pdat->Layer_Num] = 0x0B << 8;
    DEBE->LAY_LINEWIDTH[pdat->Layer_Num] = pdat->width * 24;
  }
  DEBE->LAY_ATT_CTRL_REG0[pdat->Layer_Num] = (pdat->alpha_value << 24) | (pdat->pipe << 15) | (pdat->priority << 10) |
                                             (pdat->alpha_enable << 0);
}

static void DEBE_Set_Mode(LCD_CFG_Struct * pdat, LCD_Layer_Struct * lcd_layer)
{
  DEBE->MODE_CTRL = DEBE->MODE_CTRL | (1 << 0);
  Layer_Config(lcd_layer);
  DEBE->COLOR_CTRL = pdat->backcolor;
  DEBE->REGBUFF_CTRL = DEBE->REGBUFF_CTRL | (1 << 0);
  DEBE->MODE_CTRL = DEBE->MODE_CTRL | (1 << 1);
}

static void TCON_Set_Mode(LCD_CFG_Struct * pdat)
{
  int32_t bp, total;
  uint32_t temp;
  TCON->CTRL = TCON->CTRL & ~(0x1 << 0);
  temp = (pdat->v_front_porch + pdat->v_back_porch + pdat->v_sync_len);
  TCON->TCON0_CTRL = (1 << 31) | ((temp & 0x1f) << 4);
  temp = Video_Get_Pll_Clk() / pdat->pixel_clock_hz;
  TCON->CLK_CTRL = (0xf << 28) | (temp << 0);
  TCON->TCON0_BASIC_TIMING[0] = ((pdat->width - 1) << 16) | ((pdat->height - 1) << 0);
  bp = pdat->h_sync_len + pdat->h_back_porch;
  total = pdat->width + pdat->h_front_porch + bp;
  TCON->TCON0_BASIC_TIMING[1] = ((total - 1) << 16) | ((bp - 1) << 0);
  bp = pdat->v_sync_len + pdat->v_back_porch;
  total = pdat->height + pdat->v_front_porch + bp;
  TCON->TCON0_BASIC_TIMING[2] = ((total * 2) << 16) | ((bp - 1) << 0);
  TCON->TCON0_BASIC_TIMING[3] = ((pdat->h_sync_len - 1) << 16) | ((pdat->v_sync_len - 1) << 0);
  TCON->TCON0_HV_TIMING = 0;
  TCON->TCON0_CPU_IF = 0;

  if(pdat->line_per_pixel == 18 || pdat->line_per_pixel == 16)
  {
    TCON->FRM_SEED0_R = 0x11111111;
    TCON->FRM_SEED0_G = 0x11111111;
    TCON->FRM_SEED0_B = 0x11111111;
    TCON->FRM_SEED1_R = 0x11111111;
    TCON->FRM_SEED1_G = 0x11111111;
    TCON->FRM_SEED1_B = 0x11111111;
    TCON->FRM_TABLE[0] = 0x01010000;
    TCON->FRM_TABLE[1] = 0x15151111;
    TCON->FRM_TABLE[2] = 0x57575555;
    TCON->FRM_TABLE[3] = 0x7f7f7777;
    if(pdat->line_per_pixel == 18)
    {
      TCON->FRM_CTRL = (1 << 31) | (0 << 4);
    }
    else
    {
      TCON->FRM_CTRL = (1 << 31) | (5 << 4);
    }
  }
  temp = (1 << 28);
  if(!pdat->h_sync_active)
  {
    temp |= (1 << 25);
  }
  if(!pdat->h_sync_active)
  {
    temp |= (1 << 24);
  }
  TCON->TCON0_IO_CTRL0 = temp;
  TCON->TCON0_IO_CTRL1 = 0;
}

void LCD_Init(LCD_CFG_Struct * cfg, LCD_Layer_Struct * lcd_layer)
{
  DEBE_Set_Mode(cfg, lcd_layer);
  TCON_Set_Mode(cfg);
}

void LCD_Layer_Cmd(LCD_Layer_Struct * lcd_layer, FunctionalState NewState)
{
  if(lcd_layer->Layer_Num > 3)
    return;
  if(NewState)
  {
    DEBE->MODE_CTRL |= 1 << (8 + lcd_layer->Layer_Num);
  }
  else
  {
    DEBE->MODE_CTRL &= ~(1 << (8 + lcd_layer->Layer_Num));
  }
}
