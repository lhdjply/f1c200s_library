#include "gt911.h"
#include "common.h"
#include "interrupt.h"

static void GT911_Write_Reg(uint16_t reg, uint8_t * buf, uint8_t len);
static void GT911_Read_Reg(uint16_t reg, uint8_t * buf, uint8_t len);
static uint8_t GT911_Send_Cfg(uint8_t mode);

tp_dev_t tp_dev;
uint8_t GT911_Cfg[184];
GT911_POINT_DATA gt911_data;

void GT911_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef I2C_InitStructure;

  CCU_BUS2_GatingClockCmd(CCU_BUS2Gating_I2C0, ENABLE);
  CCU_BUS2_GatingResetCmd(CCU_BUS2Gating_I2C0, ENABLE);

  GPIO_AF_Remap(GPIOE, GPIO_PinSource11, GPIO_AF_PE11_I2C0_SCK);
  GPIO_AF_Remap(GPIOE, GPIO_PinSource12, GPIO_AF_PE12_I2C0_SDA);

  // GT911_SCK,GT911_SDA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  // GT911_RST,GT911_INT
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  I2C_DeInit(GT911_I2C);
  I2C_InitStructure.SlaveAddress = GT_CMD_ADDR;
  I2C_InitStructure.ClockSpeed = 400 * 1000;
  I2C_Init(GT911_I2C, &I2C_InitStructure);

  I2C_Cmd(GT911_I2C, ENABLE);

  GT911_RST = 0;
  GT911_INT = 1;
  delay_ms(1);
  GT911_RST = 1;
  delay_ms(6);
  GT911_INT = 0;
  delay_ms(55);

  // GT911_INT设为输入模式
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  delay_ms(50);

  GT911_Read_Reg(GT_CFGS_REG, GT911_Cfg, 184);
  if(GT911_Cfg[0] != 0xff &&
     (GT911_Cfg[1] != GTP_SET_WIDTH_L_Byte ||
      GT911_Cfg[2] != GTP_SET_WIDTH_H_Byte ||
      GT911_Cfg[3] != GTP_SET_HEIGHT_L_Byte ||
      GT911_Cfg[4] != GTP_SET_HEIGHT_H_Byte))
  {
    GT911_Cfg[0] = GT911_Cfg[0] + 1;
    GT911_Cfg[1] = GTP_SET_WIDTH_L_Byte;
    GT911_Cfg[2] = GTP_SET_WIDTH_H_Byte;
    GT911_Cfg[3] = GTP_SET_HEIGHT_L_Byte;
    GT911_Cfg[4] = GTP_SET_HEIGHT_H_Byte;
    GT911_Send_Cfg(1);
  }
  delay_ms(10);
}

// reg:起始寄存器地址
// buf:数据缓缓存区
// len:写数据长度
static void GT911_Write_Reg(uint16_t reg, uint8_t * buf, uint8_t len)
{
  I2C_SetSlaveAddress(GT911_I2C, GT_CMD_ADDR);
  I2C_Write_Reg(GT911_I2C, I2C_REG_SIZE_16BIT, reg, buf, len);
}

// reg:起始寄存器地址
// buf:数据缓缓存区
// len:读数据长度
static void GT911_Read_Reg(uint16_t reg, uint8_t * buf, uint8_t len)
{
  I2C_SetSlaveAddress(GT911_I2C, GT_CMD_ADDR);
  I2C_Read_Reg(GT911_I2C, I2C_REG_SIZE_16BIT, reg, buf, len);
}

// 发送配置参数
//  mode:0,参数不保存到flash
//      1,参数保存到flash
static uint8_t GT911_Send_Cfg(uint8_t mode)
{
  uint8_t buf[2];
  uint8_t i = 0;
  buf[0] = 0;
  buf[1] = mode; // 是否写入到GT911 FLASH?  即是否掉电保存
  for(i = 0; i < sizeof(GT911_Cfg); i++)
  {
    buf[0] += GT911_Cfg[i]; // 计算校验和
  }
  buf[0] = (~buf[0]) + 1;
  GT911_Write_Reg(GT_CFGS_REG, (uint8_t *)GT911_Cfg, sizeof(GT911_Cfg)); // 发送寄存器配置
  GT911_Write_Reg(GT_CHECK_REG, buf, 2);                                 // 写入校验和,和配置更新标记
  return 0;
}

static void GetPointData(uint8_t cnt, uint8_t data[])
{
  gt911_data.point.x = data[0x03] << 8 | data[0x02];
  gt911_data.point.y = data[0x05] << 8 | data[0x04];
}

void GT911_Read_XY(tp_dev_t * tp_devx)
{
  uint8_t g_touchPointInfor[6];
  uint8_t tmp;
  GT911_Read_Reg(0x814E, g_touchPointInfor, 0x06);
  tmp = g_touchPointInfor[0];
  if((tmp & 0x80) && ((tmp & 0x0f) > 0) && (tmp != 0xff))
  {
    tp_devx->status = 1;
    GetPointData(tmp & 0x0f, g_touchPointInfor);

    tp_devx->x = gt911_data.point.x;
    tp_devx->y = gt911_data.point.y;
  }
  else
  {
    tp_devx->status = 0;
  }
  tmp = 0;
  GT911_Write_Reg(0x814E, &tmp, 1);
}
