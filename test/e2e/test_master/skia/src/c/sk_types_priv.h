/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef sk_types_priv_DEFINED
#  define sk_types_priv_DEFINED
#  include "include/c/sk_types.h"
class SkMaskFilter;
class SkPaint;
class SkShader;
static const SkPaint& AsPaint(const sk_paint_t& cpaint)
{
  return reinterpret_cast<const SkPaint&>(cpaint);
}
static const SkPaint* AsPaint(const sk_paint_t* cpaint)
{
  return reinterpret_cast<const SkPaint*>(cpaint);
}
static SkPaint* AsPaint(sk_paint_t* cpaint)
{
  return reinterpret_cast<SkPaint*>(cpaint);
}
static SkMaskFilter* AsMaskFilter(sk_maskfilter_t* cfilter)
{
  return reinterpret_cast<SkMaskFilter*>(cfilter);
}
static sk_maskfilter_t* ToMaskFilter(SkMaskFilter* filter)
{
  return reinterpret_cast<sk_maskfilter_t*>(filter);
}
static SkShader* AsShader(sk_shader_t* cshader)
{
  return reinterpret_cast<SkShader*>(cshader);
}
#endif
