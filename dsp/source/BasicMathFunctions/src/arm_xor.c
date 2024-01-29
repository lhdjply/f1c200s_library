#include "../inc/basicmathfunctions.h"

void arm_xor_u8(
  const uint8_t * pSrcA,
  const uint8_t * pSrcB,
  uint8_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (*pSrcA++) ^ (*pSrcB++);
    blkCnt--;
  }
}

void arm_xor_u16(
  const uint16_t * pSrcA,
  const uint16_t * pSrcB,
  uint16_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (*pSrcA++) ^ (*pSrcB++);
    blkCnt--;
  }
}

void arm_xor_u32(
  const uint32_t * pSrcA,
  const uint32_t * pSrcB,
  uint32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;
  while(blkCnt > 0U)
  {
    *pDst++ = (*pSrcA++) ^ (*pSrcB++);
    blkCnt--;
  }
}
