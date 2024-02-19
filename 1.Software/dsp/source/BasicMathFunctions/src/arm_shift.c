#include "../inc/basicmathfunctions.h"

void arm_shift_q7(
  const q7_t * pSrc,
  int8_t shiftBits,
  q7_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  uint8_t sign = (shiftBits & 0x80);

  blkCnt = blockSize;

  if(sign == 0U)
  {
    while(blkCnt > 0U)
    {
      *pDst++ = (q7_t) __SSAT(((q15_t) * pSrc++ << shiftBits), 8);
      blkCnt--;
    }
  }
  else
  {
    while(blkCnt > 0U)
    {
      *pDst++ = (*pSrc++ >> -shiftBits);
      blkCnt--;
    }
  }
}

void arm_shift_q15(
  const q15_t * pSrc,
  int8_t shiftBits,
  q15_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  uint8_t sign = (shiftBits & 0x80);

  blkCnt = blockSize;

  if(sign == 0U)
  {
    while(blkCnt > 0U)
    {
      *pDst++ = __SSAT(((q31_t) * pSrc++ << shiftBits), 16);
      blkCnt--;
    }
  }
  else
  {
    while(blkCnt > 0U)
    {
      *pDst++ = (*pSrc++ >> -shiftBits);
      blkCnt--;
    }
  }
}

void arm_shift_q31(
  const q31_t * pSrc,
  int8_t shiftBits,
  q31_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  uint8_t sign = (shiftBits & 0x80);

  blkCnt = blockSize;

  if(sign == 0U)
  {
    while(blkCnt > 0U)
    {
      *pDst++ = clip_q63_to_q31((q63_t) * pSrc++ << shiftBits);
      blkCnt--;
    }
  }
  else
  {
    while(blkCnt > 0U)
    {
      *pDst++ = (*pSrc++ >> -shiftBits);
      blkCnt--;
    }
  }
}
