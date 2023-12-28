#include "../inc/basicmathfunctions.h"

void arm_offset_q7(
  const q7_t * pSrc,
  q7_t offset,
  q7_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    *pDst++ = (q7_t)__SSAT((q15_t) * pSrc++ + offset, 8);
    blkCnt--;
  }
}

void arm_offset_q15(
  const q15_t * pSrc,
  q15_t offset,
  q15_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    *pDst++ = (q15_t)__SSAT(((q31_t) * pSrc++ + offset), 16);
    blkCnt--;
  }
}

void arm_offset_q31(
  const q31_t * pSrc,
  q31_t offset,
  q31_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    *pDst++ = (q31_t)clip_q63_to_q31((q63_t) * pSrc++ + offset);
    blkCnt--;
  }
}

void arm_offset_f32(
  const float32_t * pSrc,
  float32_t offset,
  float32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    *pDst++ = (*pSrc++) + offset;
    blkCnt--;
  }
}
