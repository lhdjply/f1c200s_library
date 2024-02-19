#include "f1cx00s_sdio.h"
#include "f1cx00s_ccu.h"
#include "delay.h"

static int SDIO_Transfer_data(SDIO_TypeDef * SDIOx, SDIO_XFEInitTypeDef * xfe);

int8_t SDIO_Set_Clk(SDIO_TypeDef * SDIOx, uint32_t hz)
{
  uint32_t pll, pll_hz, div, n, oclk_dly, sclk_dly;
  volatile uint32_t * mmc_clk = (SDIOx == SDIO0) ? (&CCU->SDMMC0_CLK) : (&CCU->SDMMC1_CLK);

  if(hz < 0)
  {
    return -1;
  }

  if(hz == 0)
  {
    *mmc_clk &= ~(0x1 << 31);
    return 0;
  }

  if(hz <= 24000000)
  {
    pll = (0x0 << 24);
    pll_hz = 24000000;
  }
  else
  {
    pll = (0x1 << 24);
    pll_hz = Periph_Get_Pll_Clk();
  }

  div = pll_hz / hz;
  if(pll_hz % hz)
  {
    div++;
  }

  n = 0;
  while(div > 16)
  {
    n++;
    div = (div + 1) / 2;
  }

  if(n > 3)
  {
    return -1;
  }

  /* determine delays */
  if(hz <= 400000)
  {
    oclk_dly = 0;
    sclk_dly = 0;
  }
  else if(hz <= 25000000)
  {
    oclk_dly = 0;
    sclk_dly = 5;
  }
  else if(hz <= 50000000)
  {
    oclk_dly = 3;
    sclk_dly = 4;
  }
  else
  {
    /* hz > 50000000 */
    oclk_dly = 1;
    sclk_dly = 4;
  }

  *mmc_clk = (0x1 << 31) | pll | (sclk_dly << 20) |
             (n << 16) | (oclk_dly << 8) | (div - 1);

  return 0;
}

static int8_t SDIO_Update_Clk(SDIO_TypeDef * SDIOx)
{
  uint32_t cmd;
  uint32_t timeout = 2000000;

  /* cmd load */
  cmd = SDXC_LOAD_CMD | SDXC_UPDATE_CLOCK_CMD | SDXC_WAIT_OVER_CMD;
  SDIOx->CMDR = cmd;
  /* while load success */
  while((SDIOx->CMDR & SDXC_LOAD_CMD) && (--timeout))
  {
    delay_us(1);
  }
  if(!timeout)
  {
    return -1;
  }
  /* clean interrupt */
  SDIOx->RISR = SDIOx->RISR;
  return 0;
}

int8_t SDIO_Config_Clock(SDIO_TypeDef * SDIOx, int clk)
{
  uint32_t rval = 0;

  /* disable card clock */
  rval = SDIOx->CKCR;
  rval &= ~(1 << 16);
  SDIOx->CKCR = rval;

  if(SDIO_Update_Clk(SDIOx) != 0)
  {
    return -1;
  }
  SDIO_Set_Clk(SDIOx, clk);

  /* Re-enable card clock */
  rval = SDIOx->CKCR;
  rval |= (0x1 << 16); //(3 << 16);
  SDIOx->CKCR = rval;

  if(SDIO_Update_Clk(SDIOx) != 0)
  {
    return -1;
  }

  return 0;
}

int8_t SDIO_Set_Ios(SDIO_TypeDef * SDIOx, int clk, int bus_width)
{
  /* change clock */

  if(clk && (SDIO_Config_Clock(SDIOx, clk) != 0))
  {
    return -1;
  }

  /* Change bus width */
  if(bus_width == MMCSD_BUS_WIDTH_8)
  {
    SDIOx->BWDR = 2;
  }
  else if(bus_width == MMCSD_BUS_WIDTH_4)
  {
    SDIOx->BWDR = 1;
  }
  else
  {
    SDIOx->BWDR = 0;
  }
  return 0;
}

uint32_t SDIO_Get_STA(SDIO_TypeDef * SDIOx)
{
  return SDIOx->STAR;
}

static int SDIO_Transfer_data(SDIO_TypeDef * SDIOx, SDIO_XFEInitTypeDef * xfe)
{
  unsigned i;
  unsigned byte_cnt = xfe->size * xfe->num;
  unsigned * buff = (unsigned *)(xfe->buff);
  volatile unsigned timeout = 2000000;

  if(xfe->flag == SDIO_DATA_DIR_WRITE)
  {
    for(i = 0; i < (byte_cnt >> 2); i++)
    {
      while(--timeout && (SDIOx->STAR & (1 << 3)))
      {
      }
      if(timeout <= 0)
      {
        return -1;
      }
      SDIOx->FIFO = buff[i];
      timeout = 2000000;
    }
  }
  else if(xfe->flag == SDIO_DATA_DIR_READ)
  {
    for(i = 0; i < (byte_cnt >> 2); i++)
    {
      while(--timeout && (SDIOx->STAR & (1 << 2)))
      {
      }
      if(timeout <= 0)
      {
        return -1;
      }
      buff[i] = SDIOx->FIFO;
      timeout = 2000000;
    }
  }
  return 0;
}

int8_t SDIO_SendCommand(SDIO_TypeDef * SDIOx,
                        SDIO_CmdInitTypeDef * SDIO_CmdInitStruct,
                        uint32_t us)
{
  uint32_t cmdval = 0x80000000;
  int32_t timeout = 0;
  uint32_t status = 0;

  timeout = 500 * 1000;
  status = SDIOx->STAR;
  while(status & (1 << 9))
  {
    status = SDIOx->STAR;
    if(!timeout--)
    {
      return -1;
    }
    delay_us(1);
  }
  if(!SDIO_CmdInitStruct->SDIO_CmdIndex)
    cmdval |= (1 << 15);
  if(SDIO_Resp_Type(SDIO_CmdInitStruct) != SDIO_RESP_NONE)
    cmdval |= (1 << 6);
  if(SDIO_Resp_Type(SDIO_CmdInitStruct) == SDIO_RESP_R2)
    cmdval |= (1 << 7);
  if((SDIO_Resp_Type(SDIO_CmdInitStruct) != SDIO_RESP_R3) && (SDIO_Resp_Type(SDIO_CmdInitStruct) != SDIO_RESP_R4))
    cmdval |= (1 << 8);
  if(us != 0)
  {
    delay_us(us);
  }
  SDIOx->CAGR = SDIO_CmdInitStruct->SDIO_Argument;
  SDIOx->CMDR = cmdval | SDIO_CmdInitStruct->SDIO_CmdIndex;
  SDIOx->IMKR |= 0x1 << 2;

  if(SDIO_Resp_Type(SDIO_CmdInitStruct) == SDIO_RESP_R2)
  {
    SDIO_CmdInitStruct->SDIO_Resp[3] = SDIOx->RESP0;
    SDIO_CmdInitStruct->SDIO_Resp[2] = SDIOx->RESP1;
    SDIO_CmdInitStruct->SDIO_Resp[1] = SDIOx->RESP2;
    SDIO_CmdInitStruct->SDIO_Resp[0] = SDIOx->RESP3;
  }
  else
  {
    SDIO_CmdInitStruct->SDIO_Resp[0] = SDIOx->RESP0;
  }
  SDIOx->GCTL &= ~(0x1 << 4);
  SDIOx->IMKR &= ~0xffff;
  SDIOx->RISR = 0xffffffff;
  SDIOx->GCTL |= (0x1 << 4);

  return 0;
}

int SDIO_SendCommand_and_Data(SDIO_TypeDef * SDIOx,
                              SDIO_DataInitTypeDef * SDIO_DataInitStruct,
                              SDIO_CmdInitTypeDef * SDIO_CmdInitStruct,
                              uint32_t us)
{
  uint32_t cmdval = 0x80000000;
  int32_t timeout = 0;
  uint32_t status = 0;
  uint32_t bytecnt = 0;
  SDIO_XFEInitTypeDef xfe;

  xfe.size = SDIO_DataInitStruct->blksize;
  xfe.num = SDIO_DataInitStruct->blks;
  xfe.buff = SDIO_DataInitStruct->buf;
  xfe.flag = SDIO_DataInitStruct->flags;

  timeout = 500 * 1000;
  status = SDIOx->STAR;
  while(status & (1 << 9))
  {
    status = SDIOx->STAR;
    if(!timeout--)
    {
      return -1;
    }
    delay_us(1);
  }

  if(!SDIO_CmdInitStruct->SDIO_CmdIndex)
    cmdval |= (1 << 15);
  if(SDIO_Resp_Type(SDIO_CmdInitStruct) != SDIO_RESP_NONE)
    cmdval |= (1 << 6);
  if(SDIO_Resp_Type(SDIO_CmdInitStruct) == SDIO_RESP_R2)
    cmdval |= (1 << 7);
  if((SDIO_Resp_Type(SDIO_CmdInitStruct) != SDIO_RESP_R3) && (SDIO_Resp_Type(SDIO_CmdInitStruct) != SDIO_RESP_R4))
    cmdval |= (1 << 8);
  if(us != 0)
  {
    delay_us(us);
  }

  if(SDIO_DataInitStruct != NULL)
  {
    cmdval |= (1 << 9) | (1 << 13);
    if(SDIO_DataInitStruct->flags & SDIO_DATA_DIR_WRITE)
    {
      cmdval |= (1 << 10);
    }
    if(SDIO_DataInitStruct->blks > 1)
    {
      cmdval |= (1 << 12);
    }
    SDIOx->BKSR = SDIO_DataInitStruct->blksize;
    bytecnt = SDIO_DataInitStruct->blksize * SDIO_DataInitStruct->blks;
    SDIOx->BYCR = bytecnt;
  }

  if(us != 0)
  {
    delay_us(us);
  }

  SDIOx->CAGR = SDIO_CmdInitStruct->SDIO_Argument;

  if(SDIO_DataInitStruct != NULL)
  {
    SDIOx->GCTL = SDIOx->GCTL | 0x80000000;
    SDIOx->CMDR = cmdval | SDIO_CmdInitStruct->SDIO_CmdIndex;
    SDIO_Transfer_data(SDIOx, &xfe);

    if(SDIO_DataInitStruct->blks > 1)
    {
      SDIOx->IMKR |= (0x1 << 14);
    }
    else
    {
      SDIOx->IMKR |= (0x1 << 3);
    }
  }
  SDIOx->IMKR |= 0xbfc2;
  if(SDIO_Resp_Type(SDIO_CmdInitStruct) == SDIO_RESP_R2)
  {
    SDIO_CmdInitStruct->SDIO_Resp[3] = SDIOx->RESP0;
    SDIO_CmdInitStruct->SDIO_Resp[2] = SDIOx->RESP1;
    SDIO_CmdInitStruct->SDIO_Resp[1] = SDIOx->RESP2;
    SDIO_CmdInitStruct->SDIO_Resp[0] = SDIOx->RESP3;
  }
  else
  {
    SDIO_CmdInitStruct->SDIO_Resp[0] = SDIOx->RESP0;
  }

  SDIOx->GCTL &= ~(0x1 << 4);
  SDIOx->IMKR &= ~0xffff;
  SDIOx->RISR = 0xffffffff;
  SDIOx->GCTL |= (0x1 << 4);
  return 0;
}
