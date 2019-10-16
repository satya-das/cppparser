/*
* Copyright 2017 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/
#ifndef SkHighContrastFilter_DEFINED
#  define SkHighContrastFilter_DEFINED
#  include "include/core/SkColorFilter.h"
#  include "include/core/SkPaint.h"
/**
 *  Configuration struct for SkHighContrastFilter.
 *
 *  Provides transformations to improve contrast for users with low vision.
 */
struct SkHighContrastConfig
{
  enum class InvertStyle
  {
    kNoInvert,
    kInvertBrightness,
    kInvertLightness,
    kLast = kInvertLightness
  };
  SkHighContrastConfig()
  {
    fGrayscale = false;
    fInvertStyle = InvertStyle::kNoInvert;
    fContrast = 0.0f;
  }
  SkHighContrastConfig(bool grayscale, InvertStyle invertStyle, SkScalar contrast)
    : fGrayscale(grayscale)
    , fInvertStyle(invertStyle)
    , fContrast(contrast)
  {
  }
  bool isValid() const
  {
    return fInvertStyle >= InvertStyle::kNoInvert && fInvertStyle <= InvertStyle::kInvertLightness && fContrast >= -1.0 && fContrast <= 1.0;
  }
  bool fGrayscale;
  InvertStyle fInvertStyle;
  SkScalar fContrast;
};
/**
 *  Color filter that provides transformations to improve contrast
 *  for users with low vision.
 *
 *  Applies the following transformations in this order. Each of these
 *  can be configured using SkHighContrastConfig.
 *
 *    - Conversion to grayscale
 *    - Color inversion (either in RGB or HSL space)
 *    - Increasing the resulting contrast.
 *
 * Calling SkHighContrastFilter::Make will return nullptr if the config is
 * not valid, e.g. if you try to call it with a contrast outside the range of
 * -1.0 to 1.0.
 */
class SK_API SkHighContrastFilter
{
public:
  static sk_sp<SkColorFilter> Make(const SkHighContrastConfig& config);
  static void RegisterFlattenables();
};
#endif
