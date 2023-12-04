#include "lcd.h"
#include "delay.h"

LCD_CFG_Struct lcd_cfg;
LCD_Layer_Struct lcd_layer;

static void LCD_Clock_Config(void);
static void LCD_GPIO_Config(void);
static void LCD_Fun_Config(void);
static void LCD_BL_Config(void);
static void LCD_EN_Config(void);

void LCD_Config(void)
{
  LCD_Clock_Config();
  LCD_GPIO_Config();
  LCD_Fun_Config();
  LCD_BL_Config();
  LCD_EN_Config();
}

static void LCD_Clock_Config(void)
{
  CCU_BUS1_GatingClockCmd(CCU_BUS1Gating_LCD, ENABLE);
  CCU_BUS1_GatingClockCmd(CCU_BUS1Gating_DEBE, ENABLE);
  CCU_BUS1_GatingClockCmd(CCU_BUS1Gating_DEFE, ENABLE);

  CCU_FE_ClockCmd(ENABLE);
  CCU_BE_ClockCmd(ENABLE);
  CCU_TCON_ClockCmd(ENABLE);

  CCU_BUS1_GatingResetCmd(CCU_BUS1Gating_LCD, ENABLE);
  CCU_BUS1_GatingResetCmd(CCU_BUS1Gating_DEBE, ENABLE);
  CCU_BUS1_GatingResetCmd(CCU_BUS1Gating_DEFE, ENABLE);
}

static void LCD_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_AF_Remap(GPIOD, GPIO_PinSource0, GPIO_AF_PD0_LCD_D2);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource1, GPIO_AF_PD1_LCD_D3);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource2, GPIO_AF_PD2_LCD_D4);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource3, GPIO_AF_PD3_LCD_D5);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource4, GPIO_AF_PD4_LCD_D6);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource5, GPIO_AF_PD5_LCD_D7);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource6, GPIO_AF_PD6_LCD_D10);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource7, GPIO_AF_PD7_LCD_D11);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource8, GPIO_AF_PD8_LCD_D12);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource9, GPIO_AF_PD9_LCD_D13);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource10, GPIO_AF_PD10_LCD_D14);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource11, GPIO_AF_PD11_LCD_D15);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource12, GPIO_AF_PD12_LCD_D18);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource13, GPIO_AF_PD13_LCD_D19);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource14, GPIO_AF_PD14_LCD_D20);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource15, GPIO_AF_PD15_LCD_D21);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource16, GPIO_AF_PD16_LCD_D22);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource17, GPIO_AF_PD17_LCD_D23);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource18, GPIO_AF_PD18_LCD_CLK);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource19, GPIO_AF_PD19_LCD_DE);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource20, GPIO_AF_PD20_LCD_HSYNC);
  GPIO_AF_Remap(GPIOD, GPIO_PinSource21, GPIO_AF_PD21_LCD_VSYNC);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
                                GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
                                GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 |
                                GPIO_Pin_16 | GPIO_Pin_17 | GPIO_Pin_18 | GPIO_Pin_19 |
                                GPIO_Pin_20 | GPIO_Pin_21;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

static void LCD_Fun_Config(void)
{
  LCD_DeInit();
  LCD_BE_Clk_Divider(0);
  LCD_FE_Clk_Divider(0);

  LCD_TCON_Cmd(DISABLE);

  lcd_cfg.pixel_clock_hz = LCD_FREQ; // 30Mhz
  lcd_cfg.width = MY_DISP_HOR_RES;
  lcd_cfg.height = MY_DISP_VER_RES;
  lcd_cfg.h_front_porch = LCD_HOR_FRONT_PORCH;
  lcd_cfg.h_back_porch = LCD_HOR_BACK_PORCH;
  lcd_cfg.h_sync_len = LCD_HOR_PULSE_WIDTH;
  lcd_cfg.v_front_porch = LCD_VER_PULSE_WIDTH;
  lcd_cfg.v_back_porch = LCD_VER_BACK_PORCH;
  lcd_cfg.v_sync_len = LCD_VER_PULSE_WIDTH;
  lcd_cfg.h_sync_active = 0;
  lcd_cfg.v_sync_active = 0;
  lcd_cfg.den_active = 0;
  lcd_cfg.clk_active = 0;
  lcd_cfg.line_per_pixel = 18;
  lcd_cfg.rstdefe = 46;
  lcd_cfg.rstdebe = 44;
  lcd_cfg.rsttcon = 36;
  lcd_cfg.backcolor = 0;

  lcd_layer.Layer_Num = 0;
  lcd_layer.width = MY_DISP_HOR_RES;
  lcd_layer.height = MY_DISP_VER_RES;
  lcd_layer.posx = 0;
  lcd_layer.posy = 0;
  lcd_layer.priority = 0;
  lcd_layer.pipe = 0;
  lcd_layer.alpha_enable = 1;
  lcd_layer.alpha_value = 255;
  lcd_layer.vram = (void *)rt_malloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t));
#if LV_COLOR_DEPTH == 32
  lcd_layer.vram_format = VRAM_FORMAT_ARGB;
#else
  lcd_layer.vram_format = VRAM_FORMAT_RGB565;
#endif

  LCD_Init(&lcd_cfg, &lcd_layer);
  LCD_TCON_Cmd(ENABLE);

  LCD_Layer_Cmd(&lcd_layer, ENABLE);
}

static void LCD_BL_Config(void)
{
  PWM_InitTypeDef PWM_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_AF_Remap(GPIOE, GPIO_PinSource6, GPIO_AF_PE6_PWM1);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  PWM_InitStructure.channel = PWM_CHANNEL_1;
  PWM_InitStructure.duty_cycle = 0;
  PWM_InitStructure.period = 463000; // 2160hz
  PWM_InitStructure.polarity = 1;
  PWM_Init(&PWM_InitStructure);

  PWM_Cmd(PWM_CHANNEL_1, ENABLE);
}

static void LCD_EN_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  LCD_EN = 0;
}

void LCD_Color_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lv_color_t * data)
{
  uint32_t y = y1, i;
  lv_color_t * lcdbuf_gui;
  for(y = y1; y < y2 + 1; y++)
  {
    lcdbuf_gui = (lv_color_t *)lcd_layer.vram + y * MY_DISP_HOR_RES + x1;
    for(i = 0; i < x2 - x1 + 1; i++)
    {
      *lcdbuf_gui = data[i];
      lcdbuf_gui++;
    }
    data = data + x2 - x1 + 1;
  }
}

void LCD_SetBrightness(int32_t brightness)
{
  PWM_Set_Duty(PWM_CHANNEL_1, brightness);
}
