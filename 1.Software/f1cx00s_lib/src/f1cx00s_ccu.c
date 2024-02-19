#include "f1cx00s_ccu.h"

/**
#define CCU_BUS0Gating_DMA (1<<4)
#define CCU_BUS0Gating_SD0 (1<<8)
#define CCU_BUS0Gating_SD1 (1<<9)
#define CCU_BUS0Gating_SDRAM (1<<14)
#define CCU_BUS0Gating_SPI0 (1<<20)
#define CCU_BUS0Gating_SPI1 (1<<21)
#define CCU_BUS0Gating_USB_OTG (1<<24)
**/
void CCU_BUS0_GatingResetCmd(uint32_t CCU_BUS0Gating, FunctionalState NewState)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if((CCU_BUS0Gating & (1 << i)) != 0)
    {
      if(NewState == ENABLE)
      {
        CCU->BUS_SOFT_RST0 = CCU->BUS_SOFT_RST0 | CCU_BUS0Gating;
      }
      else
      {
        CCU->BUS_SOFT_RST0 = CCU->BUS_SOFT_RST0 & (~CCU_BUS0Gating);
      }
    }
  }
}

/**
#define CCU_BUS1Gating_VE (1<<0)
#define CCU_BUS1Gating_LCD (1<<4)
#define CCU_BUS1Gating_DEINTERLACE (1<<5)
#define CCU_BUS1Gating_CSI (1<<8)
#define CCU_BUS1Gating_TVD (1<<9)
#define CCU_BUS1Gating_TVE (1<<10)
#define CCU_BUS1Gating_DEBE (1<<12)
#define CCU_BUS1Gating_DEFE (1<<14)
**/
void CCU_BUS1_GatingResetCmd(uint32_t CCU_BUS1Gating, FunctionalState NewState)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if((CCU_BUS1Gating & (1 << i)) != 0)
    {
      if(NewState == ENABLE)
      {
        CCU->BUS_SOFT_RST1 = CCU->BUS_SOFT_RST1 | CCU_BUS1Gating;
      }
      else
      {
        CCU->BUS_SOFT_RST1 = CCU->BUS_SOFT_RST1 & (~CCU_BUS1Gating);
      }
    }
  }
}

/**
#define CCU_BUS2Gating_AUDIO_CODEC (1<<0)
#define CCU_BUS2Gating_OWA (1<<1)
#define CCU_BUS2Gating_CIR (1<<2)
#define CCU_BUS2Gating_RSB (1<<3)
#define CCU_BUS2Gating_DAUDIO (1<<12)
#define CCU_BUS2Gating_TWI0 (1<<16)
#define CCU_BUS2Gating_TWI1 (1<<17)
#define CCU_BUS2Gating_TWI2 (1<<18)
#define CCU_BUS2Gating_UART0 (1<<20)
#define CCU_BUS2Gating_UART1 (1<<21)
#define CCU_BUS2Gating_UART2 (1<<22)
**/
void CCU_BUS2_GatingResetCmd(uint32_t CCU_BUS2Gating, FunctionalState NewState)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if((CCU_BUS2Gating & (1 << i)) != 0)
    {
      if(NewState == ENABLE)
      {
        CCU->BUS_SOFT_RST2 = CCU->BUS_SOFT_RST2 | CCU_BUS2Gating;
      }
      else
      {
        CCU->BUS_SOFT_RST2 = CCU->BUS_SOFT_RST2 & (~CCU_BUS2Gating);
      }
    }
  }
}

/**
#define CCU_BUS0Gating_DMA (1<<4)
#define CCU_BUS0Gating_SD0 (1<<8)
#define CCU_BUS0Gating_SD1 (1<<9)
#define CCU_BUS0Gating_SDRAM (1<<14)
#define CCU_BUS0Gating_SPI0 (1<<20)
#define CCU_BUS0Gating_SPI1 (1<<21)
#define CCU_BUS0Gating_USB_OTG (1<<24)
**/
void CCU_BUS0_GatingClockCmd(uint32_t CCU_BUS0Gating, FunctionalState NewState)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if((CCU_BUS0Gating & (1 << i)) != 0)
    {
      if(NewState == ENABLE)
      {
        CCU->BUS_CLK_GATING0 = CCU->BUS_CLK_GATING0 | CCU_BUS0Gating;
      }
      else
      {
        CCU->BUS_CLK_GATING0 = CCU->BUS_CLK_GATING0 & (~CCU_BUS0Gating);
      }
    }
  }
}

/**
#define CCU_BUS1Gating_VE (1<<0)
#define CCU_BUS1Gating_LCD (1<<4)
#define CCU_BUS1Gating_DEINTERLACE (1<<5)
#define CCU_BUS1Gating_CSI (1<<8)
#define CCU_BUS1Gating_TVD (1<<9)
#define CCU_BUS1Gating_TVE (1<<10)
#define CCU_BUS1Gating_DEBE (1<<12)
#define CCU_BUS1Gating_DEFE (1<<14)
**/
void CCU_BUS1_GatingClockCmd(uint32_t CCU_BUS1Gating, FunctionalState NewState)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if((CCU_BUS1Gating & (1 << i)) != 0)
    {
      if(NewState == ENABLE)
      {
        CCU->BUS_CLK_GATING1 = CCU->BUS_CLK_GATING1 | CCU_BUS1Gating;
      }
      else
      {
        CCU->BUS_CLK_GATING1 = CCU->BUS_CLK_GATING1 & (~CCU_BUS1Gating);
      }
    }
  }
}

/**
#define CCU_BUS2Gating_AUDIO_CODEC (1<<0)
#define CCU_BUS2Gating_OWA (1<<1)
#define CCU_BUS2Gating_CIR (1<<2)
#define CCU_BUS2Gating_RSB (1<<3)
#define CCU_BUS2Gating_DAUDIO (1<<12)
#define CCU_BUS2Gating_TWI0 (1<<16)
#define CCU_BUS2Gating_TWI1 (1<<17)
#define CCU_BUS2Gating_TWI2 (1<<18)
#define CCU_BUS2Gating_UART0 (1<<20)
#define CCU_BUS2Gating_UART1 (1<<21)
#define CCU_BUS2Gating_UART2 (1<<22)
**/
void CCU_BUS2_GatingClockCmd(uint32_t CCU_BUS2Gating, FunctionalState NewState)
{
  uint8_t i = 0;
  for(i = 0; i < 32; i++)
  {
    if((CCU_BUS2Gating & (1 << i)) != 0)
    {
      if(NewState == ENABLE)
      {
        CCU->BUS_CLK_GATING2 = CCU->BUS_CLK_GATING2 | CCU_BUS2Gating;
      }
      else
      {
        CCU->BUS_CLK_GATING2 = CCU->BUS_CLK_GATING2 & (~CCU_BUS2Gating);
      }
    }
  }
}

void CCU_FE_ClockCmd(FunctionalState NewState)
{
  if(NewState == ENABLE)
  {
    CCU->FE_CLK = CCU->FE_CLK | 0x80000000;
  }
  else
  {
    CCU->FE_CLK = CCU->FE_CLK & 0x7FFFFFFF;
  }
}

void CCU_BE_ClockCmd(FunctionalState NewState)
{
  if(NewState == ENABLE)
  {
    CCU->BE_CLK = CCU->BE_CLK | 0x80000000;
  }
  else
  {
    CCU->BE_CLK = CCU->BE_CLK & 0x7FFFFFFF;
  }
}

void CCU_DRAM_ClockCmd(CCU_DRAM_GATE dram_gate, FunctionalState NewState)
{
  if(NewState == ENABLE)
  {
    CCU->DRAM_GATING |= (0x01 << dram_gate);
  }
  else
  {
    CCU->DRAM_GATING &= ~(0x01 << dram_gate);
  }
}

void CCU_TCON_ClockCmd(FunctionalState NewState)
{
  if(NewState == ENABLE)
  {
    CCU->TCON_CLK = CCU->TCON_CLK | 0x80000000;
  }
  else
  {
    CCU->TCON_CLK = CCU->TCON_CLK & 0x7FFFFFFF;
  }
}

static uint32_t Wait_Pll_Stable(uint32_t base)
{
  uint32_t rval = 0;
  volatile int time = 0xfff;

  do
  {
    rval = *((volatile uint32_t *)base);
    time--;
  } while(time && !(rval & (1 << 28)));

  return !time;
}

uint32_t CPU_Get_Pll_Clk(void)
{
  uint32_t reg;
  uint32_t n, k, m, p;

  reg = CCU->PLL_CPU_CTRL;
  if(!(reg & (0x01 << 31)))
    return 0;

  p = ((reg >> 16) & 0x3) + 1;
  n = ((reg >> 8) & 0x1f) + 1;
  k = ((reg >> 4) & 0x3) + 1;
  m = ((reg) & 0x3) + 1;
  //(24MHz*n*k)/(m*p)
  return (24000000 * n * k) / (m * p);
}

int8_t CPU_Set_Pll_Clk(uint32_t clk)
{
  uint32_t cpu_src;
  uint32_t p = 0, k = 1, m = 1, n = 0;

  if(clk == 0)
    return -1;

  if(clk > 1152000000)
  {
    k = 2;
  }
  else if(clk > 768000000)
  {
    k = 3;
    m = 2;
  }

  n = clk / (24000000 * k / m) - 1;
  cpu_src = (CCU->CPU_CLK_SRC >> 16) & 0x3;
  CCU->CPU_CLK_SRC = CCU_CLK_OSC24M_SRC << 16;
  CCU->PLL_CPU_CTRL &= ~(0x1 << 31);
  // PLL1 rate = ((24000000 * n * k) >> 0) / m   (p is ignored)
  CCU->PLL_CPU_CTRL = (0x1 << 31) | (m << 0) | (k << 4) | (n << 8) | (p << 16);
  if(Wait_Pll_Stable((uint32_t)(&CCU->PLL_CPU_CTRL)))
    return -1;

  CCU->CPU_CLK_SRC = cpu_src << 16;

  return 0;
}

uint32_t Audio_Get_Pll_Clk(void)
{
  uint32_t reg;
  uint8_t n, m;

  reg = CCU->PLL_AUDIO_CTRL;
  if(!(reg & (0x01 << 31)))
    return 0;

  n = ((reg >> 8) & 0x7f) + 1;
  m = ((reg) & 0x1f) + 1;

  // 24MHz*n*2/m
  return 24000000 * 2 * n / m;
}

int8_t Audio_Set_Pll_Clk(uint32_t clk)
{
  int n = 0, m = 0;
  int n_temp = clk;
  int m_temp = 24000000 * 2;

  if((clk > 200000000) || (clk < 20000000))
    return -1;

  if(clk == 0)
  {
    CCU->PLL_AUDIO_CTRL &= ~(0x1 << 31);
    return 0;
  }

  while(n_temp != m_temp)
  {
    if(n_temp > m_temp)
    {
      n_temp = n_temp - m_temp;
    }
    else if(m_temp > n_temp)
    {
      m_temp = m_temp - n_temp;
    }
  }

  n = clk / n_temp;
  m = 24000000 * 2 / m_temp;
  if((n > 128) || (m > 32) || (clk != (24000000 * n * 2) / m))
    return -1;

  CCU->PLL_AUDIO_CTRL &= ~(0x1 << 31);
  n = (n - 1) & 0x7f;
  m = (m - 1) & 0x1f;
  // clk = (24 * n * 2) / m
  CCU->PLL_AUDIO_CTRL = (0x1 << 31) | (0x0 << 24) | (n << 8) | m;

  if(Wait_Pll_Stable((uint32_t)(&CCU->PLL_AUDIO_CTRL)))
    return -1;
  else
    return 0;
}

uint32_t Video_Get_Pll_Clk(void)
{
  uint32_t reg;
  uint32_t n, m;

  reg = CCU->PLL_VIDEO_CTRL;
  if(!(reg & (0x01 << 31)))
    return 0;

  if(reg & (0x1 << 24))
  {
    //(24MHz*n)/m
    n = ((reg >> 8) & 0x7f) + 1;
    m = (reg & 0xf) + 1;
    return (24000000 * n) / m;
  }

  if(reg & (0x1 << 25))
    return 270000000;
  else
    return 297000000;

  return 0;
}

int8_t Video_Set_Pll_Clk(uint32_t clk)
{
  uint32_t n = 0, m = 0;
  uint32_t n_temp = clk;
  uint32_t m_temp = 24000000;

  if((clk > 600000000) || (clk < 30000000))
    return -1;

  if(clk == 0)
  {
    CCU->PLL_VIDEO_CTRL &= ~(0x1 << 31);
    return 0;
  }

  while(n_temp != m_temp)
  {
    if(n_temp > m_temp)
    {
      n_temp = n_temp - m_temp;
    }
    else if(m_temp > n_temp)
    {
      m_temp = m_temp - n_temp;
    }
  }

  n = clk / n_temp;
  m = 24000000 / m_temp;

  if((n > 128) || (m > 16) || (clk != (24000000 * n) / m))
    return -1;

  CCU->PLL_VIDEO_CTRL &= ~(0x1 << 31);
  n = (n - 1) & 0x7f;
  m = (m - 1) & 0xf;
  // speed = (24*n)/m
  CCU->PLL_VIDEO_CTRL = (0x1 << 31) | (0x0 << 30) | (0x1 << 24) | (n << 8) | m;

  if(Wait_Pll_Stable((uint32_t)(&CCU->PLL_VIDEO_CTRL)))
    return -1;
  else
    return 0;
}

uint32_t VE_Get_Pll_Clk(void)
{
  uint32_t reg;
  uint32_t n, m;

  reg = CCU->PLL_VE_CTRL;
  if(!(reg & (0x01 << 31)))
    return 0;

  if(reg & (0x1 << 24))
  {
    //(24MHz*n)/m
    n = ((reg >> 8) & 0x7f) + 1;
    m = (reg & 0xf) + 1;

    return (24000000 * n) / m;
  }

  if(reg & (0x1 << 25))
    return 297000000;
  else
    return 270000000;

  return 0;
}

int8_t VE_Set_Pll_Clk(uint32_t clk)
{
  uint32_t n = 0, m = 0;
  uint32_t n_temp = clk;
  uint32_t m_temp = 24000000;

  if((clk > 600000000) || (clk < 30000000))
    return -1;

  if(clk == 0)
  {
    CCU->PLL_VE_CTRL &= ~(0x1 << 31);
    return 0;
  }

  while(n_temp != m_temp)
  {
    if(n_temp > m_temp)
    {
      n_temp = n_temp - m_temp;
    }
    else if(m_temp > n_temp)
    {
      m_temp = m_temp - n_temp;
    }
  }

  n = clk / n_temp;
  m = 24000000 / m_temp;

  if((n > 128) || (m > 16) || (clk != (24000000 * n) / m))
    return -1;

  CCU->PLL_VE_CTRL &= ~(0x1 << 31);
  n = (n - 1) & 0x7f;
  m = (m - 1) & 0xf;
  // clk = (24 * n) / m
  CCU->PLL_VE_CTRL = (0x1 << 31) | (0x1 << 24) | (n << 8) | m;
  if(Wait_Pll_Stable((uint32_t)(&CCU->PLL_VE_CTRL)))
    return -1;
  else
    return 0;
}

uint32_t DDR_Get_Pll_Clk(void)
{
  uint32_t reg;
  int n, k, m;

  reg = CCU->PLL_DDR_CTRL;
  if(!(reg & (0x01 << 31)))
    return 0;

  n = ((reg >> 8) & 0x1f) + 1;
  k = ((reg >> 4) & 0x3) + 1;
  m = ((reg) & 0x3) + 1;

  //(24MHz*n*k)/m
  return (24000000 * n * k) / m;
}

uint32_t Periph_Get_Pll_Clk(void)
{
  uint32_t reg;
  uint32_t n, k;

  reg = CCU->PLL_PERIPH_CTRL;
  if(!(reg & (0x01 << 31)))
    return 0;

  n = ((reg >> 8) & 0x1f) + 1;
  k = ((reg >> 4) & 0x3) + 1;

  return 24000000 * n * k;
}

int8_t Periph_Set_Pll_Clk(uint32_t clk)
{
  uint32_t clk_src;
  uint32_t temp_data;
  uint32_t n = 0, k = 0;

  if((clk > 1800000000) || (clk < 200000000) || (clk == 0) || (clk % 24000000 != 0))
    return -1;

  n = clk / 24000000;

  for(k = 2; ((n > 32) || (k < 5)); k++)
  {
    if((n % k) != 0)
      n /= k;
  }

  if((n > 32) || (k > 4) || (clk != (24000000 * n * k)))
    return -1;
  temp_data = CCU->AHB_APB_HCLKC_CFG;
  clk_src = (temp_data >> 12) & 0x3;
  temp_data &= ~(0x3 << 12);
  temp_data |= (CCU_CLK_PLL_SRC << 12);
  CCU->AHB_APB_HCLKC_CFG = temp_data;
  CCU->PLL_PERIPH_CTRL &= ~(0x1 << 31);
  n = (n - 1) & 0x1f;
  k = (k - 1) & 0x3;
  // clk = 24 * n *k
  CCU->PLL_PERIPH_CTRL = (0x1 << 31) | (0x1 << 18) | (n << 8) | (k << 4) || (0x1);
  if(Wait_Pll_Stable((uint32_t)(&CCU->PLL_PERIPH_CTRL)))
    return -1;

  temp_data = CCU->AHB_APB_HCLKC_CFG;
  temp_data &= ~(0x3 << 12);
  temp_data |= (clk_src << 12);
  CCU->AHB_APB_HCLKC_CFG = temp_data;

  return 0;
}

static int CPU_Get_Clk_Src(void)
{
  return (CCU->CPU_CLK_SRC >> 16) & 0x3;
}

uint32_t CPU_Get_Clk(void)
{
  uint32_t reg;
  uint32_t cpusrc;

  reg = CCU->AHB_APB_HCLKC_CFG;
  cpusrc = CPU_Get_Clk_Src();

  if(cpusrc == CCU_CLK_PLL_SRC)
    return (CPU_Get_Pll_Clk() / (((reg >> 16) & 0x3) + 1));
  else if(cpusrc == CCU_CLK_OSC24M_SRC)
    return 24000000 / (((reg >> 16) & 0x3) + 1);
  else
    return 32000 / (((reg >> 16) & 0x3) + 1); // 猜测 内部32KHz时钟

  return 0;
}

int8_t CPU_Set_Clk(uint32_t clk)
{
  if(clk < 24000000)
    return -1;

  if(clk == CPU_Get_Clk())
    return 0;

  CCU->CPU_CLK_SRC = CCU_CLK_OSC24M_SRC << 16;
  if(clk == 24000000)
    return 0;

  if(CPU_Set_Pll_Clk(clk))
    return -1;

  CCU->AHB_APB_HCLKC_CFG &= ~(0x3 << 16);
  CCU->CPU_CLK_SRC = CCU_CLK_PLL_SRC << 16;

  return 0;
}

uint32_t AHB_Get_Clk(void)
{
  uint32_t reg;
  uint32_t sel, spd;

  reg = CCU->AHB_APB_HCLKC_CFG;
  sel = ((reg >> 12) & 0x3);

  if(sel == CCU_CLK_PLL_SRC)
  {
    spd = CPU_Get_Clk();
    return spd / (1 << ((reg >> 4) & 0x3));
  }
  else if(sel == CCU_PRE_DIV_SRC)
  {
    spd = Periph_Get_Pll_Clk();
    return spd / (((reg >> 6) & 0x3) + 1) / (1 << ((reg >> 4) & 0x3));
  }
  else if(sel == CCU_CLK_OSC24M_SRC)
    return 24000000 / (1 << ((reg >> 4) & 0x3));
  else
    return 32000 / (1 << ((reg >> 4) & 0x3));
}

uint32_t APB_Get_clk(void)
{
  uint32_t reg;
  uint32_t spd;

  reg = CCU->AHB_APB_HCLKC_CFG;
  spd = AHB_Get_Clk();
  // 0x:/2 10:/4 11:/8
  if(!(((reg >> 8) & 0x3) & 0x1))
    return spd / 2;
  else
    return spd / (1 << ((reg >> 8) & 0x3));
}
