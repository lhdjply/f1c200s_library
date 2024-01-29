#include "../inc/basicmathfunctions.h"

void arm_scale_q7(
  const q7_t * pSrc,
  q7_t scaleFract,
  int8_t shift,
  q7_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  int8_t kShift = 7 - shift;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (q7_t)(__SSAT((((q15_t) * pSrc++ * scaleFract) >> kShift), 8));
    blkCnt--;
  }

}

void arm_scale_q15(
  const q15_t * pSrc,
  q15_t scaleFract,
  int8_t shift,
  q15_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  int8_t kShift = 15 - shift;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (q15_t)(__SSAT(((q31_t) * pSrc++ * scaleFract) >> kShift, 16));
    blkCnt--;
  }

}

void arm_scale_q31(
  const q31_t * pSrc,
  q31_t scaleFract,
  int8_t shift,
  q31_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;
  q31_t in, out;
  int8_t kShift = shift + 1;
  int8_t sign = (kShift & 0x80);

  blkCnt = blockSize;

  if(sign == 0U)
  {
    while(blkCnt > 0U)
    {
      in = *pSrc++;
      in = ((q63_t) in * scaleFract) >> 32;
      out = in << kShift;
      if(in != (out >> kShift))
        out = 0x7FFFFFFF ^ (in >> 31);
      *pDst++ = out;
      blkCnt--;
    }
  }
  else
  {
    while(blkCnt > 0U)
    {
      in = *pSrc++;
      in = ((q63_t) in * scaleFract) >> 32;
      out = in >> -kShift;
      *pDst++ = out;
      blkCnt--;
    }
  }
}

void arm_scale_f32(
  const float32_t * pSrc,
  float32_t scale,
  float32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;

  blkCnt = blockSize;

  while(blkCnt > 0U)
  {
    *pDst++ = (*pSrc++) * scale;
    blkCnt--;
  }
}
