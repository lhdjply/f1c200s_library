#include "sd3031.h"

static void SD3031_I2C_Config(void);
static uint8_t SD3031_BCD2HEX(uint8_t val);
static uint16_t SD3031_B_BCD(uint8_t val);
static void SD3031_WriteTimeOn(void);
static void SD3031_WriteTimeOff(void);
static uint8_t SD3031_CaculateWeek(uint16_t year, uint8_t month, uint8_t day);
static void SD3031_Write_Reg(uint8_t reg, uint8_t * buf, uint8_t len);
static void SD3031_Read_Reg(uint8_t reg, uint8_t * buf, uint8_t len);

int8_t SD3031_Init(void)
{
  uint8_t temp;
  SD3031_I2C_Config();
  SD3031_Write_Reg(0x12, &temp, 1);
  if(temp == 0xff)
  {
    return -1;
  }
  else
  {
    temp = 0x80;
    SD3031_Write_Reg(0x10, &temp, 1);
    temp = 0x84;
    SD3031_Write_Reg(0x0f, &temp, 1);
    return 0;
  }
}

static void SD3031_I2C_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef I2C_InitStructure;

  CCU_BUS2_GatingClockCmd(CCU_BUS2Gating_I2C2, ENABLE);
  CCU_BUS2_GatingResetCmd(CCU_BUS2Gating_I2C2, ENABLE);

  GPIO_AF_Remap(GPIOE, GPIO_PinSource0, GPIO_AF_PE0_I2C2_SCK);
  GPIO_AF_Remap(GPIOE, GPIO_PinSource1, GPIO_AF_PE1_I2C2_SDA);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  I2C_DeInit(SD3031_IIC);
  I2C_InitStructure.SlaveAddress = SD3031_ADDR;
  I2C_InitStructure.ClockSpeed = 400 * 1000;
  I2C_Init(SD3031_IIC, &I2C_InitStructure);

  I2C_Cmd(SD3031_IIC, ENABLE);
}

static uint8_t SD3031_BCD2HEX(uint8_t val)
{
  uint8_t i;
  i = val & 0x0f;
  val >>= 4;
  val &= 0x0f;
  val *= 10;
  i += val;

  return i;
}

static uint16_t SD3031_B_BCD(uint8_t val)
{
  uint8_t i, j, k;
  i = val / 10;
  j = val % 10;
  k = j + (i << 4);
  return k;
}

static void SD3031_WriteTimeOn(void)
{
  uint8_t temp;
  temp = 0x80;
  SD3031_Write_Reg(0x10, &temp, 1);
  temp = 0xff;
  SD3031_Write_Reg(0x0f, &temp, 1);
}

static void SD3031_WriteTimeOff(void)
{
  uint8_t temp;
  temp = 0x7b;
  SD3031_Write_Reg(0x0f, &temp, 1);
  temp = 0x00;
  SD3031_Write_Reg(0x10, &temp, 1);
}

void Set_SD3031_Time(RTC_TIME * set_calendar)
{
  uint8_t temp[7];
  temp[0] = SD3031_B_BCD(set_calendar->second);
  temp[1] = SD3031_B_BCD(set_calendar->minute);
  temp[2] = SD3031_B_BCD(set_calendar->hour) | 0x80;
  temp[3] = SD3031_B_BCD(SD3031_CaculateWeek(set_calendar->year,
                                             set_calendar->month,
                                             set_calendar->day));
  temp[4] = SD3031_B_BCD(set_calendar->day);
  temp[5] = SD3031_B_BCD(set_calendar->month);
  temp[6] = SD3031_B_BCD(set_calendar->year - 2000);

  SD3031_WriteTimeOn();
  SD3031_Write_Reg(0x00, temp, 7);
  SD3031_WriteTimeOff();
}

void Get_SD3031_Time(RTC_TIME * calendar)
{
  uint8_t temp[7];
  SD3031_Read_Reg(0x00, temp, 7);
  calendar->second = SD3031_BCD2HEX(temp[0]);
  calendar->minute = SD3031_BCD2HEX(temp[1]);
  calendar->hour = SD3031_BCD2HEX(temp[2] & 0x3f);
  calendar->week = SD3031_BCD2HEX(temp[3]);
  calendar->day = SD3031_BCD2HEX(temp[4]);
  calendar->month = SD3031_BCD2HEX(temp[5]);
  calendar->year = SD3031_BCD2HEX(temp[6]) + 2000;

  if(calendar->second > 59)calendar->week = 59;
  if(calendar->minute > 59)calendar->week = 59;
  if(calendar->hour > 23)calendar->week = 23;
  if(calendar->week > 7)calendar->week = 7;
  if(calendar->day > 31)calendar->week = 31;
  if(calendar->month > 12)calendar->week = 12;

}

static uint8_t SD3031_CaculateWeek(uint16_t year, uint8_t month, uint8_t day)
{
  uint8_t Week;
  if(month == 1 || month == 2)
  {
    month += 12;
    year--;
  }
  Week = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7 + 1;
  return Week;
}

// reg:起始寄存器地址
// buf:数据缓缓存区
// len:写数据长度
static void SD3031_Write_Reg(uint8_t reg, uint8_t * buf, uint8_t len)
{
  I2C_SetSlaveAddress(SD3031_IIC, SD3031_ADDR);
  I2C_Write_Reg(SD3031_IIC, I2C_REG_SIZE_8BIT, reg, buf, len);
}

// reg:起始寄存器地址
// buf:数据缓缓存区
// len:读数据长度
static void SD3031_Read_Reg(uint8_t reg, uint8_t * buf, uint8_t len)
{
  I2C_SetSlaveAddress(SD3031_IIC, SD3031_ADDR);
  I2C_Read_Reg(SD3031_IIC, I2C_REG_SIZE_8BIT, reg, buf, len);
}
