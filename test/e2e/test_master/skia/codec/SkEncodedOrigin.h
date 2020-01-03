/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkEncodedOrigin_DEFINED
#  define SkEncodedOrigin_DEFINED
#  include "include/core/SkMatrix.h"
// These values match the orientation www.exif.org/Exif2-2.PDF.
enum SkEncodedOrigin
{
  kTopLeft_SkEncodedOrigin = 1,
  kTopRight_SkEncodedOrigin = 2,
  kBottomRight_SkEncodedOrigin = 3,
  kBottomLeft_SkEncodedOrigin = 4,
  kLeftTop_SkEncodedOrigin = 5,
  kRightTop_SkEncodedOrigin = 6,
  kRightBottom_SkEncodedOrigin = 7,
  kLeftBottom_SkEncodedOrigin = 8,
  kDefault_SkEncodedOrigin = kTopLeft_SkEncodedOrigin,
  kLast_SkEncodedOrigin = kLeftBottom_SkEncodedOrigin
};
/**
 * Given an encoded origin and the width and height of the source data, returns a matrix
 * that transforms the source rectangle [0, 0, w, h] to a correctly oriented destination
 * rectangle, with the upper left corner still at [0, 0].
 */
static SkMatrix SkEncodedOriginToMatrix(SkEncodedOrigin origin, int w, int h)
{
  switch(origin)
  {
    case kTopLeft_SkEncodedOrigin:
      return SkMatrix::I();
    case kTopRight_SkEncodedOrigin:
      return SkMatrix::MakeAll(-1, 0, w, 0, 1, 0, 0, 0, 1);
    case kBottomRight_SkEncodedOrigin:
      return SkMatrix::MakeAll(-1, 0, w, 0, -1, h, 0, 0, 1);
    case kBottomLeft_SkEncodedOrigin:
      return SkMatrix::MakeAll(1, 0, 0, 0, -1, h, 0, 0, 1);
    case kLeftTop_SkEncodedOrigin:
      return SkMatrix::MakeAll(0, 1, 0, 1, 0, 0, 0, 0, 1);
    case kRightTop_SkEncodedOrigin:
      return SkMatrix::MakeAll(0, -1, h, 1, 0, 0, 0, 0, 1);
    case kRightBottom_SkEncodedOrigin:
      return SkMatrix::MakeAll(0, -1, h, -1, 0, w, 0, 0, 1);
    case kLeftBottom_SkEncodedOrigin:
      return SkMatrix::MakeAll(0, 1, 0, -1, 0, w, 0, 0, 1);
  }
  SK_ABORT("Unexpected origin");
}
#endif
