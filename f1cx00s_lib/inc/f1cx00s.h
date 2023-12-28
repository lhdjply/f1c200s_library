#ifndef __F1CX00S__H
#define __F1CX00S__H

#include "stdint.h"

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;

typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus;

typedef struct
{
  volatile uint32_t DAC_DPC;
  volatile uint32_t DAC_FIFOC;
  volatile uint32_t DAC_FIF;
  volatile uint32_t DAC_TXDATA;
  volatile uint32_t ADC_FIFOC;
  volatile uint32_t ADC_FIFOS;
  volatile uint32_t ADC_RXDATA;
  volatile uint32_t Reserve0;
  volatile uint32_t DAC_MIXER_CTRL;
  volatile uint32_t ADC_MIXER_CTRL;
  volatile uint32_t ADDA_TUNE;
  volatile uint32_t BIAS_DA16_CAL_CTRL0;
  volatile uint32_t Reserve1;
  volatile uint32_t BIAS_DA16_CAL_CTRL1;
  volatile uint32_t Reserve2[2];
  volatile uint32_t DAC_CNT;
  volatile uint32_t ADC_CNT;
  volatile uint32_t DAC_DG;
  volatile uint32_t ADC_DG;
  volatile uint32_t Reserve3[8];
  volatile uint32_t ADC_DAP_CTR;
  volatile uint32_t ADC_DAP_LCTR;
  volatile uint32_t ADC_DAP_RCTR;
  volatile uint32_t ADC_DAP_PARA;
  volatile uint32_t ADC_DAP_LAC;
  volatile uint32_t ADC_DAP_LDAT;
  volatile uint32_t ADC_DAP_RAC;
  volatile uint32_t ADC_DAP_RDAT;
  volatile uint32_t ADC_DAP_HPFC;
  volatile uint32_t ADC_DAP_LINAC;
  volatile uint32_t ADC_DAP_RINAC;
  volatile uint32_t ADC_DAP_ORT;
} AUDIO_TypeDef;

typedef struct
{
  volatile uint32_t PLL_CPU_CTRL;
  volatile uint32_t Reserve0;
  volatile uint32_t PLL_AUDIO_CTRL;
  volatile uint32_t Reserve1;
  volatile uint32_t PLL_VIDEO_CTRL;
  volatile uint32_t Reserve2;
  volatile uint32_t PLL_VE_CTRL;
  volatile uint32_t Reserve3;
  volatile uint32_t PLL_DDR_CTRL;
  volatile uint32_t Reserve4;
  volatile uint32_t PLL_PERIPH_CTRL;
  volatile uint32_t Reserve5[9];
  volatile uint32_t CPU_CLK_SRC;
  volatile uint32_t AHB_APB_HCLKC_CFG;
  volatile uint32_t Reserve6[2];
  volatile uint32_t BUS_CLK_GATING0;
  volatile uint32_t BUS_CLK_GATING1;
  volatile uint32_t BUS_CLK_GATING2;
  volatile uint32_t Reserve7[7];
  volatile uint32_t SDMMC0_CLK;
  volatile uint32_t SDMMC1_CLK;
  volatile uint32_t Reserve8[8];
  volatile uint32_t DAUDIO_CLK;
  volatile uint32_t OWA_CLK;
  volatile uint32_t CIR_CLK;
  volatile uint32_t Reserve9[4];
  volatile uint32_t USBPHY_CLK;
  volatile uint32_t Reserve10[12];
  volatile uint32_t DRAM_GATING;
  volatile uint32_t BE_CLK;
  volatile uint32_t Reserve11;
  volatile uint32_t FE_CLK;
  volatile uint32_t Reserve12[2];
  volatile uint32_t TCON_CLK;
  volatile uint32_t DI_CLK;
  volatile uint32_t TVE_CLK;
  volatile uint32_t TVD_CLK;
  volatile uint32_t Reserve13[3];
  volatile uint32_t CSI_CLK;
  volatile uint32_t Reserve14;
  volatile uint32_t VE_CLK;
  volatile uint32_t AUDIO_CODEC_CLK;
  volatile uint32_t AVS_CLK;
  volatile uint32_t Reserve15[46];
  volatile uint32_t PLL_STABLE_TIME0;
  volatile uint32_t PLL_STABLE_TIME1;
  volatile uint32_t Reserve16[6];
  volatile uint32_t PLL_CPU_BIAS;
  volatile uint32_t PLL_AUDIO_BIAS;
  volatile uint32_t PLL_VIDEO_BIAS;
  volatile uint32_t PLL_VE_BIAS;
  volatile uint32_t PLL_DDR_BIAS;
  volatile uint32_t PLL_PERIPH_BIAS;
  volatile uint32_t Reserve17[6];
  volatile uint32_t PLL_CPU_TUN;
  volatile uint32_t Reserve18[3];
  volatile uint32_t PLL_DDR_TUN;
  volatile uint32_t Reserve19[8];
  volatile uint32_t PLL_AUDIO_PAT_CTRL;
  volatile uint32_t PLL_VIDEO_PAT_CTRL;
  volatile uint32_t Reserve20;
  volatile uint32_t PLL_DDR_PAT_CTRL;
  volatile uint32_t Reserve21[11];
  volatile uint32_t BUS_SOFT_RST0;
  volatile uint32_t BUS_SOFT_RST1;
  volatile uint32_t Reserve22[2];
  volatile uint32_t BUS_SOFT_RST2;
} CCU_TypeDef;

typedef struct
{
  volatile uint32_t Reserve0[512];
  volatile uint32_t MODE_CTRL;
  volatile uint32_t COLOR_CTRL;
  volatile uint32_t Reserve1[2];
  volatile uint32_t LAY_SIZE[4];
  volatile uint32_t LAY_CODNT[4];
  volatile uint32_t Reserve2[4];
  volatile uint32_t LAY_LINEWIDTH[4];
  volatile uint32_t LAY_FB_ADDR[4];
  volatile uint32_t Reserve3[4];
  volatile uint32_t REGBUFF_CTRL;
  volatile uint32_t Reserve4[3];
  volatile uint32_t CK_MAX;
  volatile uint32_t CK_MIN;
  volatile uint32_t CK_CFG;
  volatile uint32_t Reserve5;
  volatile uint32_t LAY_ATT_CTRL_REG0[4];
  volatile uint32_t LAY_ATT_CTRL_REG1[4];
  volatile uint32_t Reserve6[10];
  volatile uint32_t HWC_CTRL;
  volatile uint32_t Reserve7;
  volatile uint32_t HWCFB_CTRL;
  volatile uint32_t Reserve8[3];
  volatile uint32_t WB_CTRL;
  volatile uint32_t WB_ADDR;
  volatile uint32_t WB_LW;
  volatile uint32_t Reserve9[9];
  volatile uint32_t IYUV_CH_CTRL;
  volatile uint32_t Reserve10[3];
  volatile uint32_t CH0_YUV_FB_ADDR;
  volatile uint32_t CH1_YUV_FB_ADDR;
  volatile uint32_t CH2_YUV_FB_ADDR;
  volatile uint32_t Reserve11;
  volatile uint32_t CH0_YUV_BLW;
  volatile uint32_t CH1_YUV_BLW;
  volatile uint32_t CH2_YUV_BLW;
  volatile uint32_t Reserve12;
  volatile uint32_t COEF00;
  volatile uint32_t COEF01;
  volatile uint32_t COEF02;
  volatile uint32_t COEF03;
  volatile uint32_t COEF10;
  volatile uint32_t COEF11;
  volatile uint32_t COEF12;
  volatile uint32_t COEF13;
  volatile uint32_t COEF20;
  volatile uint32_t COEF21;
  volatile uint32_t COEF22;
  volatile uint32_t COEF23;
} DEBE_TypeDef;

typedef struct
{
  volatile uint32_t EN;
  volatile uint32_t FRM_CTRL;
  volatile uint32_t BYPASS;
  volatile uint32_t AGTH_SEL;
  volatile uint32_t LINT_CTRL;
  volatile uint32_t Reserve0[3];
  volatile uint32_t BUF_ADDR0;
  volatile uint32_t BUF_ADDR1;
  volatile uint32_t BUF_ADDR2;
  volatile uint32_t FIELD_CTRL;
  volatile uint32_t TB_OFF0;
  volatile uint32_t TB_OFF1;
  volatile uint32_t TB_OFF2;
  volatile uint32_t Reserve1;
  volatile uint32_t LINESTRD0;
  volatile uint32_t LINESTRD1;
  volatile uint32_t LINESTRD2;
  volatile uint32_t INPUT_FMT;
  volatile uint32_t WB_ADDR;
  volatile uint32_t Reserve2[2];
  volatile uint32_t OUTPUT_FMT;
  volatile uint32_t INT_EN;
  volatile uint32_t INT_STATUS;
  volatile uint32_t STATUS;
  volatile uint32_t Reserve3;
  volatile uint32_t CSC_COEF00;
  volatile uint32_t CSC_COEF01;
  volatile uint32_t CSC_COEF02;
  volatile uint32_t CSC_COEF03;
  volatile uint32_t CSC_COEF10;
  volatile uint32_t CSC_COEF11;
  volatile uint32_t CSC_COEF12;
  volatile uint32_t CSC_COEF13;
  volatile uint32_t CSC_COEF20;
  volatile uint32_t CSC_COEF21;
  volatile uint32_t CSC_COEF22;
  volatile uint32_t CSC_COEF23;
  volatile uint32_t Reserve4[24];
  volatile uint32_t INSIZE;
  volatile uint32_t OUTSIZE;
  volatile uint32_t HORZFACT;
  volatile uint32_t VERTFACT;
  volatile uint32_t Reserve5[188];
  volatile uint32_t CH0_HORZCOEF[32];
  volatile uint32_t Reserve6[32];
  volatile uint32_t CH0_VERTCOEF[32];
  volatile uint32_t Reserve7[32];
  volatile uint32_t CH1_HORZCOEF[32];
  volatile uint32_t Reserve8[32];
  volatile uint32_t CH1_VERTCOEF[32];
} DEFE_TypeDef;

typedef struct
{
  volatile uint32_t CFG0;
  volatile uint32_t CFG1;
  volatile uint32_t CFG2;
  volatile uint32_t CFG3;
  volatile uint32_t CTRL;
  volatile uint32_t STA;
  volatile uint32_t DEB;
} EXTI_TypeDef;

typedef struct
{
  volatile uint32_t CFG0;
  volatile uint32_t CFG1;
  volatile uint32_t CFG2;
  volatile uint32_t CFG3;
  volatile uint32_t DATA;
  volatile uint32_t DRV0;
  volatile uint32_t DRV1;
  volatile uint32_t PUL0;
  volatile uint32_t PUL1;
} GPIO_TypeDef;

typedef struct
{
  volatile uint32_t ADDR;
  volatile uint32_t XADDR;
  volatile uint32_t DATA;
  volatile uint32_t CNTR;
  volatile uint32_t STAT;
  volatile uint32_t CCR;
  volatile uint32_t SRST;
  volatile uint32_t EFR;
  volatile uint32_t LCR;
} I2C_TypeDef;

typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t CH0_PERIOD;
  volatile uint32_t CH1_PERIOD;
} PWM_TypeDef;

typedef struct
{
  volatile uint32_t GCTL;
  volatile uint32_t CKCR;
  volatile uint32_t TMOR;
  volatile uint32_t BWDR;
  volatile uint32_t BKSR;
  volatile uint32_t BYCR;
  volatile uint32_t CMDR;
  volatile uint32_t CAGR;
  volatile uint32_t RESP0;
  volatile uint32_t RESP1;
  volatile uint32_t RESP2;
  volatile uint32_t RESP3;
  volatile uint32_t IMKR;
  volatile uint32_t MISR;
  volatile uint32_t RISR;
  volatile uint32_t STAR;
  volatile uint32_t FWLR;
  volatile uint32_t FUNS;
  volatile uint32_t CBCR;
  volatile uint32_t BBCR;
  volatile uint32_t DBGC;
  volatile uint32_t Reserve0;
  volatile uint32_t A12A;
  volatile uint32_t Reserve1[7];
  volatile uint32_t HWRST;
  volatile uint32_t Reserve2;
  volatile uint32_t DMAC;
  volatile uint32_t DLBA;
  volatile uint32_t IDST;
  volatile uint32_t IDIE;
  volatile uint32_t CHDA;
  volatile uint32_t CBDA;
  volatile uint32_t Reserve3[26];
  volatile uint32_t CARD_THLDC;
  volatile uint32_t Reserve4[2];
  volatile uint32_t EMMC_DSBD;
  volatile uint32_t Reserve5[12];
  volatile uint32_t Reserve6[48];
  volatile uint32_t FIFO;
} SDIO_TypeDef;

typedef struct
{
  volatile uint32_t Reserve0;
  volatile uint32_t GCR;
  volatile uint32_t TCR;
  volatile uint32_t Reserve1;
  volatile uint32_t IER;
  volatile uint32_t ISR;
  volatile uint32_t FCR;
  volatile uint32_t FSR;
  volatile uint32_t WCR;
  volatile uint32_t CCR;
  volatile uint32_t Reserve2[2];
  volatile uint32_t MBC;
  volatile uint32_t MTC;
  volatile uint32_t BCC;
  volatile uint32_t Reserve3[113];
  volatile uint32_t TXD_DATA;
  volatile uint32_t Reserve4[63];
  volatile uint32_t RXD_DATA;
} SPI_TypeDef;

typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t INT0;
  volatile uint32_t INT1;
  volatile uint32_t Reserve0;
  volatile uint32_t FRM_CTRL;
  volatile uint32_t FRM_SEED0_R;
  volatile uint32_t FRM_SEED0_G;
  volatile uint32_t FRM_SEED0_B;
  volatile uint32_t FRM_SEED1_R;
  volatile uint32_t FRM_SEED1_G;
  volatile uint32_t FRM_SEED1_B;
  volatile uint32_t FRM_TABLE[4];
  volatile uint32_t Reserve1;
  volatile uint32_t TCON0_CTRL;
  volatile uint32_t CLK_CTRL;
  volatile uint32_t TCON0_BASIC_TIMING[4];
  volatile uint32_t TCON0_HV_TIMING;
  volatile uint32_t Reserve2;
  volatile uint32_t TCON0_CPU_IF;
  volatile uint32_t TCON0_CPU_WR;
  volatile uint32_t TCON0_CPU_RD;
  volatile uint32_t TCON0_CPU_RD_NX;
  volatile uint32_t Reserve3[6];
  volatile uint32_t TCON0_IO_CTRL0;
  volatile uint32_t TCON0_IO_CTRL1;
  volatile uint32_t TCON1_CTRL;
  volatile uint32_t TCON1_BASIC[6];
  volatile uint32_t Reserve4[17];
  volatile uint32_t TCON1_IO_CTRL0;
  volatile uint32_t TCON1_IO_CTRL1;
  volatile uint32_t Reserve5;
  volatile uint32_t DEBUG_INFO;
} TCON_TypeDef;

typedef struct
{
  volatile uint32_t RBR_THR_DLL;
  volatile uint32_t DLH_IER;
  volatile uint32_t IIR_FCR;
  volatile uint32_t LCR;
  volatile uint32_t MCR;
  volatile uint32_t LSR;
  volatile uint32_t MSR;
  volatile uint32_t SCH;
  volatile uint32_t Reserve0[23];
  volatile uint32_t USR;
  volatile uint32_t TFL;
  volatile uint32_t RFL;
  volatile uint32_t HSK;
  volatile uint32_t Reserve1[6];
  volatile uint32_t HALT;
  volatile uint32_t Reserve2[2];
  volatile uint32_t DBG_DLL;
  volatile uint32_t DBG_DLH;
} UART_TypeDef;

typedef struct
{
  volatile uint32_t IRQ_EN;
  volatile uint32_t IRQ_STA;
  volatile uint32_t Reserve[2];
  volatile uint32_t CTRL;
  volatile uint32_t CFG;
  volatile uint32_t MODE;
} WDOG_TypeDef;

#define AUDIO_BASE 0x01C23C00
#define CCU_BASE 0x01C20000
#define DEBE_BASE 0x01E60000
#define DEFE_BASE 0x01E00000
#define EXTID_BASE 0x01C20A00
#define EXTIE_BASE 0x01C20A20
#define EXTIF_BASE 0x01C20A40
#define GPIOA_BASE 0x01C20800
#define GPIOB_BASE 0x01C20824
#define GPIOC_BASE 0x01C20848
#define GPIOD_BASE 0x01C2086C
#define GPIOE_BASE 0x01C20890
#define GPIOF_BASE 0x01C208b4
#define I2C0_BASE 0x01C27000
#define I2C1_BASE 0x01C27400
#define I2C2_BASE 0x01C27800
#define PWM_BASE 0x01C21000
#define SDIO0_BASE 0x01C0F000
#define SDIO1_BASE 0x01C10000
#define SPI0_BASE 0x01C05000
#define SPI1_BASE 0x01C06000
#define TCON_BASE 0x01C0C000
#define UART0_BASE 0x01C25000
#define UART1_BASE 0x01C25400
#define UART2_BASE 0x01C25800
#define WDOG_BASE 0x01C20CA0

#define AUDIO ((AUDIO_TypeDef *)AUDIO_BASE)
#define DEBE ((DEBE_TypeDef *)DEBE_BASE)
#define DEFE ((DEFE_TypeDef *)DEFE_BASE)
#define CCU ((CCU_TypeDef *)CCU_BASE)
#define EXTID ((EXTI_TypeDef *)EXTID_BASE)
#define EXTIE ((EXTI_TypeDef *)EXTIE_BASE)
#define EXTIF ((EXTI_TypeDef *)EXTIF_BASE)
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *)GPIOF_BASE)
#define I2C0 ((I2C_TypeDef *)I2C0_BASE)
#define I2C1 ((I2C_TypeDef *)I2C1_BASE)
#define I2C2 ((I2C_TypeDef *)I2C2_BASE)
#define PWM ((PWM_TypeDef *)PWM_BASE)
#define SDIO0 ((SDIO_TypeDef *)SDIO0_BASE)
#define SDIO1 ((SDIO_TypeDef *)SDIO1_BASE)
#define SPI0 ((SPI_TypeDef *)SPI0_BASE)
#define SPI1 ((SPI_TypeDef *)SPI1_BASE)
#define TCON ((TCON_TypeDef *)TCON_BASE)
#define UART0 ((UART_TypeDef *)UART0_BASE)
#define UART1 ((UART_TypeDef *)UART1_BASE)
#define UART2 ((UART_TypeDef *)UART2_BASE)
#define WDOG ((WDOG_TypeDef *)WDOG_BASE)

#endif
