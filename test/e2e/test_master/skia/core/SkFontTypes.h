/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkFontTypes_DEFINED
#  define SkFontTypes_DEFINED
enum class SkTextEncoding
{
  kUTF8,
  kUTF16,
  kUTF32,
  kGlyphID
};
enum class SkFontHinting
{
  kNone,
  kSlight,
  kNormal,
  kFull
};
#endif
