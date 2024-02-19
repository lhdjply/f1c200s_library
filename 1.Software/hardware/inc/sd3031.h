#ifndef __SD3031_H__
#define __SD3031_H__
#include "sys.h"
#include "delay.h"

#define SD3031_ADDR 0x32

#define SD3031_IIC I2C2

typedef struct
{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;

  uint16_t year;
  uint8_t  month;
  uint8_t  day;
  uint8_t  week;
} RTC_TIME;

int8_t SD3031_Init(void);
void Get_SD3031_Time(RTC_TIME * calendar);
void Set_SD3031_Time(RTC_TIME * set_calendar); // 设置时间
#endif
