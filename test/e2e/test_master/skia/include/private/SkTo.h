/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkTo_DEFINED
#  define SkTo_DEFINED
#  include "include/core/SkTypes.h"
#  include "include/private/SkTFitsIn.h"
template <typename D, typename S>
D SkTo(S s)
{
  return SkASSERT(SkTFitsIn<D>(s)), static_cast<D>(s);
}
template <typename S>
int8_t SkToS8(S x)
{
  return SkTo<int8_t>(x);
}
template <typename S>
uint8_t SkToU8(S x)
{
  return SkTo<uint8_t>(x);
}
template <typename S>
int16_t SkToS16(S x)
{
  return SkTo<int16_t>(x);
}
template <typename S>
uint16_t SkToU16(S x)
{
  return SkTo<uint16_t>(x);
}
template <typename S>
int32_t SkToS32(S x)
{
  return SkTo<int32_t>(x);
}
template <typename S>
uint32_t SkToU32(S x)
{
  return SkTo<uint32_t>(x);
}
template <typename S>
int SkToInt(S x)
{
  return SkTo<int>(x);
}
template <typename S>
unsigned SkToUInt(S x)
{
  return SkTo<unsigned>(x);
}
template <typename S>
size_t SkToSizeT(S x)
{
  return SkTo<size_t>(x);
}
#endif
