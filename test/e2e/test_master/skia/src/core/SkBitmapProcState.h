/*
 * Copyright 2007 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkBitmapProcState_DEFINED
#  define SkBitmapProcState_DEFINED
#  include "include/core/SkBitmap.h"
#  include "include/core/SkPaint.h"
#  include "include/core/SkShader.h"
#  include "include/private/SkFixed.h"
#  include "include/private/SkFloatBits.h"
#  include "include/private/SkTemplates.h"
#  include "src/core/SkArenaAlloc.h"
#  include "src/core/SkBitmapController.h"
#  include "src/core/SkMatrixPriv.h"
#  include "src/core/SkMipMap.h"
typedef SkFixed3232 SkFractionalInt;
#  define SkScalarToFractionalInt(x)	  SkScalarToFixed3232(x)
#  define SkFractionalIntToFixed(x)	   SkFixed3232ToFixed(x)
#  define SkFixedToFractionalInt(x)	   SkFixedToFixed3232(x)
#  define SkFractionalIntToInt(x)	     SkFixed3232ToInt(x)
class SkPaint;
struct SkBitmapProcInfo
{
  SkBitmapProcInfo(const SkImage_Base*, SkTileMode tmx, SkTileMode tmy);
  ~SkBitmapProcInfo();
  const SkImage_Base* fImage;
  SkPixmap fPixmap;
  SkMatrix fInvMatrix;
    // TODO: combine fInvMatrix and fRealInvMatrix.
  SkMatrix fRealInvMatrix;
  SkColor fPaintColor;
  SkTileMode fTileModeX;
  SkTileMode fTileModeY;
  SkFilterQuality fFilterQuality;
  SkMatrix::TypeMask fInvType;
  bool init(const SkMatrix& inverse, const SkPaint&);
private:
  enum {
        kBMStateSize = 136  // found by inspection. if too small, we will call new/delete
  };
  SkSTArenaAlloc<kBMStateSize> fAlloc;
  SkBitmapController::State* fBMState;
};
struct SkBitmapProcState : public SkBitmapProcInfo
{
  SkBitmapProcState(const SkImage_Base* image, SkTileMode tmx, SkTileMode tmy)
    : SkBitmapProcInfo(image, tmx, tmy)
  {
  }
  bool setup(const SkMatrix& inv, const SkPaint& paint)
  {
    return this->init(inv, paint) && this->chooseProcs();
  }
  typedef void (*ShaderProc32) (const void* ctx, int x, int y, SkPMColor[], int count);
  typedef void (*MatrixProc) (const SkBitmapProcState&, uint32_t bitmapXY[], int count, int x, int y);
  typedef void (*SampleProc32) (const SkBitmapProcState&, const uint32_t[], int count, SkPMColor colors[]);
  SkMatrixPriv::MapXYProc fInvProc;
  SkFractionalInt fInvSxFractionalInt;
  SkFractionalInt fInvKyFractionalInt;
  SkFixed fFilterOneX;
  SkFixed fFilterOneY;
  SkFixed fInvSx;
  SkFixed fInvKy;
  SkPMColor fPaintPMColor;
  uint16_t fAlphaScale;
    /** Given the byte size of the index buffer to be passed to the matrix proc,
        return the maximum number of resulting pixels that can be computed
        (i.e. the number of SkPMColor values to be written by the sample proc).
        This routine takes into account that filtering and scale-vs-affine
        affect the amount of buffer space needed.

        Only valid to call after chooseProcs (setContext) has been called. It is
        safe to call this inside the shader's shadeSpan() method.
     */
  int maxCountForBufferSize(size_t bufferSize) const;
    // If a shader proc is present, then the corresponding matrix/sample procs
    // are ignored
  ShaderProc32 getShaderProc32() const
  {
    return fShaderProc32;
  }
#  ifdef SK_DEBUG
  MatrixProc getMatrixProc() const;
#  else 
  MatrixProc getMatrixProc() const
  {
    return fMatrixProc;
  }
#  endif
  SampleProc32 getSampleProc32() const
  {
    return fSampleProc32;
  }
private:
  ShaderProc32 fShaderProc32;
    // These are used if the shaderproc is nullptr
  MatrixProc fMatrixProc;
  SampleProc32 fSampleProc32;
  MatrixProc chooseMatrixProc(bool trivial_matrix);
  bool chooseProcs();
  ShaderProc32 chooseShaderProc32();
    // Return false if we failed to setup for fast translate (e.g. overflow)
  bool setupForTranslate();
#  ifdef SK_DEBUG
  static void DebugMatrixProc(const SkBitmapProcState&, uint32_t[], int count, int x, int y);
#  endif
};
/*  Macros for packing and unpacking pairs of 16bit values in a 32bit uint.
    Used to allow access to a stream of uint16_t either one at a time, or
    2 at a time by unpacking a uint32_t
 */
#  ifdef SK_CPU_BENDIAN
#    define PACK_TWO_SHORTS(pri, sec) ((pri) << 16 | (sec))
#    define UNPACK_PRIMARY_SHORT(packed)    ((uint32_t)(packed) >> 16)
#    define UNPACK_SECONDARY_SHORT(packed)  ((packed) & 0xFFFF)
#  else 
#    define PACK_TWO_SHORTS(pri, sec) ((pri) | ((sec) << 16))
#    define UNPACK_PRIMARY_SHORT(packed)    ((packed) & 0xFFFF)
#    define UNPACK_SECONDARY_SHORT(packed)  ((uint32_t)(packed) >> 16)
#  endif
#  ifdef SK_DEBUG
static uint32_t pack_two_shorts(U16CPU pri, U16CPU sec)
{
  SkASSERT((uint16_t) pri == pri);
  SkASSERT((uint16_t) sec == sec);
  return PACK_TWO_SHORTS(pri, sec);
}
#  else 
#    define pack_two_shorts(pri, sec)	   PACK_TWO_SHORTS(pri, sec)
#  endif
// Helper class for mapping the middle of pixel (x, y) into SkFractionalInt bitmap space.
// Discussion:
// Overall, this code takes a point in destination space, and uses the center of the pixel
// at (x, y) to determine the sample point in source space. It then adjusts the pixel by different
// amounts based in filtering and tiling.
// This code can be broken into two main cases based on filtering:
// * no filtering (nearest neighbor) - when using nearest neighbor filtering all tile modes reduce
// the sampled by one ulp. If a simple point pt lies precisely on XXX.1/2 then it forced down
// when positive making 1/2 + 1/2 = .999999 instead of 1.0.
// * filtering - in the filtering case, the code calculates the -1/2 shift for starting the
// bilerp kernel. There is a twist; there is a big difference between clamp and the other tile
// modes. In tile and repeat the matrix has been reduced by an additional 1/width and 1/height
// factor. This maps from destination space to [0, 1) (instead of source space) to allow easy
// modulo arithmetic. This means that the -1/2 needed by bilerp is actually 1/2 * 1/width for x
// and 1/2 * 1/height for y. This is what happens when the poorly named fFilterOne{X|Y} is
// divided by two.
class SkBitmapProcStateAutoMapper
{
public:
  SkBitmapProcStateAutoMapper(const SkBitmapProcState& s, int x, int y, SkPoint* scalarPoint = nullptr)
  {
    SkPoint pt;
    s.fInvProc(s.fInvMatrix, SkIntToScalar(x) + SK_ScalarHalf, SkIntToScalar(y) + SK_ScalarHalf, &pt);
    SkFixed biasX, biasY;
    if (s.fFilterQuality == kNone_SkFilterQuality)
    {
            // SkFixed epsilon bias to ensure inverse-mapped bitmap coordinates are rounded
            // consistently WRT geometry.  Note that we only need the bias for positive scales:
            // for negative scales, the rounding is intrinsically correct.
            // We scale it to persist SkFractionalInt -> SkFixed conversions.
      biasX = (s.fInvMatrix.getScaleX() > 0);
      biasY = (s.fInvMatrix.getScaleY() > 0);
    }
    else 
    {
      biasX = s.fFilterOneX >> 1;
      biasY = s.fFilterOneY >> 1;
    }
        // punt to unsigned for defined underflow behavior
    fX = (SkFractionalInt) ((uint64_t) SkScalarToFractionalInt(pt.x()) - (uint64_t) SkFixedToFractionalInt(biasX));
    fY = (SkFractionalInt) ((uint64_t) SkScalarToFractionalInt(pt.y()) - (uint64_t) SkFixedToFractionalInt(biasY));
    if (scalarPoint)
    {
      scalarPoint->set(pt.x() - SkFixedToScalar(biasX), pt.y() - SkFixedToScalar(biasY));
    }
  }
  SkFractionalInt fractionalIntX() const
  {
    return fX;
  }
  SkFractionalInt fractionalIntY() const
  {
    return fY;
  }
  SkFixed fixedX() const
  {
    return SkFractionalIntToFixed(fX);
  }
  SkFixed fixedY() const
  {
    return SkFractionalIntToFixed(fY);
  }
  int intX() const
  {
    return SkFractionalIntToInt(fX);
  }
  int intY() const
  {
    return SkFractionalIntToInt(fY);
  }
private:
  SkFractionalInt fX, fY;
};
#endif
