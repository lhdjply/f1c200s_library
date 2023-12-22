#include "../inc/supportfunctions.h"

void arm_fill_q7(q7_t value, q7_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = value;
    blkCnt--;
  }
}

void arm_fill_q15(q15_t value, q15_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = value;
    blkCnt--;
  }
}

void arm_fill_q31(q31_t value, q31_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = value;
    blkCnt--;
  }
}

void arm_fill_f32(float32_t value, float32_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = value;
    blkCnt--;
  }
}
