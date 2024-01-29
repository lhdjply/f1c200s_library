#include "../inc/basicmathfunctions.h"

void arm_not_u8(
  const uint8_t * pSrc,
  uint8_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = ~(*pSrc++);
    blkCnt--;
  }
}

void arm_not_u16(
  const uint16_t * pSrc,
  uint16_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = ~(*pSrc++);
    blkCnt--;
  }
}

void arm_not_u32(
  const uint32_t * pSrc,
  uint32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = ~(*pSrc++);
    blkCnt--;
  }
}
