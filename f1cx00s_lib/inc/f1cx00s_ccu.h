#ifndef __F1CX00S_CCU__H
#define __F1CX00S_CCU__H

#include "f1cx00s.h"

#define CCU_BUS0Gating_DMA (1 << 6)
#define CCU_BUS0Gating_SD0 (1 << 8)
#define CCU_BUS0Gating_SD1 (1 << 9)
#define CCU_BUS0Gating_SDRAM (1 << 14)
#define CCU_BUS0Gating_SPI0 (1 << 20)
#define CCU_BUS0Gating_SPI1 (1 << 21)
#define CCU_BUS0Gating_USB_OTG (1 << 24)
#define CCU_BUS1Gating_VE (1 << 0)
#define CCU_BUS1Gating_LCD (1 << 4)
#define CCU_BUS1Gating_DEINTERLACE (1 << 5)
#define CCU_BUS1Gating_CSI (1 << 8)
#define CCU_BUS1Gating_TVD (1 << 9)
#define CCU_BUS1Gating_TVE (1 << 10)
#define CCU_BUS1Gating_DEBE (1 << 12)
#define CCU_BUS1Gating_DEFE (1 << 14)
#define CCU_BUS2Gating_AUDIO_CODEC (1 << 0)
#define CCU_BUS2Gating_OWA (1 << 1)
#define CCU_BUS2Gating_CIR (1 << 2)
#define CCU_BUS2Gating_RSB (1 << 3)
#define CCU_BUS2Gating_DAUDIO (1 << 12)
#define CCU_BUS2Gating_I2C0 (1 << 16)
#define CCU_BUS2Gating_I2C1 (1 << 17)
#define CCU_BUS2Gating_I2C2 (1 << 18)
#define CCU_BUS2Gating_UART0 (1 << 20)
#define CCU_BUS2Gating_UART1 (1 << 21)
#define CCU_BUS2Gating_UART2 (1 << 22)

#define CCU_CLK_LOSC_SRC (0x00)
#define CCU_CLK_OSC24M_SRC (0x01)
#define CCU_CLK_PLL_SRC (0x02)
#define CCU_PRE_DIV_SRC (0x03)

typedef enum
{
  CCU_BE_GATING_DRAM = 26,
  CCU_FE_GATING_DRAM = 24,
  CCU_TVD_GATING_DRAM = 3,
  CCU_DEINTERLACE_GATING_DRAM = 2,
  CCU_CSI_GATING_DRAM = 1,
  CCU_VE_GATING_DRAM = 0
} CCU_DRAM_GATE;

void CCU_BUS0_GatingResetCmd(uint32_t CCU_BUS0Gating, FunctionalState NewState);
void CCU_BUS1_GatingResetCmd(uint32_t CCU_BUS0Gating, FunctionalState NewState);
void CCU_BUS2_GatingResetCmd(uint32_t CCU_BUS0Gating, FunctionalState NewState);
void CCU_BUS0_GatingClockCmd(uint32_t CCU_BUS0Gating, FunctionalState NewState);
void CCU_BUS1_GatingClockCmd(uint32_t CCU_BUS1Gating, FunctionalState NewState);
void CCU_BUS2_GatingClockCmd(uint32_t CCU_BUS2Gating, FunctionalState NewState);
void CCU_FE_ClockCmd(FunctionalState NewState);
void CCU_BE_ClockCmd(FunctionalState NewState);
void CCU_TCON_ClockCmd(FunctionalState NewState);
void CCU_DRAM_ClockCmd(CCU_DRAM_GATE dram_gate, FunctionalState NewState);

uint32_t CPU_Get_Pll_Clk(void);
int8_t CPU_Set_Pll_Clk(uint32_t clk);
uint32_t Audio_Get_Pll_Clk(void);
int8_t Audio_Set_Pll_Clk(uint32_t clk);
uint32_t Video_Get_Pll_Clk(void);
int8_t Video_Set_Pll_Clk(uint32_t clk);
uint32_t VE_Get_Pll_Clk(void);
int8_t VE_Set_Pll_Clk(uint32_t clk);
uint32_t DDR_Get_Pll_Clk(void);
uint32_t Periph_Get_Pll_Clk(void);
int8_t Periph_Set_Pll_Clk(uint32_t clk);
uint32_t CPU_Get_Clk(void);
int8_t CPU_Set_Clk(uint32_t clk);
uint32_t AHB_Get_Clk(void);
uint32_t APB_Get_clk(void);

#endif
