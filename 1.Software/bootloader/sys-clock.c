#include <stdint.h>
#include <delay.h>
#include <io.h>

static void wait_pll_stable(uint32_t base)
{
  uint32_t rval = 0;
  uint32_t time = 0xfff;

  do
  {
    rval = read32(base);
    time--;
  } while(time && !(rval & (1 << 28)));
}

static void clock_set_pll_cpu(uint32_t clk)
{
  uint32_t n, k, m, p;
  uint32_t rval = 0;
  uint32_t div = 0;

  if(clk > 720000000)
    clk = 720000000;

  if((clk % 24000000) == 0)
  {
    div = clk / 24000000;
    n = div - 1;
    k = 0;
    m = 0;
    p = 0;
  }
  else if((clk % 12000000) == 0)
  {
    m = 1;
    div = clk / 12000000;
    if((div % 3) == 0)
      k = 2;
    else if((div % 4) == 0)
      k = 3;
    else
      k = 1;
    n = (div / (k + 1)) - 1;
    p = 0;
  }
  else
  {
    div = clk / 24000000;
    n = div - 1;
    k = 0;
    m = 0;
    p = 0;
  }

  rval = CCU->PLL_CPU_CTRL;
  rval &= ~((0x3 << 16) | (0x1f << 8) | (0x3 << 4) | (0x3 << 0));
  rval |= (1U << 31) | (p << 16) | (n << 8) | (k << 4) | m;
  CCU->PLL_CPU_CTRL = rval;
  wait_pll_stable((uint32_t) & (CCU->PLL_CPU_CTRL));
}

void sys_clock_init(void)
{
  uint32_t val;

  CCU->PLL_STABLE_TIME0 = 0x1ff;
  CCU->PLL_STABLE_TIME1 = 0x1ff;

  val = CCU->CPU_CLK_SRC;
  val &= ~(0x3 << 16);
  val |= (0x1 << 16);
  CCU->CPU_CLK_SRC = val;
  delay_unit(100);

  CCU->PLL_VIDEO_CTRL = 0x81004107;
  delay_unit(100);
  CCU->PLL_PERIPH_CTRL = 0x80041800;
  delay_unit(100);
  CCU->AHB_APB_HCLKC_CFG = 0x00003180;
  delay_unit(100);

  val = CCU->DRAM_GATING;
  val |= (0x1 << 26) | (0x1 << 24);
  CCU->DRAM_GATING = val;
  delay_unit(100);

  clock_set_pll_cpu(408000000);
  val = CCU->CPU_CLK_SRC;
  val &= ~(0x3 << 16);
  val |= (0x2 << 16);
  CCU->CPU_CLK_SRC = val;
  delay_unit(100);
}
