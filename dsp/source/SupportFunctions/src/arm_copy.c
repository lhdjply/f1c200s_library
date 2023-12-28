#include "../inc/supportfunctions.h"

void arm_copy_q7(const q7_t * pSrc, q7_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    *pDst++ = *pSrc++;
    blkCnt--;
  }
}

void arm_copy_q15(const q15_t * pSrc, q15_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    *pDst++ = *pSrc++;
    blkCnt--;
  }
}

void arm_copy_q31(const q31_t * pSrc, q31_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    *pDst++ = *pSrc++;
    blkCnt--;
  }
}

void arm_copy_f32(const float32_t * pSrc, float32_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = *pSrc++;
    blkCnt--;
  }
}
