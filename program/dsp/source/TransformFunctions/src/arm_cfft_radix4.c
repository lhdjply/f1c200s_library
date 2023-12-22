#include "../inc/transformfunctions.h"

void arm_radix4_butterfly_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  const q15_t * pCoef16,
  uint32_t twidCoefModifier);
void arm_radix4_butterfly_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  const q31_t * pCoef,
  uint32_t twidCoefModifier);
void arm_radix4_butterfly_f32(
  float32_t * pSrc,
  uint16_t fftLen,
  const float32_t * pCoef,
  uint16_t twidCoefModifier);

void arm_radix4_butterfly_inverse_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  const q15_t * pCoef16,
  uint32_t twidCoefModifier);
void arm_radix4_butterfly_inverse_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  const q31_t * pCoef,
  uint32_t twidCoefModifier);
void arm_radix4_butterfly_inverse_f32(
  float32_t * pSrc,
  uint16_t fftLen,
  const float32_t * pCoef,
  uint16_t twidCoefModifier,
  float32_t onebyfftLen);

void arm_bitreversal_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  uint16_t bitRevFactor,
  const uint16_t * pBitRevTab);
void arm_bitreversal_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  uint16_t bitRevFactor,
  const uint16_t * pBitRevTab);
void arm_bitreversal_f32(
  float32_t * pSrc,
  uint16_t fftSize,
  uint16_t bitRevFactor,
  const uint16_t * pBitRevTab);

void arm_cfft_radix4_q15(
  const arm_cfft_radix4_instance_q15 * S,
  q15_t * pSrc)
{
  if(S->ifftFlag == 1U)
  {
    arm_radix4_butterfly_inverse_q15(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }
  else
  {
    arm_radix4_butterfly_q15(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }
  if(S->bitReverseFlag == 1U)
  {
    arm_bitreversal_q15(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);
  }
}

void arm_cfft_radix4_q31(
  const arm_cfft_radix4_instance_q31 * S,
  q31_t * pSrc)
{
  if(S->ifftFlag == 1U)
  {
    arm_radix4_butterfly_inverse_q31(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }
  else
  {
    arm_radix4_butterfly_q31(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }
  if(S->bitReverseFlag == 1U)
  {
    arm_bitreversal_q31(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);
  }
}

void arm_cfft_radix4_f32(
  const arm_cfft_radix4_instance_f32 * S,
  float32_t * pSrc)
{
  if(S->ifftFlag == 1U)
  {
    arm_radix4_butterfly_inverse_f32(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier, S->onebyfftLen);
  }
  else
  {
    arm_radix4_butterfly_f32(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }
  if(S->bitReverseFlag == 1U)
  {
    arm_bitreversal_f32(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);
  }
}

void arm_radix4_butterfly_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  const q15_t * pCoef16,
  uint32_t twidCoefModifier)
{
  q15_t R0, R1, S0, S1, T0, T1, U0, U1;
  q15_t Co1, Si1, Co2, Si2, Co3, Si3, out1, out2;
  uint32_t n1, n2, ic, i0, i1, i2, i3, j, k;

  n2 = fftLen;
  n1 = n2;

  n2 >>= 2U;

  ic = 0U;

  i0 = 0U;
  j = n2;

  do
  {
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    T0 = pSrc16[i0 * 2U] >> 2U;
    T1 = pSrc16[(i0 * 2U) + 1U] >> 2U;

    S0 = pSrc16[i2 * 2U] >> 2U;
    S1 = pSrc16[(i2 * 2U) + 1U] >> 2U;

    R0 = __SSAT(T0 + S0, 16U);

    R1 = __SSAT(T1 + S1, 16U);

    S0 = __SSAT(T0 - S0, 16);

    S1 = __SSAT(T1 - S1, 16);

    T0 = pSrc16[i1 * 2U] >> 2U;
    T1 = pSrc16[(i1 * 2U) + 1U] >> 2U;

    U0 = pSrc16[i3 * 2U] >> 2U;
    U1 = pSrc16[(i3 * 2U) + 1] >> 2U;

    T0 = __SSAT(T0 + U0, 16U);

    T1 = __SSAT(T1 + U1, 16U);

    pSrc16[i0 * 2U] = (R0 >> 1U) + (T0 >> 1U);
    pSrc16[(i0 * 2U) + 1U] = (R1 >> 1U) + (T1 >> 1U);

    R0 = __SSAT(R0 - T0, 16U);
    R1 = __SSAT(R1 - T1, 16U);

    Co2 = pCoef16[2U * ic * 2U];
    Si2 = pCoef16[(2U * ic * 2U) + 1];

    out1 = (q15_t)((Co2 * R0 + Si2 * R1) >> 16U);

    out2 = (q15_t)((-Si2 * R0 + Co2 * R1) >> 16U);

    T0 = pSrc16[i1 * 2U] >> 2;
    T1 = pSrc16[(i1 * 2U) + 1] >> 2;

    pSrc16[i1 * 2U] = out1;
    pSrc16[(i1 * 2U) + 1] = out2;

    U0 = pSrc16[i3 * 2U] >> 2;
    U1 = pSrc16[(i3 * 2U) + 1] >> 2;

    T0 = __SSAT(T0 - U0, 16);

    T1 = __SSAT(T1 - U1, 16);

    R0 = (q15_t)__SSAT((q31_t)(S0 - T1), 16);
    R1 = (q15_t)__SSAT((q31_t)(S1 + T0), 16);

    S0 = (q15_t)__SSAT(((q31_t)S0 + T1), 16U);
    S1 = (q15_t)__SSAT(((q31_t)S1 - T0), 16U);

    Co1 = pCoef16[ic * 2U];
    Si1 = pCoef16[(ic * 2U) + 1];

    out1 = (q15_t)((Si1 * S1 + Co1 * S0) >> 16);

    out2 = (q15_t)((-Si1 * S0 + Co1 * S1) >> 16);

    pSrc16[i2 * 2U] = out1;
    pSrc16[(i2 * 2U) + 1] = out2;

    Co3 = pCoef16[3U * (ic * 2U)];
    Si3 = pCoef16[(3U * (ic * 2U)) + 1];

    out1 = (q15_t)((Si3 * R1 + Co3 * R0) >> 16U);

    out2 = (q15_t)((-Si3 * R0 + Co3 * R1) >> 16U);

    pSrc16[i3 * 2U] = out1;
    pSrc16[(i3 * 2U) + 1] = out2;

    ic = ic + twidCoefModifier;

    i0 = i0 + 1U;

  } while(--j);

  twidCoefModifier <<= 2U;

  for(k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    n1 = n2;
    n2 >>= 2U;
    ic = 0U;

    for(j = 0U; j <= (n2 - 1U); j++)
    {
      Co1 = pCoef16[ic * 2U];
      Si1 = pCoef16[(ic * 2U) + 1U];
      Co2 = pCoef16[2U * (ic * 2U)];
      Si2 = pCoef16[(2U * (ic * 2U)) + 1U];
      Co3 = pCoef16[3U * (ic * 2U)];
      Si3 = pCoef16[(3U * (ic * 2U)) + 1U];

      ic = ic + twidCoefModifier;

      for(i0 = j; i0 < fftLen; i0 += n1)
      {
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        T0 = pSrc16[i0 * 2U];
        T1 = pSrc16[(i0 * 2U) + 1U];

        S0 = pSrc16[i2 * 2U];
        S1 = pSrc16[(i2 * 2U) + 1U];

        R0 = __SSAT(T0 + S0, 16);
        R1 = __SSAT(T1 + S1, 16);

        S0 = __SSAT(T0 - S0, 16);
        S1 = __SSAT(T1 - S1, 16);

        T0 = pSrc16[i1 * 2U];
        T1 = pSrc16[(i1 * 2U) + 1U];

        U0 = pSrc16[i3 * 2U];
        U1 = pSrc16[(i3 * 2U) + 1U];

        T0 = __SSAT(T0 + U0, 16);
        T1 = __SSAT(T1 + U1, 16);

        out1 = ((R0 >> 1U) + (T0 >> 1U)) >> 1U;
        out2 = ((R1 >> 1U) + (T1 >> 1U)) >> 1U;

        pSrc16[i0 * 2U] = out1;
        pSrc16[(2U * i0) + 1U] = out2;

        R0 = (R0 >> 1U) - (T0 >> 1U);
        R1 = (R1 >> 1U) - (T1 >> 1U);

        out1 = (q15_t)((Co2 * R0 + Si2 * R1) >> 16U);

        out2 = (q15_t)((-Si2 * R0 + Co2 * R1) >> 16U);

        T0 = pSrc16[i1 * 2U];
        T1 = pSrc16[(i1 * 2U) + 1U];

        pSrc16[i1 * 2U] = out1;
        pSrc16[(i1 * 2U) + 1U] = out2;

        U0 = pSrc16[i3 * 2U];
        U1 = pSrc16[(i3 * 2U) + 1U];

        T0 = __SSAT(T0 - U0, 16);
        T1 = __SSAT(T1 - U1, 16);

        R0 = (S0 >> 1U) - (T1 >> 1U);
        R1 = (S1 >> 1U) + (T0 >> 1U);

        S0 = (S0 >> 1U) + (T1 >> 1U);
        S1 = (S1 >> 1U) - (T0 >> 1U);

        out1 = (q15_t)((Co1 * S0 + Si1 * S1) >> 16U);

        out2 = (q15_t)((-Si1 * S0 + Co1 * S1) >> 16U);

        pSrc16[i2 * 2U] = out1;
        pSrc16[(i2 * 2U) + 1U] = out2;

        out1 = (q15_t)((Si3 * R1 + Co3 * R0) >> 16U);

        out2 = (q15_t)((-Si3 * R0 + Co3 * R1) >> 16U);

        pSrc16[i3 * 2U] = out1;
        pSrc16[(i3 * 2U) + 1U] = out2;
      }
    }

    twidCoefModifier <<= 2U;
  }

  n1 = n2;
  n2 >>= 2U;

  for(i0 = 0U; i0 <= (fftLen - n1); i0 += n1)
  {
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    T0 = pSrc16[i0 * 2U];
    T1 = pSrc16[(i0 * 2U) + 1U];

    S0 = pSrc16[i2 * 2U];
    S1 = pSrc16[(i2 * 2U) + 1U];

    R0 = __SSAT(T0 + S0, 16U);
    R1 = __SSAT(T1 + S1, 16U);

    S0 = __SSAT(T0 - S0, 16U);
    S1 = __SSAT(T1 - S1, 16U);

    T0 = pSrc16[i1 * 2U];
    T1 = pSrc16[(i1 * 2U) + 1U];

    U0 = pSrc16[i3 * 2U];
    U1 = pSrc16[(i3 * 2U) + 1U];

    T0 = __SSAT(T0 + U0, 16U);
    T1 = __SSAT(T1 + U1, 16U);

    pSrc16[i0 * 2U] = (R0 >> 1U) + (T0 >> 1U);
    pSrc16[(i0 * 2U) + 1U] = (R1 >> 1U) + (T1 >> 1U);

    R0 = (R0 >> 1U) - (T0 >> 1U);
    R1 = (R1 >> 1U) - (T1 >> 1U);

    T0 = pSrc16[i1 * 2U];
    T1 = pSrc16[(i1 * 2U) + 1U];

    pSrc16[i1 * 2U] = R0;
    pSrc16[(i1 * 2U) + 1U] = R1;

    U0 = pSrc16[i3 * 2U];
    U1 = pSrc16[(i3 * 2U) + 1U];

    T0 = __SSAT(T0 - U0, 16U);
    T1 = __SSAT(T1 - U1, 16U);

    pSrc16[i2 * 2U] = (S0 >> 1U) + (T1 >> 1U);
    pSrc16[(i2 * 2U) + 1U] = (S1 >> 1U) - (T0 >> 1U);

    pSrc16[i3 * 2U] = (S0 >> 1U) - (T1 >> 1U);
    pSrc16[(i3 * 2U) + 1U] = (S1 >> 1U) + (T0 >> 1U);
  }
}

void arm_radix4_butterfly_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  const q31_t * pCoef,
  uint32_t twidCoefModifier)
{
  uint32_t n1, n2, ia1, ia2, ia3, i0, i1, i2, i3, j, k;
  q31_t t1, t2, r1, r2, s1, s2, co1, co2, co3, si1, si2, si3;

  q31_t xa, xb, xc, xd;
  q31_t ya, yb, yc, yd;
  q31_t xa_out, xb_out, xc_out, xd_out;
  q31_t ya_out, yb_out, yc_out, yd_out;

  q31_t * ptr1;

  n2 = fftLen;
  n1 = n2;

  n2 >>= 2U;
  i0 = 0U;
  ia1 = 0U;

  j = n2;

  do
  {
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    r1 = (pSrc[(2U * i0)] >> 4U) + (pSrc[(2U * i2)] >> 4U);

    r2 = (pSrc[(2U * i0)] >> 4U) - (pSrc[(2U * i2)] >> 4U);

    t1 = (pSrc[(2U * i1)] >> 4U) + (pSrc[(2U * i3)] >> 4U);

    s1 = (pSrc[(2U * i0) + 1U] >> 4U) + (pSrc[(2U * i2) + 1U] >> 4U);

    s2 = (pSrc[(2U * i0) + 1U] >> 4U) - (pSrc[(2U * i2) + 1U] >> 4U);

    pSrc[2U * i0] = (r1 + t1);

    r1 = r1 - t1;

    t2 = (pSrc[(2U * i1) + 1U] >> 4U) + (pSrc[(2U * i3) + 1U] >> 4U);

    pSrc[(2U * i0) + 1U] = (s1 + t2);

    s1 = s1 - t2;

    t1 = (pSrc[(2U * i1) + 1U] >> 4U) - (pSrc[(2U * i3) + 1U] >> 4U);

    t2 = (pSrc[(2U * i1)] >> 4U) - (pSrc[(2U * i3)] >> 4U);

    ia2 = 2U * ia1;
    co2 = pCoef[(ia2 * 2U)];
    si2 = pCoef[(ia2 * 2U) + 1U];

    pSrc[2U * i1] = (((int32_t)(((q63_t)r1 * co2) >> 32)) +
                     ((int32_t)(((q63_t)s1 * si2) >> 32)))
                    << 1U;

    pSrc[(2U * i1) + 1U] = (((int32_t)(((q63_t)s1 * co2) >> 32)) -
                            ((int32_t)(((q63_t)r1 * si2) >> 32)))
                           << 1U;

    r1 = r2 + t1;

    r2 = r2 - t1;

    s1 = s2 - t2;

    s2 = s2 + t2;

    co1 = pCoef[(ia1 * 2U)];
    si1 = pCoef[(ia1 * 2U) + 1U];

    pSrc[2U * i2] = (((int32_t)(((q63_t)r1 * co1) >> 32)) +
                     ((int32_t)(((q63_t)s1 * si1) >> 32)))
                    << 1U;

    pSrc[(2U * i2) + 1U] = (((int32_t)(((q63_t)s1 * co1) >> 32)) -
                            ((int32_t)(((q63_t)r1 * si1) >> 32)))
                           << 1U;

    ia3 = 3U * ia1;
    co3 = pCoef[(ia3 * 2U)];
    si3 = pCoef[(ia3 * 2U) + 1U];

    pSrc[2U * i3] = (((int32_t)(((q63_t)r2 * co3) >> 32)) +
                     ((int32_t)(((q63_t)s2 * si3) >> 32)))
                    << 1U;

    pSrc[(2U * i3) + 1U] = (((int32_t)(((q63_t)s2 * co3) >> 32)) -
                            ((int32_t)(((q63_t)r2 * si3) >> 32)))
                           << 1U;

    ia1 = ia1 + twidCoefModifier;

    i0 = i0 + 1U;

  } while(--j);
  twidCoefModifier <<= 2U;

  for(k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    n1 = n2;
    n2 >>= 2U;
    ia1 = 0U;

    for(j = 0U; j <= (n2 - 1U); j++)
    {
      ia2 = ia1 + ia1;
      ia3 = ia2 + ia1;
      co1 = pCoef[(ia1 * 2U)];
      si1 = pCoef[(ia1 * 2U) + 1U];
      co2 = pCoef[(ia2 * 2U)];
      si2 = pCoef[(ia2 * 2U) + 1U];
      co3 = pCoef[(ia3 * 2U)];
      si3 = pCoef[(ia3 * 2U) + 1U];

      ia1 = ia1 + twidCoefModifier;

      for(i0 = j; i0 < fftLen; i0 += n1)
      {
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        r1 = pSrc[2U * i0] + pSrc[2U * i2];

        r2 = pSrc[2U * i0] - pSrc[2U * i2];

        s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];

        s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

        t1 = pSrc[2U * i1] + pSrc[2U * i3];

        pSrc[2U * i0] = (r1 + t1) >> 2U;

        r1 = r1 - t1;

        t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];

        pSrc[(2U * i0) + 1U] = (s1 + t2) >> 2U;

        s1 = s1 - t2;

        t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];

        t2 = pSrc[2U * i1] - pSrc[2U * i3];

        pSrc[2U * i1] = (((int32_t)(((q63_t)r1 * co2) >> 32)) +
                         ((int32_t)(((q63_t)s1 * si2) >> 32))) >>
                        1U;

        pSrc[(2U * i1) + 1U] = (((int32_t)(((q63_t)s1 * co2) >> 32)) -
                                ((int32_t)(((q63_t)r1 * si2) >> 32))) >>
                               1U;

        r1 = r2 + t1;

        r2 = r2 - t1;

        s1 = s2 - t2;

        s2 = s2 + t2;

        pSrc[2U * i2] = (((int32_t)(((q63_t)r1 * co1) >> 32)) +
                         ((int32_t)(((q63_t)s1 * si1) >> 32))) >>
                        1U;

        pSrc[(2U * i2) + 1U] = (((int32_t)(((q63_t)s1 * co1) >> 32)) -
                                ((int32_t)(((q63_t)r1 * si1) >> 32))) >>
                               1U;

        pSrc[2U * i3] = (((int32_t)(((q63_t)r2 * co3) >> 32)) +
                         ((int32_t)(((q63_t)s2 * si3) >> 32))) >>
                        1U;

        pSrc[(2U * i3) + 1U] = (((int32_t)(((q63_t)s2 * co3) >> 32)) -
                                ((int32_t)(((q63_t)r2 * si3) >> 32))) >>
                               1U;
      }
    }
    twidCoefModifier <<= 2U;
  }

  j = fftLen >> 2;
  ptr1 = &pSrc[0];

  do
  {
    xa = *ptr1++;
    ya = *ptr1++;

    xb = *ptr1++;
    yb = *ptr1++;

    xc = *ptr1++;
    yc = *ptr1++;

    xd = *ptr1++;
    yd = *ptr1++;

    xa_out = xa + xb + xc + xd;

    ya_out = ya + yb + yc + yd;

    ptr1 = ptr1 - 8U;

    *ptr1++ = xa_out;
    *ptr1++ = ya_out;

    xc_out = (xa - xb + xc - xd);
    yc_out = (ya - yb + yc - yd);

    *ptr1++ = xc_out;
    *ptr1++ = yc_out;

    xb_out = (xa + yb - xc - yd);
    yb_out = (ya - xb - yc + xd);

    *ptr1++ = xb_out;
    *ptr1++ = yb_out;

    xd_out = (xa - yb - xc + yd);
    yd_out = (ya + xb - yc - xd);

    *ptr1++ = xd_out;
    *ptr1++ = yd_out;

  } while(--j);
}

void arm_radix4_butterfly_f32(
  float32_t * pSrc,
  uint16_t fftLen,
  const float32_t * pCoef,
  uint16_t twidCoefModifier)
{
  float32_t co1, co2, co3, si1, si2, si3;
  uint32_t ia1, ia2, ia3;
  uint32_t i0, i1, i2, i3;
  uint32_t n1, n2, j, k;

  float32_t t1, t2, r1, r2, s1, s2;

  n2 = fftLen;
  n1 = n2;
  for(k = fftLen; k > 1U; k >>= 2U)
  {
    n1 = n2;
    n2 >>= 2U;
    ia1 = 0U;

    j = 0;
    do
    {
      ia2 = ia1 + ia1;
      ia3 = ia2 + ia1;
      co1 = pCoef[ia1 * 2U];
      si1 = pCoef[(ia1 * 2U) + 1U];
      co2 = pCoef[ia2 * 2U];
      si2 = pCoef[(ia2 * 2U) + 1U];
      co3 = pCoef[ia3 * 2U];
      si3 = pCoef[(ia3 * 2U) + 1U];

      ia1 = ia1 + twidCoefModifier;

      i0 = j;
      do
      {
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        r1 = pSrc[(2U * i0)] + pSrc[(2U * i2)];

        r2 = pSrc[(2U * i0)] - pSrc[(2U * i2)];

        s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];

        s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

        t1 = pSrc[2U * i1] + pSrc[2U * i3];

        pSrc[2U * i0] = r1 + t1;

        r1 = r1 - t1;

        t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];

        pSrc[(2U * i0) + 1U] = s1 + t2;

        s1 = s1 - t2;

        t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];

        t2 = pSrc[2U * i1] - pSrc[2U * i3];

        pSrc[2U * i1] = (r1 * co2) + (s1 * si2);

        pSrc[(2U * i1) + 1U] = (s1 * co2) - (r1 * si2);

        r1 = r2 + t1;

        r2 = r2 - t1;

        s1 = s2 - t2;

        s2 = s2 + t2;

        pSrc[2U * i2] = (r1 * co1) + (s1 * si1);

        pSrc[(2U * i2) + 1U] = (s1 * co1) - (r1 * si1);

        pSrc[2U * i3] = (r2 * co3) + (s2 * si3);

        pSrc[(2U * i3) + 1U] = (s2 * co3) - (r2 * si3);

        i0 += n1;
      } while(i0 < fftLen);
      j++;
    } while(j <= (n2 - 1U));
    twidCoefModifier <<= 2U;
  }
}

void arm_radix4_butterfly_inverse_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  const q15_t * pCoef16,
  uint32_t twidCoefModifier)
{
  q15_t R0, R1, S0, S1, T0, T1, U0, U1;
  q15_t Co1, Si1, Co2, Si2, Co3, Si3, out1, out2;
  uint32_t n1, n2, ic, i0, i1, i2, i3, j, k;

  n2 = fftLen;
  n1 = n2;

  n2 >>= 2U;

  ic = 0U;

  i0 = 0U;

  j = n2;

  do
  {
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    T0 = pSrc16[i0 * 2U] >> 2U;
    T1 = pSrc16[(i0 * 2U) + 1U] >> 2U;

    S0 = pSrc16[i2 * 2U] >> 2U;
    S1 = pSrc16[(i2 * 2U) + 1U] >> 2U;

    R0 = __SSAT(T0 + S0, 16U);
    R1 = __SSAT(T1 + S1, 16U);

    S0 = __SSAT(T0 - S0, 16U);
    S1 = __SSAT(T1 - S1, 16U);

    T0 = pSrc16[i1 * 2U] >> 2U;
    T1 = pSrc16[(i1 * 2U) + 1U] >> 2U;

    U0 = pSrc16[i3 * 2U] >> 2U;
    U1 = pSrc16[(i3 * 2U) + 1U] >> 2U;

    T0 = __SSAT(T0 + U0, 16U);
    T1 = __SSAT(T1 + U1, 16U);

    pSrc16[i0 * 2U] = (R0 >> 1U) + (T0 >> 1U);
    pSrc16[(i0 * 2U) + 1U] = (R1 >> 1U) + (T1 >> 1U);

    R0 = __SSAT(R0 - T0, 16U);
    R1 = __SSAT(R1 - T1, 16U);

    Co2 = pCoef16[2U * ic * 2U];
    Si2 = pCoef16[(2U * ic * 2U) + 1U];

    out1 = (q15_t)((Co2 * R0 - Si2 * R1) >> 16U);

    out2 = (q15_t)((Si2 * R0 + Co2 * R1) >> 16U);

    T0 = pSrc16[i1 * 2U] >> 2U;
    T1 = pSrc16[(i1 * 2U) + 1U] >> 2U;

    pSrc16[i1 * 2U] = out1;
    pSrc16[(i1 * 2U) + 1U] = out2;

    U0 = pSrc16[i3 * 2U] >> 2U;
    U1 = pSrc16[(i3 * 2U) + 1U] >> 2U;

    T0 = __SSAT(T0 - U0, 16U);
    T1 = __SSAT(T1 - U1, 16U);

    R0 = (q15_t)__SSAT((q31_t)(S0 + T1), 16);
    R1 = (q15_t)__SSAT((q31_t)(S1 - T0), 16);

    S0 = (q15_t)__SSAT((q31_t)(S0 - T1), 16);
    S1 = (q15_t)__SSAT((q31_t)(S1 + T0), 16);

    Co1 = pCoef16[ic * 2U];
    Si1 = pCoef16[(ic * 2U) + 1U];

    out1 = (q15_t)((Co1 * S0 - Si1 * S1) >> 16U);

    out2 = (q15_t)((Si1 * S0 + Co1 * S1) >> 16U);

    pSrc16[i2 * 2U] = out1;
    pSrc16[(i2 * 2U) + 1U] = out2;

    Co3 = pCoef16[3U * ic * 2U];
    Si3 = pCoef16[(3U * ic * 2U) + 1U];

    out1 = (q15_t)((Co3 * R0 - Si3 * R1) >> 16U);

    out2 = (q15_t)((Si3 * R0 + Co3 * R1) >> 16U);

    pSrc16[i3 * 2U] = out1;
    pSrc16[(i3 * 2U) + 1U] = out2;

    ic = ic + twidCoefModifier;

    i0 = i0 + 1U;

  } while(--j);
  twidCoefModifier <<= 2U;

  for(k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    n1 = n2;
    n2 >>= 2U;
    ic = 0U;

    for(j = 0U; j <= (n2 - 1U); j++)
    {
      Co1 = pCoef16[ic * 2U];
      Si1 = pCoef16[(ic * 2U) + 1U];
      Co2 = pCoef16[2U * ic * 2U];
      Si2 = pCoef16[2U * ic * 2U + 1U];
      Co3 = pCoef16[3U * ic * 2U];
      Si3 = pCoef16[(3U * ic * 2U) + 1U];

      ic = ic + twidCoefModifier;

      for(i0 = j; i0 < fftLen; i0 += n1)
      {
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        T0 = pSrc16[i0 * 2U];
        T1 = pSrc16[(i0 * 2U) + 1U];

        S0 = pSrc16[i2 * 2U];
        S1 = pSrc16[(i2 * 2U) + 1U];

        R0 = __SSAT(T0 + S0, 16U);
        R1 = __SSAT(T1 + S1, 16U);

        S0 = __SSAT(T0 - S0, 16U);
        S1 = __SSAT(T1 - S1, 16U);

        T0 = pSrc16[i1 * 2U];
        T1 = pSrc16[(i1 * 2U) + 1U];

        U0 = pSrc16[i3 * 2U];
        U1 = pSrc16[(i3 * 2U) + 1U];

        T0 = __SSAT(T0 + U0, 16U);
        T1 = __SSAT(T1 + U1, 16U);

        pSrc16[i0 * 2U] = ((R0 >> 1U) + (T0 >> 1U)) >> 1U;
        pSrc16[(i0 * 2U) + 1U] = ((R1 >> 1U) + (T1 >> 1U)) >> 1U;

        R0 = (R0 >> 1U) - (T0 >> 1U);
        R1 = (R1 >> 1U) - (T1 >> 1U);

        out1 = (q15_t)((Co2 * R0 - Si2 * R1) >> 16);

        out2 = (q15_t)((Si2 * R0 + Co2 * R1) >> 16);

        T0 = pSrc16[i1 * 2U];
        T1 = pSrc16[(i1 * 2U) + 1U];

        pSrc16[i1 * 2U] = out1;
        pSrc16[(i1 * 2U) + 1U] = out2;

        U0 = pSrc16[i3 * 2U];
        U1 = pSrc16[(i3 * 2U) + 1U];

        T0 = __SSAT(T0 - U0, 16U);
        T1 = __SSAT(T1 - U1, 16U);

        R0 = (S0 >> 1U) + (T1 >> 1U);
        R1 = (S1 >> 1U) - (T0 >> 1U);

        S0 = (S0 >> 1U) - (T1 >> 1U);
        S1 = (S1 >> 1U) + (T0 >> 1U);

        out1 = (q15_t)((Co1 * S0 - Si1 * S1) >> 16U);
        out2 = (q15_t)((Si1 * S0 + Co1 * S1) >> 16U);

        pSrc16[i2 * 2U] = out1;
        pSrc16[(i2 * 2U) + 1U] = out2;

        out1 = (q15_t)((Co3 * R0 - Si3 * R1) >> 16U);

        out2 = (q15_t)((Si3 * R0 + Co3 * R1) >> 16U);

        pSrc16[i3 * 2U] = out1;
        pSrc16[(i3 * 2U) + 1U] = out2;
      }
    }
    twidCoefModifier <<= 2U;
  }
  n1 = n2;
  n2 >>= 2U;

  for(i0 = 0U; i0 <= (fftLen - n1); i0 += n1)
  {
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    T0 = pSrc16[i0 * 2U];
    T1 = pSrc16[(i0 * 2U) + 1U];

    S0 = pSrc16[i2 * 2U];
    S1 = pSrc16[(i2 * 2U) + 1U];

    R0 = __SSAT(T0 + S0, 16U);
    R1 = __SSAT(T1 + S1, 16U);

    S0 = __SSAT(T0 - S0, 16U);
    S1 = __SSAT(T1 - S1, 16U);

    T0 = pSrc16[i1 * 2U];
    T1 = pSrc16[(i1 * 2U) + 1U];

    U0 = pSrc16[i3 * 2U];
    U1 = pSrc16[(i3 * 2U) + 1U];

    T0 = __SSAT(T0 + U0, 16U);
    T1 = __SSAT(T1 + U1, 16U);

    pSrc16[i0 * 2U] = (R0 >> 1U) + (T0 >> 1U);
    pSrc16[(i0 * 2U) + 1U] = (R1 >> 1U) + (T1 >> 1U);

    R0 = (R0 >> 1U) - (T0 >> 1U);
    R1 = (R1 >> 1U) - (T1 >> 1U);

    T0 = pSrc16[i1 * 2U];
    T1 = pSrc16[(i1 * 2U) + 1U];

    pSrc16[i1 * 2U] = R0;
    pSrc16[(i1 * 2U) + 1U] = R1;

    U0 = pSrc16[i3 * 2U];
    U1 = pSrc16[(i3 * 2U) + 1U];

    T0 = __SSAT(T0 - U0, 16U);
    T1 = __SSAT(T1 - U1, 16U);

    pSrc16[i2 * 2U] = (S0 >> 1U) - (T1 >> 1U);
    pSrc16[(i2 * 2U) + 1U] = (S1 >> 1U) + (T0 >> 1U);

    pSrc16[i3 * 2U] = (S0 >> 1U) + (T1 >> 1U);
    pSrc16[(i3 * 2U) + 1U] = (S1 >> 1U) - (T0 >> 1U);
  }
}

void arm_radix4_butterfly_inverse_q31(
  q31_t * pSrc,
  uint32_t fftLen,
  const q31_t * pCoef,
  uint32_t twidCoefModifier)
{
  uint32_t n1, n2, ia1, ia2, ia3, i0, i1, i2, i3, j, k;
  q31_t t1, t2, r1, r2, s1, s2, co1, co2, co3, si1, si2, si3;
  q31_t xa, xb, xc, xd;
  q31_t ya, yb, yc, yd;
  q31_t xa_out, xb_out, xc_out, xd_out;
  q31_t ya_out, yb_out, yc_out, yd_out;

  q31_t * ptr1;

  n2 = fftLen;
  n1 = n2;
  /* n2 = fftLen/4 */
  n2 >>= 2U;
  i0 = 0U;
  ia1 = 0U;

  j = n2;

  do
  {
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    r1 = (pSrc[2U * i0] >> 4U) + (pSrc[2U * i2] >> 4U);

    r2 = (pSrc[2U * i0] >> 4U) - (pSrc[2U * i2] >> 4U);

    t1 = (pSrc[2U * i1] >> 4U) + (pSrc[2U * i3] >> 4U);

    s1 = (pSrc[(2U * i0) + 1U] >> 4U) + (pSrc[(2U * i2) + 1U] >> 4U);

    s2 = (pSrc[(2U * i0) + 1U] >> 4U) - (pSrc[(2U * i2) + 1U] >> 4U);

    pSrc[2U * i0] = (r1 + t1);

    r1 = r1 - t1;

    t2 = (pSrc[(2U * i1) + 1U] >> 4U) + (pSrc[(2U * i3) + 1U] >> 4U);

    pSrc[(2U * i0) + 1U] = (s1 + t2);

    s1 = s1 - t2;

    t1 = (pSrc[(2U * i1) + 1U] >> 4U) - (pSrc[(2U * i3) + 1U] >> 4U);

    t2 = (pSrc[2U * i1] >> 4U) - (pSrc[2U * i3] >> 4U);

    ia2 = 2U * ia1;
    co2 = pCoef[ia2 * 2U];
    si2 = pCoef[(ia2 * 2U) + 1U];

    pSrc[2U * i1] = (((int32_t)(((q63_t)r1 * co2) >> 32)) -
                     ((int32_t)(((q63_t)s1 * si2) >> 32)))
                    << 1U;

    pSrc[2U * i1 + 1U] = (((int32_t)(((q63_t)s1 * co2) >> 32)) +
                          ((int32_t)(((q63_t)r1 * si2) >> 32)))
                         << 1U;

    r1 = r2 - t1;

    r2 = r2 + t1;

    s1 = s2 + t2;

    s2 = s2 - t2;

    co1 = pCoef[ia1 * 2U];
    si1 = pCoef[(ia1 * 2U) + 1U];

    pSrc[2U * i2] = (((int32_t)(((q63_t)r1 * co1) >> 32)) -
                     ((int32_t)(((q63_t)s1 * si1) >> 32)))
                    << 1U;

    pSrc[(2U * i2) + 1U] = (((int32_t)(((q63_t)s1 * co1) >> 32)) +
                            ((int32_t)(((q63_t)r1 * si1) >> 32)))
                           << 1U;

    ia3 = 3U * ia1;
    co3 = pCoef[ia3 * 2U];
    si3 = pCoef[(ia3 * 2U) + 1U];

    pSrc[2U * i3] = (((int32_t)(((q63_t)r2 * co3) >> 32)) -
                     ((int32_t)(((q63_t)s2 * si3) >> 32)))
                    << 1U;

    pSrc[(2U * i3) + 1U] = (((int32_t)(((q63_t)s2 * co3) >> 32)) +
                            ((int32_t)(((q63_t)r2 * si3) >> 32)))
                           << 1U;

    ia1 = ia1 + twidCoefModifier;

    i0 = i0 + 1U;

  } while(--j);

  twidCoefModifier <<= 2U;
  for(k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    n1 = n2;
    n2 >>= 2U;
    ia1 = 0U;

    for(j = 0; j <= (n2 - 1U); j++)
    {
      ia2 = ia1 + ia1;
      ia3 = ia2 + ia1;
      co1 = pCoef[(ia1 * 2U)];
      si1 = pCoef[(ia1 * 2U) + 1U];
      co2 = pCoef[(ia2 * 2U)];
      si2 = pCoef[(ia2 * 2U) + 1U];
      co3 = pCoef[(ia3 * 2U)];
      si3 = pCoef[(ia3 * 2U) + 1U];

      ia1 = ia1 + twidCoefModifier;

      for(i0 = j; i0 < fftLen; i0 += n1)
      {
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        r1 = pSrc[2U * i0] + pSrc[2U * i2];

        r2 = pSrc[2U * i0] - pSrc[2U * i2];

        s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];

        s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

        t1 = pSrc[2U * i1] + pSrc[2U * i3];

        pSrc[2U * i0] = (r1 + t1) >> 2U;

        r1 = r1 - t1;

        t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];

        pSrc[(2U * i0) + 1U] = (s1 + t2) >> 2U;

        s1 = s1 - t2;

        t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];

        t2 = pSrc[2U * i1] - pSrc[2U * i3];

        pSrc[2U * i1] = (((int32_t)(((q63_t)r1 * co2) >> 32U)) -
                         ((int32_t)(((q63_t)s1 * si2) >> 32U))) >>
                        1U;

        pSrc[(2U * i1) + 1U] = (((int32_t)(((q63_t)s1 * co2) >> 32U)) +
                                ((int32_t)(((q63_t)r1 * si2) >> 32U))) >>
                               1U;

        r1 = r2 - t1;

        r2 = r2 + t1;

        s1 = s2 + t2;

        s2 = s2 - t2;

        pSrc[2U * i2] = (((int32_t)(((q63_t)r1 * co1) >> 32)) -
                         ((int32_t)(((q63_t)s1 * si1) >> 32))) >>
                        1U;

        pSrc[(2U * i2) + 1U] = (((int32_t)(((q63_t)s1 * co1) >> 32)) +
                                ((int32_t)(((q63_t)r1 * si1) >> 32))) >>
                               1U;

        pSrc[(2U * i3)] = (((int32_t)(((q63_t)r2 * co3) >> 32)) -
                           ((int32_t)(((q63_t)s2 * si3) >> 32))) >>
                          1U;

        pSrc[(2U * i3) + 1U] = (((int32_t)(((q63_t)s2 * co3) >> 32)) +
                                ((int32_t)(((q63_t)r2 * si3) >> 32))) >>
                               1U;
      }
    }
    twidCoefModifier <<= 2U;
  }
  j = fftLen >> 2;
  ptr1 = &pSrc[0];

  do
  {
    xa = *ptr1++;
    ya = *ptr1++;

    xb = *ptr1++;
    yb = *ptr1++;

    xc = *ptr1++;
    yc = *ptr1++;

    xd = *ptr1++;
    yd = *ptr1++;

    xa_out = xa + xb + xc + xd;

    ya_out = ya + yb + yc + yd;

    ptr1 = ptr1 - 8U;

    *ptr1++ = xa_out;
    *ptr1++ = ya_out;

    xc_out = (xa - xb + xc - xd);
    yc_out = (ya - yb + yc - yd);

    *ptr1++ = xc_out;
    *ptr1++ = yc_out;

    xb_out = (xa - yb - xc + yd);
    yb_out = (ya + xb - yc - xd);

    *ptr1++ = xb_out;
    *ptr1++ = yb_out;

    xd_out = (xa + yb - xc - yd);
    yd_out = (ya - xb - yc + xd);

    *ptr1++ = xd_out;
    *ptr1++ = yd_out;

  } while(--j);
}

void arm_radix4_butterfly_inverse_f32(
  float32_t * pSrc,
  uint16_t fftLen,
  const float32_t * pCoef,
  uint16_t twidCoefModifier,
  float32_t onebyfftLen)
{
  float32_t co1, co2, co3, si1, si2, si3;
  uint32_t ia1, ia2, ia3;
  uint32_t i0, i1, i2, i3;
  uint32_t n1, n2, j, k;

  float32_t t1, t2, r1, r2, s1, s2;

  n2 = fftLen;
  n1 = n2;

  for(k = fftLen; k > 4U; k >>= 2U)
  {
    n1 = n2;
    n2 >>= 2U;
    ia1 = 0U;

    j = 0;
    do
    {
      ia2 = ia1 + ia1;
      ia3 = ia2 + ia1;
      co1 = pCoef[ia1 * 2U];
      si1 = pCoef[(ia1 * 2U) + 1U];
      co2 = pCoef[ia2 * 2U];
      si2 = pCoef[(ia2 * 2U) + 1U];
      co3 = pCoef[ia3 * 2U];
      si3 = pCoef[(ia3 * 2U) + 1U];

      ia1 = ia1 + twidCoefModifier;

      i0 = j;
      do
      {
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        r1 = pSrc[(2U * i0)] + pSrc[(2U * i2)];

        r2 = pSrc[(2U * i0)] - pSrc[(2U * i2)];

        s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];

        s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

        t1 = pSrc[2U * i1] + pSrc[2U * i3];

        pSrc[2U * i0] = r1 + t1;

        r1 = r1 - t1;

        t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];

        pSrc[(2U * i0) + 1U] = s1 + t2;

        s1 = s1 - t2;

        t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];

        t2 = pSrc[2U * i1] - pSrc[2U * i3];

        pSrc[2U * i1] = (r1 * co2) - (s1 * si2);

        pSrc[(2U * i1) + 1U] = (s1 * co2) + (r1 * si2);

        r1 = r2 - t1;

        r2 = r2 + t1;

        s1 = s2 + t2;

        s2 = s2 - t2;

        pSrc[2U * i2] = (r1 * co1) - (s1 * si1);

        pSrc[(2U * i2) + 1U] = (s1 * co1) + (r1 * si1);

        pSrc[2U * i3] = (r2 * co3) - (s2 * si3);

        pSrc[(2U * i3) + 1U] = (s2 * co3) + (r2 * si3);

        i0 += n1;
      } while(i0 < fftLen);
      j++;
    } while(j <= (n2 - 1U));
    twidCoefModifier <<= 2U;
  }
  n1 = n2;
  n2 >>= 2U;

  for(i0 = 0U; i0 <= (fftLen - n1); i0 += n1)
  {
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    r1 = pSrc[2U * i0] + pSrc[2U * i2];

    r2 = pSrc[2U * i0] - pSrc[2U * i2];

    s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];

    s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

    t1 = pSrc[2U * i1] + pSrc[2U * i3];

    pSrc[2U * i0] = (r1 + t1) * onebyfftLen;

    r1 = r1 - t1;

    t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];

    pSrc[(2U * i0) + 1U] = (s1 + t2) * onebyfftLen;

    s1 = s1 - t2;

    t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];

    t2 = pSrc[2U * i1] - pSrc[2U * i3];

    pSrc[2U * i1] = r1 * onebyfftLen;

    pSrc[(2U * i1) + 1U] = s1 * onebyfftLen;

    r1 = r2 - t1;

    r2 = r2 + t1;

    s1 = s2 + t2;

    s2 = s2 - t2;

    pSrc[2U * i2] = r1 * onebyfftLen;

    pSrc[(2U * i2) + 1U] = s1 * onebyfftLen;

    pSrc[2U * i3] = r2 * onebyfftLen;

    pSrc[(2U * i3) + 1U] = s2 * onebyfftLen;
  }
}
