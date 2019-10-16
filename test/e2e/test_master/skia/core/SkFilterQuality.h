/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkFilterQuality_DEFINED
#  define SkFilterQuality_DEFINED
#  include "include/core/SkTypes.h"
/**
 *  Controls how much filtering to be done when scaling/transforming complex colors
 *  e.g. images
 */
enum SkFilterQuality
{
  kNone_SkFilterQuality,
  kLow_SkFilterQuality,
  kMedium_SkFilterQuality,
  kHigh_SkFilterQuality,
  kLast_SkFilterQuality = kHigh_SkFilterQuality
};
#endif
