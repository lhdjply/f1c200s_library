#ifndef __F1CX00S_SDIO__H
#define __F1CX00S_SDIO__H

#include "f1cx00s.h"

#define MMCSD_BUS_WIDTH_1 1
#define MMCSD_BUS_WIDTH_4 4
#define MMCSD_BUS_WIDTH_8 8

#define SDIO_BIT(x) (1 << (x))

/*
    SD CMD reg
REG[0-5] : Cmd ID
REG[6]   : Has response
REG[7]   : Long response
REG[8]   : Check response CRC
REG[9]   : Has data
REG[10]  : Write
REG[11]  : Steam mode
REG[12]  : Auto stop
REG[13]  : Wait previous over
REG[14]  : About cmd
REG[15]  : Send initialization
REG[21]  : Update clock
REG[31]  : Load cmd
*/
#define SDXC_RESPONSE_CMD SDIO_BIT(6)
#define SDXC_LONG_RESPONSE_CMD SDIO_BIT(7)
#define SDXC_CHECK_CRC_CMD SDIO_BIT(8)
#define SDXC_HAS_DATA_CMD SDIO_BIT(9)
#define SDXC_WRITE_CMD SDIO_BIT(10)
#define SDXC_STEAM_CMD SDIO_BIT(11)
#define SDXC_AUTO_STOP_CMD SDIO_BIT(12)
#define SDXC_WAIT_OVER_CMD SDIO_BIT(13)
#define SDXC_ABOUT_CMD SDIO_BIT(14)
#define SDXC_SEND_INIT_CMD SDIO_BIT(15)
#define SDXC_UPDATE_CLOCK_CMD SDIO_BIT(21)
#define SDXC_LOAD_CMD SDIO_BIT(31)

typedef struct
{
  volatile uint32_t size; /* block size  */
  volatile uint32_t num;  /* block num   */
  volatile uint8_t * buff; /* buff addr   */
  volatile uint32_t flag; /* write or read or stream */
} SDIO_XFEInitTypeDef;

typedef struct
{
  volatile uint32_t blksize;
  volatile uint32_t blks;
  volatile uint8_t * buf;
  volatile uint32_t err;
  volatile uint32_t flags;
#define SDIO_DATA_DIR_WRITE (1 << 0)
#define SDIO_DATA_DIR_READ (1 << 1)
#define SDIO_DATA_STREAM (1 << 2)
} SDIO_DataInitTypeDef;

typedef struct
{
  volatile uint32_t SDIO_CmdIndex;
  volatile uint32_t SDIO_Argument;
  volatile uint32_t SDIO_Resp[4];
  volatile uint32_t SDIO_Flags;

#define SDIO_RESP_MASK (0xF)
#define SDIO_RESP_NONE (0)
#define SDIO_RESP_R1 (1 << 0)
#define SDIO_RESP_R1B (2 << 0)
#define SDIO_RESP_R2 (3 << 0)
#define SDIO_RESP_R3 (4 << 0)
#define SDIO_RESP_R4 (5 << 0)
#define SDIO_RESP_R6 (6 << 0)
#define SDIO_RESP_R7 (7 << 0)
#define SDIO_RESP_R5 (8 << 0) /*SDIO command response type*/
#define SDIO_Resp_Type(cmd) ((cmd)->SDIO_Flags & SDIO_RESP_MASK)

#define SDIO_CMD_MASK (3 << 4) /* command type */
#define SDIO_CMD_AC (0 << 4)
#define SDIO_CMD_ADTC (1 << 4)
#define SDIO_CMD_BC (2 << 4)
#define SDIO_CMD_BCR (3 << 4)
#define SDIO_Cmd_Type(cmd) ((cmd)->SDIO_Flags & SDIO_CMD_MASK)

#define SDIO_RESP_SPI_MASK (0x7 << 6)
#define SDIO_RESP_SPI_R1 (1 << 6)
#define SDIO_RESP_SPI_R1B (2 << 6)
#define SDIO_RESP_SPI_R2 (3 << 6)
#define SDIO_RESP_SPI_R3 (4 << 6)
#define SDIO_RESP_SPI_R4 (5 << 6)
#define SDIO_RESP_SPI_R5 (6 << 6)
#define SDIO_RESP_SPI_R7 (7 << 6)
#define SDIO_Resp_Spi_Type(cmd) ((cmd)->SDIO_Flags & SDIO_RESP_SPI_MASK)
} SDIO_CmdInitTypeDef;

int8_t SDIO_Set_Clk(SDIO_TypeDef * SDIOx, uint32_t hz);
int8_t SDIO_Config_Clock(SDIO_TypeDef * SDIOx, int clk);
int8_t SDIO_Set_Ios(SDIO_TypeDef * SDIOx, int clk, int bus_width);
uint32_t SDIO_Get_STA(SDIO_TypeDef * SDIOx);
int8_t SDIO_SendCommand(SDIO_TypeDef * SDIOx,
                        SDIO_CmdInitTypeDef * SDIO_CmdInitStruct,
                        uint32_t us);
int SDIO_SendCommand_and_Data(SDIO_TypeDef * SDIOx,
                              SDIO_DataInitTypeDef * SDIO_DataInitStruct,
                              SDIO_CmdInitTypeDef * SDIO_CmdInitStruct,
                              uint32_t us);
#endif
