/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkBlendMode_DEFINED
#  define SkBlendMode_DEFINED
#  include "include/core/SkTypes.h"
enum class SkBlendMode
{
  kClear,
  kSrc,
  kDst,
  kSrcOver,
  kDstOver,
  kSrcIn,
  kDstIn,
  kSrcOut,
  kDstOut,
  kSrcATop,
  kDstATop,
  kXor,
  kPlus,
  kModulate,
  kScreen,
  kLastCoeffMode = kScreen,
  kOverlay,
  kDarken,
  kLighten,
  kColorDodge,
  kColorBurn,
  kHardLight,
  kSoftLight,
  kDifference,
  kExclusion,
  kMultiply,
  kLastSeparableMode = kMultiply,
  kHue,
  kSaturation,
  kColor,
  kLuminosity,
  kLastMode = kLuminosity
};
/** Returns name of blendMode as null-terminated C string.

    @param blendMode  one of:
                      SkBlendMode::kClear, SkBlendMode::kSrc, SkBlendMode::kDst,
                      SkBlendMode::kSrcOver, SkBlendMode::kDstOver, SkBlendMode::kSrcIn,
                      SkBlendMode::kDstIn, SkBlendMode::kSrcOut, SkBlendMode::kDstOut,
                      SkBlendMode::kSrcATop, SkBlendMode::kDstATop, SkBlendMode::kXor,
                      SkBlendMode::kPlus, SkBlendMode::kModulate, SkBlendMode::kScreen,
                      SkBlendMode::kOverlay, SkBlendMode::kDarken, SkBlendMode::kLighten,
                      SkBlendMode::kColorDodge, SkBlendMode::kColorBurn, SkBlendMode::kHardLight,
                      SkBlendMode::kSoftLight, SkBlendMode::kDifference, SkBlendMode::kExclusion,
                      SkBlendMode::kMultiply, SkBlendMode::kHue, SkBlendMode::kSaturation,
                      SkBlendMode::kColor, SkBlendMode::kLuminosity
    @return           C string
*/
SK_API const char* SkBlendMode_Name(SkBlendMode blendMode);
#endif
