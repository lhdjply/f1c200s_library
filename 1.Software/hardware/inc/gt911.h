#ifndef _GTXX_H
#define _GTXX_H

#include "sys.h"
#include "delay.h"
#include "lcd.h"

#define GT911_I2C I2C0
#define GT911_INT PEout(10) // GT911_INT
#define GT911_RST PEout(9)  // GT911_RST

#define GTP_MAX_WIDTH MY_DISP_HOR_RES
#define GTP_MAX_HEIGHT MY_DISP_VER_RES

#define GTP_SET_WIDTH_H_Byte (uint8_t)(GTP_MAX_WIDTH >> 8) // 设置 x 坐标高字节
#define GTP_SET_WIDTH_L_Byte (uint8_t)(GTP_MAX_WIDTH)      // 设置 x 坐标低字节

#define GTP_SET_HEIGHT_H_Byte (uint8_t)(GTP_MAX_HEIGHT >> 8) // 设置 y 坐标 高字节
#define GTP_SET_HEIGHT_L_Byte (uint8_t)(GTP_MAX_HEIGHT)      // 设置 y 坐标 低字节

// I2C读写命令
#define GT_CMD_ADDR 0x14

// GT911 部分寄存器定义
#define GT_CTRL_REG 0X8040  // GT911控制寄存器
#define GT_CFGS_REG 0X8047  // GT911配置起始地址寄存器
#define GT_CHECK_REG 0X80FF // GT911校验和寄存器
#define GT_PID_REG 0X8140   // GT911产品ID寄存器

#define GT_GSTID_REG 0X814E // GT911当前检测到的触摸情况
#define GT9x_TP1 0x8150   /*!< 第一个触摸点数据地址 */
#define GT9x_TP2 0x8158   /*!< 第二个触摸点数据地址 */
#define GT9x_TP3 0x8160   /*!< 第三个触摸点数据地址 */
#define GT9x_TP4 0x8168   /*!< 第四个触摸点数据地址 */
#define GT9x_TP5 0x8170   /*!< 第五个触摸点数据地址 */

typedef struct _POINT
{
  uint16_t x;
  uint16_t y;
} POINT, * PPOINT;

typedef struct _GT911_POINT_DATA
{
  uint8_t cnt;
  POINT point;
} GT911_POINT_DATA, * PGT911_POINT_DATA;

typedef struct
{
  uint16_t x;     /*!< 当前x坐标 */
  uint16_t y;     /*!< 当前y坐标 */
  uint8_t status; /*!< 触摸状态 */
  uint16_t sta;
} tp_dev_t;

void GT911_Init(void);
void GT911_Read_XY(tp_dev_t * tp_devx);

#endif
