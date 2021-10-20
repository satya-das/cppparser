/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkFontMetrics_DEFINED
#  define SkFontMetrics_DEFINED
#  include "include/core/SkScalar.h"
/** \class SkFontMetrics
    The metrics of an SkFont.
    The metric values are consistent with the Skia y-down coordinate system.
 */
struct SK_API SkFontMetrics
{
    /** \enum FontMetricsFlags
     FontMetricsFlags indicate when certain metrics are valid;
     the underline or strikeout metrics may be valid and zero.
     Fonts with embedded bitmaps may not have valid underline or strikeout metrics.
     */
  enum FontMetricsFlags {
        kUnderlineThicknessIsValid_Flag = 1 << 0, //!< set if fUnderlineThickness is valid
        kUnderlinePositionIsValid_Flag  = 1 << 1, //!< set if fUnderlinePosition is valid
        kStrikeoutThicknessIsValid_Flag = 1 << 2, //!< set if fStrikeoutThickness is valid
        kStrikeoutPositionIsValid_Flag  = 1 << 3, //!< set if fStrikeoutPosition is valid
  };
  uint32_t fFlags;
  SkScalar fTop;
  SkScalar fAscent;
  SkScalar fDescent;
  SkScalar fBottom;
  SkScalar fLeading;
  SkScalar fAvgCharWidth;
  SkScalar fMaxCharWidth;
  SkScalar fXMin;
  SkScalar fXMax;
  SkScalar fXHeight;
  SkScalar fCapHeight;
  SkScalar fUnderlineThickness;
  SkScalar fUnderlinePosition;
  SkScalar fStrikeoutThickness;
  SkScalar fStrikeoutPosition;
    /** Returns true if SkFontMetrics has a valid underline thickness, and sets
     thickness to that value. If the underline thickness is not valid,
     return false, and ignore thickness.

     @param thickness  storage for underline width
     @return           true if font specifies underline width
     */
  bool hasUnderlineThickness(SkScalar* thickness) const
  {
        if (SkToBool(fFlags & kUnderlineThicknessIsValid_Flag)) {
            *thickness = fUnderlineThickness;
            return true;
        }
        return false;
  }
    /** Returns true if SkFontMetrics has a valid underline position, and sets
     position to that value. If the underline position is not valid,
     return false, and ignore position.

     @param position  storage for underline position
     @return          true if font specifies underline position
     */
  bool hasUnderlinePosition(SkScalar* position) const
  {
        if (SkToBool(fFlags & kUnderlinePositionIsValid_Flag)) {
            *position = fUnderlinePosition;
            return true;
        }
        return false;
  }
    /** Returns true if SkFontMetrics has a valid strikeout thickness, and sets
     thickness to that value. If the underline thickness is not valid,
     return false, and ignore thickness.

     @param thickness  storage for strikeout width
     @return           true if font specifies strikeout width
     */
  bool hasStrikeoutThickness(SkScalar* thickness) const
  {
        if (SkToBool(fFlags & kStrikeoutThicknessIsValid_Flag)) {
            *thickness = fStrikeoutThickness;
            return true;
        }
        return false;
  }
    /** Returns true if SkFontMetrics has a valid strikeout position, and sets
     position to that value. If the underline position is not valid,
     return false, and ignore position.

     @param position  storage for strikeout position
     @return          true if font specifies strikeout position
     */
  bool hasStrikeoutPosition(SkScalar* position) const
  {
        if (SkToBool(fFlags & kStrikeoutPositionIsValid_Flag)) {
            *position = fStrikeoutPosition;
            return true;
        }
        return false;
  }
};
#endif
