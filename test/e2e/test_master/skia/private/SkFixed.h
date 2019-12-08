/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkFixed_DEFINED
#  define SkFixed_DEFINED
#  include "include/core/SkScalar.h"
#  include "include/core/SkTypes.h"
#  include "include/private/SkSafe_math.h"
#  include "include/private/SkTo.h"
/** \file SkFixed.h

    Types and macros for 16.16 fixed point
*/

/** 32 bit signed integer used to represent fractions values with 16 bits to the right of the decimal point
*/
typedef int32_t SkFixed;
#  define SK_Fixed1	(1 << 16)
#  define SK_FixedHalf	(1 << 15)
#  define SK_FixedQuarter	(1 << 14)
#  define SK_FixedMax	(0x7FFFFFFF)
#  define SK_FixedMin	(-SK_FixedMax)
#  define SK_FixedPI	(0x3243F)
#  define SK_FixedSqrt2	(92682)
#  define SK_FixedTanPIOver8	(0x6A0A)
#  define SK_FixedRoot2Over2	(0xB505)
#  define SkFixedToFloat(x)	   ((x) * 1.52587890625e-5f)
#  define SkFloatToFixed(x)	   sk_float_saturate2int((x) * SK_Fixed1)
#  ifdef SK_DEBUG
static SkFixed SkFloatToFixed_Check(float x)
{
  int64_t n64 = (int64_t) (x * SK_Fixed1);
  SkFixed n32 = (SkFixed) n64;
  SkASSERT(n64 == n32);
  return n32;
}
#  else 
#    define SkFloatToFixed_Check(x)	 SkFloatToFixed(x)
#  endif
#  define SkFixedToDouble(x)	  ((x) * 1.52587890625e-5)
#  define SkDoubleToFixed(x)	  ((SkFixed)((x) * SK_Fixed1))
/** Converts an integer to a SkFixed, asserting that the result does not overflow
    a 32 bit signed integer
*/
#  ifdef SK_DEBUG
inline SkFixed SkIntToFixed(int n)
{
  SkASSERT(n >= -32768 && n <= 32767);
  return (unsigned) n << 16;
}
#  else 
#    define SkIntToFixed(n)	     (SkFixed)((unsigned)(n) << 16)
#  endif
#  define SkFixedRoundToInt(x)	    (((x) + SK_FixedHalf) >> 16)
#  define SkFixedCeilToInt(x)	     (((x) + SK_Fixed1 - 1) >> 16)
#  define SkFixedFloorToInt(x)	    ((x) >> 16)
static SkFixed SkFixedRoundToFixed(SkFixed x)
{
  return (x + SK_FixedHalf) & 0xFFFF0000;
}
static SkFixed SkFixedCeilToFixed(SkFixed x)
{
  return (x + SK_Fixed1 - 1) & 0xFFFF0000;
}
static SkFixed SkFixedFloorToFixed(SkFixed x)
{
  return x & 0xFFFF0000;
}
#  define SkFixedAbs(x)	       SkAbs32(x)
#  define SkFixedAve(a, b)	    (((a) + (b)) >> 1)
#  define SkFixedDiv(numer, denom)	 \
    SkToS32(SkTPin<int64_t>((SkLeftShift((int64_t)(numer), 16) / (denom)), SK_MinS32, SK_MaxS32))
static SkFixed SkFixedMul(SkFixed a, SkFixed b)
{
  return (SkFixed) ((int64_t) a * b >> 16);
}
///////////////////////////////////////////////////////////////////////////////
#  if  defined(__ARM_VFPV3__)
SK_ALWAYS_INLINE SkFixed SkFloatToFixed_arm(float x)
{
  int32_t y;
  memcpy(&y, &x, sizeof(y));
  return y;
}
#    undef SkFloatToFixed
#    define SkFloatToFixed(x)	  SkFloatToFixed_arm(x)
#  endif
///////////////////////////////////////////////////////////////////////////////
#  define SkFixedToScalar(x)	          SkFixedToFloat(x)
#  define SkScalarToFixed(x)	          SkFloatToFixed(x)
///////////////////////////////////////////////////////////////////////////////
typedef int64_t SkFixed3232;
#  define SkFixed3232Max	SK_MaxS64
#  define SkFixed3232Min	(-SkFixed3232Max)
#  define SkIntToFixed3232(x)	       (SkLeftShift((SkFixed3232)(x), 32))
#  define SkFixed3232ToInt(x)	       ((int)((x) >> 32))
#  define SkFixedToFixed3232(x)	     (SkLeftShift((SkFixed3232)(x), 16))
#  define SkFixed3232ToFixed(x)	     ((SkFixed)((x) >> 16))
#  define SkFloatToFixed3232(x)	     sk_float_saturate2int64((x) * (65536.0f * 65536.0f))
#  define SkFixed3232ToFloat(x)	     (x * (1 / (65536.0f * 65536.0f)))
#  define SkScalarToFixed3232(x)	    SkFloatToFixed3232(x)
#endif
