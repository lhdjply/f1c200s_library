#include "../inc/statisticsfunctions.h"

void arm_max_q7(
  const q7_t * pSrc,
  uint32_t blockSize,
  q7_t * pResult,
  uint32_t * pIndex)
{
  q7_t maxVal, out;
  uint32_t blkCnt, outIndex;

  outIndex = 0;
  out = *pSrc++;
  blkCnt = (blockSize - 1U);

  while(blkCnt > 0)
  {
    maxVal = *pSrc++;
    if(out < maxVal)
    {
      out = maxVal;
      outIndex = blockSize - blkCnt;
    }
    blkCnt--;
  }
  *pResult = out;
  *pIndex = outIndex;
}

void arm_max_q15(
  const q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult,
  uint32_t * pIndex)
{
  q15_t maxVal, out;
  uint32_t blkCnt, outIndex;

  outIndex = 0;
  out = *pSrc++;
  blkCnt = (blockSize - 1U);

  while(blkCnt > 0)
  {
    maxVal = *pSrc++;
    if(out < maxVal)
    {
      out = maxVal;
      outIndex = blockSize - blkCnt;
    }
    blkCnt--;
  }
  *pResult = out;
  *pIndex = outIndex;
}

void arm_max_q31(
  const q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult,
  uint32_t * pIndex)
{
  q31_t maxVal, out;
  uint32_t blkCnt, outIndex;

  outIndex = 0;
  out = *pSrc++;
  blkCnt = (blockSize - 1U);

  while(blkCnt > 0)
  {
    maxVal = *pSrc++;
    if(out < maxVal)
    {
      out = maxVal;
      outIndex = blockSize - blkCnt;
    }
    blkCnt--;
  }
  *pResult = out;
  *pIndex = outIndex;
}

void arm_max_f32(const float32_t * pSrc,
                 uint32_t blockSize,
                 float32_t * pResult,
                 uint32_t * pIndex)
{
  float32_t maxVal, out;
  uint32_t blkCnt, outIndex;

  outIndex = 0;
  out = *pSrc++;
  blkCnt = (blockSize - 1U);

  while(blkCnt > 0)
  {
    maxVal = *pSrc++;
    if(out < maxVal)
    {
      out = maxVal;
      outIndex = blockSize - blkCnt;
    }
    blkCnt--;
  }
  *pResult = out;
  *pIndex = outIndex;
}
