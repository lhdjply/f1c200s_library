#include "../inc/statisticsfunctions.h"

void arm_rms_q15(const q15_t * pSrc, uint32_t blockSize, q15_t * pResult)
{
  uint32_t blkCnt;
  q63_t sum = 0;
  q15_t in;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    in = *pSrc++;
    sum += ((q31_t)in * in);
    blkCnt--;
  }
  arm_sqrt_q15(__SSAT((sum / (q63_t)blockSize) >> 15, 16), pResult);
}

void arm_rms_q31(const q31_t * pSrc, uint32_t blockSize, q31_t * pResult)
{
  uint32_t blkCnt;
  uint64_t sum = 0;
  q31_t in;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    in = *pSrc++;
    sum += ((q63_t)in * in);
    blkCnt--;
  }
  arm_sqrt_q31(clip_q63_to_q31((sum / (q63_t)blockSize) >> 31), pResult);
}

void arm_rms_f32(const float32_t * pSrc, uint32_t blockSize, float32_t * pResult)
{
  uint32_t blkCnt;
  float32_t sum = 0;
  float32_t in;

  blkCnt = blockSize;

  while(blkCnt > 0)
  {
    in = *pSrc++;
    sum += (in * in);
    blkCnt--;
  }
  arm_sqrt_f32(sum / (float32_t)blockSize, pResult);
}
