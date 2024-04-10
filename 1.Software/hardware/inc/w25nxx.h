#ifndef __W25NXX_H
#define __W25NXX_H

#include "sys.h"
#include "delay.h"

#define W25NXX_CS PCout(1) // W25NXX的片选信号
#define W25NXX_SPI SPI0


/*
 * Default spi nand page size: 2048(11), 4096(12)
 */
// #define W25NXX_PAGE_SIZE 2048
#define W25NXX_PAGE_BITS (11)
#define W25NXX_PAGE_MASK ((1 << W25NXX_PAGE_BITS) - 1)
#define W25NXX_PAGE_SIZE (1 << W25NXX_PAGE_BITS)

// 指令表
#define W25N_WriteEnable 0x06
#define W25N_WriteDisable 0x04
#define W25N_ReadStatusReg 0x0f
#define W25N_WriteStatusReg 0x1f
#define W25N_ReadPage 0x13
#define W25N_ReadData 0x03
#define W25N_PageProgram_Load 0x02
#define W25N_Program_Execute 0x10
#define W25N_JedecDeviceID 0x9F
#define W25N_BlockErase 0xD8

void W25NXX_Init(void);
uint16_t W25NXX_ReadID(void);
void W25NXX_Read_Buffer(uint8_t * pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void W25NXX_Write_Buffer(uint8_t * pBuffer, uint32_t WriteAddr, uint16_t NumByteToRead);
void W25NXX_FLASH_BlockErase(uint32_t BlockAddr);

#endif
