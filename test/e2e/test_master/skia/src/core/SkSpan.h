/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkSpan_DEFINED
#  define SkSpan_DEFINED
#  include <cstddef>
#  include "include/private/SkTo.h"
template <typename T>
class SkSpan
{
public:
  SkSpan()
    : fPtr(nullptr)
    , fSize(0)
  {
  }
  SkSpan(T* ptr, size_t size)
    : fPtr(ptr)
    , fSize(size)
  {
  }
  template <typename U, typename  = typename std::enable_if<std::is_same<const U, T>::value>::type>
  SkSpan(const SkSpan<U>& that)
    : fPtr(that.data())
    , fSize(that.size())
  {
  }
  SkSpan(const SkSpan& o);
  SkSpan& operator=(const SkSpan& that)
  {
    fPtr = that.fPtr;
    fSize = that.fSize;
    return *this;
  }
  T& operator [](size_t i) const
  {
    return fPtr[i];
  }
  T& front() const
  {
    return fPtr[0];
  }
  T& back() const
  {
    return fPtr[fSize - 1];
  }
  T* begin() const
  {
    return fPtr;
  }
  T* end() const
  {
    return fPtr + fSize;
  }
  const T* cbegin() const
  {
    return fPtr;
  }
  const T* cend() const
  {
    return fPtr + fSize;
  }
  T* data() const
  {
    return fPtr;
  }
  size_t size() const
  {
    return fSize;
  }
  bool empty() const
  {
    return fSize == 0;
  }
  size_t size_bytes() const
  {
    return fSize * sizeof(T);
  }
  SkSpan<T> first(size_t prefixLen)
  {
    return SkSpan<T>(fPtr, prefixLen);
  }
private:
  T* fPtr;
  size_t fSize;
};
template <typename T, typename S>
inline SkSpan<T> SkMakeSpan(T* p, S s)
{
  return SkSpan<T>(p, SkTo<size_t>(s));
}
template <size_t N, typename T>
inline SkSpan<T> SkMakeSpan(T (&a)[N])
{
  return SkSpan<T>(a, N);
}
template <typename Container>
inline auto SkMakeSpan(Container& c) -> SkSpan<typename std::remove_reference<decltype(*(c.data()))>::type>
{
  return {c.data(), c.size()};
}
#endif
