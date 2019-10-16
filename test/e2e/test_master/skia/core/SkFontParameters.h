/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkFontParameters_DEFINED
#  define SkFontParameters_DEFINED
#  include "include/core/SkScalar.h"
#  include "include/core/SkTypes.h"
struct SkFontParameters
{
  struct Variation
  {
    struct Axis
    {
      SkFourByteTag tag;
      float min;
      float def;
      float max;
      bool isHidden() const
      {
        return flags & HIDDEN;
      }
      void setHidden(bool hidden)
      {
        flags = hidden ? (flags | HIDDEN) : (flags & ~HIDDEN);
      }
    private:
      static uint16_t HIDDEN = 0x0001;
      uint16_t flags;
    };
  };
};
#endif
