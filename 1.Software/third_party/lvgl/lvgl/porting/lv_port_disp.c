#include "lv_port_disp.h"
#include "common.h"

static void disp_init(void);
static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

void lv_port_disp_init(void)
{
    uint32_t color_size;
    static uint8_t *buf_1_1, *buf_1_2;
    disp_init();

    lv_display_t *disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    color_size = MY_DISP_HOR_RES *
                 MY_DISP_VER_RES *
                 lv_color_format_get_size(LV_COLOR_FORMAT_NATIVE);
    buf_1_1 = (uint8_t *)rt_malloc(color_size);
    buf_1_2 = (uint8_t *)rt_malloc(color_size);
    lv_display_set_buffers(disp,
                            buf_1_1,
                            buf_1_2,
                            color_size,
                            LV_DISPLAY_RENDER_MODE_PARTIAL);
}

static void disp_init(void)
{
    LCD_Config();
    LCD_SetBrightness(0);
}

static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{
    LCD_Color_Fill(area->x1, area->y1, area->x2, area->y2, px_map);
    lv_display_flush_ready(disp_drv);
}
