#include "lv_port_disp.h"
#include "../lvgl.h"
#include "common.h"

static void disp_init(void);

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
// static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//         const lv_area_t * fill_area, lv_color_t color);

static lv_disp_drv_t my_disp_drv; /*Descriptor of a display driver*/
extern LCD_Layer_Struct lcd_layer;

void lv_port_disp_init(void)
{
    static lv_color_t *buf_1_1, *buf_1_2;
    disp_init();
    static lv_disp_draw_buf_t draw_buf_dsc_1;
    buf_1_1 = (lv_color_t *)rt_malloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t));
    buf_1_2 = (lv_color_t *)rt_malloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t));
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1_1, buf_1_2, MY_DISP_HOR_RES * MY_DISP_VER_RES); /*Initialize the display buffer*/
    lv_disp_drv_init(&my_disp_drv);
    /*Basic initialization*/
    my_disp_drv.hor_res = MY_DISP_HOR_RES;
    my_disp_drv.ver_res = MY_DISP_VER_RES;
    my_disp_drv.flush_cb = disp_flush;
    my_disp_drv.draw_buf = &draw_buf_dsc_1;
    // my_disp_drv.full_refresh = 1;
    // my_disp_drv.sw_rotate = 1;
    // my_disp_drv.rotated = LV_DISP_ROT_270;
    //  my_disp_drv.gpu_fill_cb = gpu_fill;
    lv_disp_drv_register(&my_disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    LCD_Config();
    LCD_SetBrightness(0);
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    LCD_Color_Fill(area->x1, area->y1, area->x2, area->y2, color_p);
    lv_disp_flush_ready(disp_drv);
}
/*OPTIONAL: GPU INTERFACE*/

/*If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color*/
// static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//                     const lv_area_t * fill_area, lv_color_t color)
//{
//     /*It's an example code which should be done by your GPU*/
//     int32_t x, y;
//     dest_buf += dest_width * fill_area->y1; /*Go to the first line*/
//
//     for(y = fill_area->y1; y <= fill_area->y2; y++) {
//         for(x = fill_area->x1; x <= fill_area->x2; x++) {
//             dest_buf[x] = color;
//         }
//         dest_buf+=dest_width;    /*Go to the next line*/
//     }
// }
