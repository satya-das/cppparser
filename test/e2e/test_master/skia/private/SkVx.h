/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SKVX_DEFINED
#  define SKVX_DEFINED
#  include <algorithm>
#  include <cmath>
#  include <cstdint>
#  include <cstring>
#  include <initializer_list>
#  if  defined(__SSE__)
#    include <immintrin.h>
#  elif  defined(__ARM_NEON)
#    include <arm_neon.h>
#  endif
#  if  !defined(__clang__) && defined(__GNUC__) && defined(__mips64)
#    define SKVX_ALIGNMENT
#  elif  !defined(__clang__) && defined(_MSC_VER) && defined(_M_IX86)
#    define SKVX_ALIGNMENT
#  else 
#    define SKVX_ALIGNMENT	alignas(N * sizeof(T))
#  endif
namespace skvx
{
  template <int N, typename T>
  struct SKVX_ALIGNMENT Vec
  {
    static_assert((N & (N - 1)) == 0, "N must be a power of 2.");
    static_assert(sizeof(T) >= alignof(T), "What kind of crazy T is this?");
    Vec<N/2,T> lo, hi;
    Vec();
    template <typename U, typename  = typename std::enable_if<std::is_convertible<U,T>::value>::type>
    Vec(U x)
      : lo(x)
      , hi(x)
    {
    }
    Vec(std::initializer_list<T> xs)
    {
      T vals[N] = {0};
      memcpy(vals, xs.begin(), std::min(xs.size(), (size_t) N) * sizeof(T));
      lo = Vec<N/2,T>::Load(vals + 0);
      hi = Vec<N/2,T>::Load(vals + N / 2);
    }
    T operator[](int i) const
    {
      return i < N / 2 ? lo[i] : hi[i - N / 2];
    }
    T& operator[](int i)
    {
      return i < N / 2 ? lo[i] : hi[i - N / 2];
    }
    static Vec Load(const void* ptr)
    {
      Vec v;
      memcpy(&v, ptr, sizeof(Vec));
      return v;
    }
    void store(void* ptr) const
    {
      memcpy(ptr, this, sizeof(Vec));
    }
  };
  template <typename T>
  struct Vec<1,T>
  {
    T val;
    Vec();
    template <typename U, typename  = typename std::enable_if<std::is_convertible<U,T>::value>::type>
    Vec(U x)
      : val(x)
    {
    }
    Vec(std::initializer_list<T> xs)
      : val(xs.size() ? *xs.begin() : 0)
    {
    }
    T operator[](int) const
    {
      return val;
    }
    T& operator[](int)
    {
      return val;
    }
    static Vec Load(const void* ptr)
    {
      Vec v;
      memcpy(&v, ptr, sizeof(Vec));
      return v;
    }
    void store(void* ptr) const
    {
      memcpy(ptr, this, sizeof(Vec));
    }
  };
#  if  defined(__GNUC__) && !defined(__clang__) && defined(__SSE__)
#    pragma  GCC diagnostic ignored "-Wpsabi"
#  endif
#  define SIT	template <       typename T> static inline
#  define SINT	template <int N, typename T> static inline
#  define SINTU	template <int N, typename T, typename U, \
                        typename=typename std::enable_if<std::is_convertible<U,T>::value>::type> \
              static inline
  template <typename D, typename S>
  static D bit_pun(const S& s)
  {
    static_assert(sizeof(D) == sizeof(S), "");
    D d;
    memcpy(&d, &s, sizeof(D));
    return d;
  }
  template <typename T>
  struct Mask
  {
    using type = T;
  };
  template <>
  struct Mask<float >
  {
    using type = int32_t;
  };
  template <>
  struct Mask<double>
  {
    using type = int64_t;
  };
  template <typename T>
  using M = typename Mask<T>::type;
  SINT Vec<2*N,T> join(const Vec<N,T>& lo, const Vec<N,T>& hi)
  {
    Vec<2*N,T> v;
    v.lo = lo;
    v.hi = hi;
    return v;
  }
#  if  !defined(SKNX_NO_SIMD) && (defined(__clang__) || defined(__GNUC__))
#    if  defined(__clang__)
  template <int N, typename T>
  using VExt = T;
#    elif  defined(__GNUC__)
  template <int N, typename T>
  struct VExtHelper
  {
    typedef T type;
  };
  template <int N, typename T>
  using VExt = typename VExtHelper<N,T>::type;
  static Vec<4,float> to_vec(VExt<4,float> v)
  {
    return bit_pun<Vec<4,float>>(v);
  }
#    endif
  SINT VExt<N,T> to_vext(const Vec<N,T>& v)
  {
    return bit_pun<VExt<N,T>>(v);
  }
  SINT Vec <N,T> to_vec(const VExt<N,T>& v)
  {
    return bit_pun<Vec <N,T>>(v);
  }
  SINT Vec<N,T> operator+(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return to_vec<N,T>(to_vext(x) + to_vext(y));
  }
  SINT Vec<N,T> operator-(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return to_vec<N,T>(to_vext(x) - to_vext(y));
  }
  SINT Vec<N,T> operator*(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return to_vec<N,T>(to_vext(x) * to_vext(y));
  }
  SINT Vec<N,T> operator/(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return to_vec<N,T>(to_vext(x) / to_vext(y));
  }
  SINT Vec<N,T> operator^(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return to_vec<N,T>(to_vext(x) ^ to_vext(y));
  }
  SINT Vec<N,T> operator&(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return to_vec<N,T>(to_vext(x) & to_vext(y));
  }
  SINT Vec<N,T> operator|(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return to_vec<N,T>(to_vext(x) | to_vext(y));
  }
  SINT Vec<N,T> operator!(const Vec<N,T>& x)
  {
    return to_vec<N,T>(!to_vext(x));
  }
  SINT Vec<N,T> operator-(const Vec<N,T>& x)
  {
    return to_vec<N,T>(-to_vext(x));
  }
  SINT Vec<N,T> operator~(const Vec<N,T>& x)
  {
    return to_vec<N,T>(~to_vext(x));
  }
  SINT Vec<N,T> operator<<(const Vec<N,T>& x, int bits)
  {
    return to_vec<N,T>(to_vext(x) << bits);
  }
  SINT Vec<N,T> operator>>(const Vec<N,T>& x, int bits)
  {
    return to_vec<N,T>(to_vext(x) >> bits);
  }
  SINT Vec<N,M<T>> operator==(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return bit_pun<Vec<N,M<T>>>(to_vext(x) == to_vext(y));
  }
  SINT Vec<N,M<T>> operator!=(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return bit_pun<Vec<N,M<T>>>(to_vext(x) != to_vext(y));
  }
  SINT Vec<N,M<T>> operator<=(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return bit_pun<Vec<N,M<T>>>(to_vext(x) <= to_vext(y));
  }
  SINT Vec<N,M<T>> operator>=(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return bit_pun<Vec<N,M<T>>>(to_vext(x) >= to_vext(y));
  }
  SINT Vec<N,M<T>> operator<(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return bit_pun<Vec<N,M<T>>>(to_vext(x) < to_vext(y));
  }
  SINT Vec<N,M<T>> operator>(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return bit_pun<Vec<N,M<T>>>(to_vext(x) > to_vext(y));
  }
#  else 
  SIT Vec<1,T> operator+(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val + y.val;
  }
  SIT Vec<1,T> operator-(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val - y.val;
  }
  SIT Vec<1,T> operator*(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val * y.val;
  }
  SIT Vec<1,T> operator/(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val / y.val;
  }
  SIT Vec<1,T> operator^(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val ^ y.val;
  }
  SIT Vec<1,T> operator&(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val & y.val;
  }
  SIT Vec<1,T> operator|(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val | y.val;
  }
  SIT Vec<1,T> operator!(const Vec<1,T>& x)
  {
    return !x.val;
  }
  SIT Vec<1,T> operator-(const Vec<1,T>& x)
  {
    return -x.val;
  }
  SIT Vec<1,T> operator~(const Vec<1,T>& x)
  {
    return ~x.val;
  }
  SIT Vec<1,T> operator<<(const Vec<1,T>& x, int bits)
  {
    return x.val << bits;
  }
  SIT Vec<1,T> operator>>(const Vec<1,T>& x, int bits)
  {
    return x.val >> bits;
  }
  SIT Vec<1,M<T>> operator==(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val == y.val ? ~0 : 0;
  }
  SIT Vec<1,M<T>> operator!=(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val != y.val ? ~0 : 0;
  }
  SIT Vec<1,M<T>> operator<=(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val <= y.val ? ~0 : 0;
  }
  SIT Vec<1,M<T>> operator>=(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val >= y.val ? ~0 : 0;
  }
  SIT Vec<1,M<T>> operator<(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val < y.val ? ~0 : 0;
  }
  SIT Vec<1,M<T>> operator>(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return x.val > y.val ? ~0 : 0;
  }
  SINT Vec<N,T> operator+(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo + y.lo, x.hi + y.hi);
  }
  SINT Vec<N,T> operator-(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo - y.lo, x.hi - y.hi);
  }
  SINT Vec<N,T> operator*(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo * y.lo, x.hi * y.hi);
  }
  SINT Vec<N,T> operator/(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo / y.lo, x.hi / y.hi);
  }
  SINT Vec<N,T> operator^(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo ^ y.lo, x.hi ^ y.hi);
  }
  SINT Vec<N,T> operator&(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo & y.lo, x.hi & y.hi);
  }
  SINT Vec<N,T> operator|(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo | y.lo, x.hi | y.hi);
  }
  SINT Vec<N,T> operator!(const Vec<N,T>& x)
  {
    return join(!x.lo, !x.hi);
  }
  SINT Vec<N,T> operator-(const Vec<N,T>& x)
  {
    return join(-x.lo, -x.hi);
  }
  SINT Vec<N,T> operator~(const Vec<N,T>& x)
  {
    return join(~x.lo, ~x.hi);
  }
  SINT Vec<N,T> operator<<(const Vec<N,T>& x, int bits)
  {
    return join(x.lo << bits, x.hi << bits);
  }
  SINT Vec<N,T> operator>>(const Vec<N,T>& x, int bits)
  {
    return join(x.lo >> bits, x.hi >> bits);
  }
  SINT Vec<N,M<T>> operator==(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo == y.lo, x.hi == y.hi);
  }
  SINT Vec<N,M<T>> operator!=(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo != y.lo, x.hi != y.hi);
  }
  SINT Vec<N,M<T>> operator<=(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo <= y.lo, x.hi <= y.hi);
  }
  SINT Vec<N,M<T>> operator>=(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo >= y.lo, x.hi >= y.hi);
  }
  SINT Vec<N,M<T>> operator<(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo < y.lo, x.hi < y.hi);
  }
  SINT Vec<N,M<T>> operator>(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(x.lo > y.lo, x.hi > y.hi);
  }
#  endif
  SIT Vec<1,T> if_then_else(const Vec<1,M<T>>& cond, const Vec<1,T>& t, const Vec<1,T>& e)
  {
    auto t_bits, e_bits;
    return bit_pun<T>((cond.val & t_bits) | (~cond.val & e_bits));
  }
  SIT bool any(const Vec<1,T>& x)
  {
    return x.val != 0;
  }
  SIT bool all(const Vec<1,T>& x)
  {
    return x.val != 0;
  }
  SIT T min(const Vec<1,T>& x)
  {
    return x.val;
  }
  SIT T max(const Vec<1,T>& x)
  {
    return x.val;
  }
  SIT Vec<1,T> min(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return std::min(x.val, y.val);
  }
  SIT Vec<1,T> max(const Vec<1,T>& x, const Vec<1,T>& y)
  {
    return std::max(x.val, y.val);
  }
  SIT Vec<1,T> ceil(const Vec<1,T>& x)
  {
    return std:: ceil(x.val);
  }
  SIT Vec<1,T> floor(const Vec<1,T>& x)
  {
    return std::floor(x.val);
  }
  SIT Vec<1,T> trunc(const Vec<1,T>& x)
  {
    return std::trunc(x.val);
  }
  SIT Vec<1,T> round(const Vec<1,T>& x)
  {
    return std::round(x.val);
  }
  SIT Vec<1,T> sqrt(const Vec<1,T>& x)
  {
    return std:: sqrt(x.val);
  }
  SIT Vec<1,T> abs(const Vec<1,T>& x)
  {
    return std::  abs(x.val);
  }
  SIT Vec<1,T> rcp(const Vec<1,T>& x)
  {
    return 1 / x.val;
  }
  SIT Vec<1,T> rsqrt(const Vec<1,T>& x)
  {
    return rcp(sqrt(x));
  }
  SIT Vec<1,T> mad(const Vec<1,T>& f, const Vec<1,T>& m, const Vec<1,T>& a)
  {
    return f * m + a;
  }
  SINT Vec<N,T> if_then_else(const Vec<N,M<T>>& cond, const Vec<N,T>& t, const Vec<N,T>& e)
  {
    return join(if_then_else(cond.lo, t.lo, e.lo), if_then_else(cond.hi, t.hi, e.hi));
  }
  SINT bool any(const Vec<N,T>& x)
  {
    return any(x.lo) || any(x.hi);
  }
  SINT bool all(const Vec<N,T>& x)
  {
    return all(x.lo) && all(x.hi);
  }
  SINT T min(const Vec<N,T>& x)
  {
    return std::min(min(x.lo), min(x.hi));
  }
  SINT T max(const Vec<N,T>& x)
  {
    return std::max(max(x.lo), max(x.hi));
  }
  SINT Vec<N,T> min(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(min(x.lo, y.lo), min(x.hi, y.hi));
  }
  SINT Vec<N,T> max(const Vec<N,T>& x, const Vec<N,T>& y)
  {
    return join(max(x.lo, y.lo), max(x.hi, y.hi));
  }
  SINT Vec<N,T> ceil(const Vec<N,T>& x)
  {
    return join(ceil(x.lo), ceil(x.hi));
  }
  SINT Vec<N,T> floor(const Vec<N,T>& x)
  {
    return join(floor(x.lo), floor(x.hi));
  }
  SINT Vec<N,T> trunc(const Vec<N,T>& x)
  {
    return join(trunc(x.lo), trunc(x.hi));
  }
  SINT Vec<N,T> round(const Vec<N,T>& x)
  {
    return join(round(x.lo), round(x.hi));
  }
  SINT Vec<N,T> sqrt(const Vec<N,T>& x)
  {
    return join(sqrt(x.lo), sqrt(x.hi));
  }
  SINT Vec<N,T> abs(const Vec<N,T>& x)
  {
    return join(abs(x.lo), abs(x.hi));
  }
  SINT Vec<N,T> rcp(const Vec<N,T>& x)
  {
    return join(rcp(x.lo), rcp(x.hi));
  }
  SINT Vec<N,T> rsqrt(const Vec<N,T>& x)
  {
    return join(rsqrt(x.lo), rsqrt(x.hi));
  }
  SINT Vec<N,T> mad(const Vec<N,T>& f, const Vec<N,T>& m, const Vec<N,T>& a)
  {
    return join(mad(f.lo, m.lo, a.lo), mad(f.hi, m.hi, a.hi));
  }
  SINTU Vec<N,T> operator+(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) + y;
  }
  SINTU Vec<N,T> operator-(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) - y;
  }
  SINTU Vec<N,T> operator*(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) * y;
  }
  SINTU Vec<N,T> operator/(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) / y;
  }
  SINTU Vec<N,T> operator^(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) ^ y;
  }
  SINTU Vec<N,T> operator&(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) & y;
  }
  SINTU Vec<N,T> operator|(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) | y;
  }
  SINTU Vec<N,M<T>> operator==(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) == y;
  }
  SINTU Vec<N,M<T>> operator!=(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) != y;
  }
  SINTU Vec<N,M<T>> operator<=(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) <= y;
  }
  SINTU Vec<N,M<T>> operator>=(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) >= y;
  }
  SINTU Vec<N,M<T>> operator<(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) < y;
  }
  SINTU Vec<N,M<T>> operator>(U x, const Vec<N,T>& y)
  {
    return Vec<N,T>(x) > y;
  }
  SINTU Vec<N,T> min(U x, const Vec<N,T>& y)
  {
    return min(Vec<N,T>(x), y);
  }
  SINTU Vec<N,T> max(U x, const Vec<N,T>& y)
  {
    return max(Vec<N,T>(x), y);
  }
  SINTU Vec<N,T> operator+(const Vec<N,T>& x, U y)
  {
    return x + Vec<N,T>(y);
  }
  SINTU Vec<N,T> operator-(const Vec<N,T>& x, U y)
  {
    return x - Vec<N,T>(y);
  }
  SINTU Vec<N,T> operator*(const Vec<N,T>& x, U y)
  {
    return x * Vec<N,T>(y);
  }
  SINTU Vec<N,T> operator/(const Vec<N,T>& x, U y)
  {
    return x / Vec<N,T>(y);
  }
  SINTU Vec<N,T> operator^(const Vec<N,T>& x, U y)
  {
    return x ^ Vec<N,T>(y);
  }
  SINTU Vec<N,T> operator&(const Vec<N,T>& x, U y)
  {
    return x & Vec<N,T>(y);
  }
  SINTU Vec<N,T> operator|(const Vec<N,T>& x, U y)
  {
    return x | Vec<N,T>(y);
  }
  SINTU Vec<N,M<T>> operator==(const Vec<N,T>& x, U y)
  {
    return x == Vec<N,T>(y);
  }
  SINTU Vec<N,M<T>> operator!=(const Vec<N,T>& x, U y)
  {
    return x != Vec<N,T>(y);
  }
  SINTU Vec<N,M<T>> operator<=(const Vec<N,T>& x, U y)
  {
    return x <= Vec<N,T>(y);
  }
  SINTU Vec<N,M<T>> operator>=(const Vec<N,T>& x, U y)
  {
    return x >= Vec<N,T>(y);
  }
  SINTU Vec<N,M<T>> operator<(const Vec<N,T>& x, U y)
  {
    return x <  Vec<N,T>(y);
  }
  SINTU Vec<N,M<T>> operator>(const Vec<N,T>& x, U y)
  {
    return x > Vec<N,T>(y);
  }
  SINTU Vec<N,T> min(const Vec<N,T>& x, U y)
  {
    return min(x, Vec<N,T>(y));
  }
  SINTU Vec<N,T> max(const Vec<N,T>& x, U y)
  {
    return max(x, Vec<N,T>(y));
  }
  SINTU Vec<N,T> mad(U f, const Vec<N,T>& m, const Vec<N,T>& a)
  {
    return Vec<N,T>(f) * m + a;
  }
  SINTU Vec<N,T> mad(const Vec<N,T>& f, U m, const Vec<N,T>& a)
  {
    return f * Vec<N,T>(m) + a;
  }
  SINTU Vec<N,T> mad(const Vec<N,T>& f, const Vec<N,T>& m, U a)
  {
    return f * m + Vec<N,T>(a);
  }
  SINTU Vec<N,T> mad(const Vec<N,T>& f, U m, U a)
  {
    return f * Vec<N,T>(m) + Vec<N,T>(a);
  }
  SINTU Vec<N,T> mad(U f, const Vec<N,T>& m, U a)
  {
    return Vec<N,T>(f) * m + Vec<N,T>(a);
  }
  SINTU Vec<N,T> mad(U f, U m, const Vec<N,T>& a)
  {
    return Vec<N,T>(f) * Vec<N,T>(m) + a;
  }
  SINT Vec<N,T>& operator+=(Vec<N,T>& x, const Vec<N,T>& y)
  {
    return (x = x + y);
  }
  SINT Vec<N,T>& operator-=(Vec<N,T>& x, const Vec<N,T>& y)
  {
    return (x = x - y);
  }
  SINT Vec<N,T>& operator*=(Vec<N,T>& x, const Vec<N,T>& y)
  {
    return (x = x * y);
  }
  SINT Vec<N,T>& operator/=(Vec<N,T>& x, const Vec<N,T>& y)
  {
    return (x = x / y);
  }
  SINT Vec<N,T>& operator^=(Vec<N,T>& x, const Vec<N,T>& y)
  {
    return (x = x ^ y);
  }
  SINT Vec<N,T>& operator&=(Vec<N,T>& x, const Vec<N,T>& y)
  {
    return (x = x & y);
  }
  SINT Vec<N,T>& operator|=(Vec<N,T>& x, const Vec<N,T>& y)
  {
    return (x = x | y);
  }
  SINTU Vec<N,T>& operator+=(Vec<N,T>& x, U y)
  {
    return (x = x + Vec<N,T>(y));
  }
  SINTU Vec<N,T>& operator-=(Vec<N,T>& x, U y)
  {
    return (x = x - Vec<N,T>(y));
  }
  SINTU Vec<N,T>& operator*=(Vec<N,T>& x, U y)
  {
    return (x = x * Vec<N,T>(y));
  }
  SINTU Vec<N,T>& operator/=(Vec<N,T>& x, U y)
  {
    return (x = x / Vec<N,T>(y));
  }
  SINTU Vec<N,T>& operator^=(Vec<N,T>& x, U y)
  {
    return (x = x ^ Vec<N,T>(y));
  }
  SINTU Vec<N,T>& operator&=(Vec<N,T>& x, U y)
  {
    return (x = x & Vec<N,T>(y));
  }
  SINTU Vec<N,T>& operator|=(Vec<N,T>& x, U y)
  {
    return (x = x | Vec<N,T>(y));
  }
  SINT Vec<N,T>& operator<<=(Vec<N,T>& x, int bits)
  {
    return (x = x << bits);
  }
  SINT Vec<N,T>& operator>>=(Vec<N,T>& x, int bits)
  {
    return (x = x >> bits);
  }
  template <typename D, typename S>
  static Vec<1,D> cast(const Vec<1,S>& src)
  {
    return (D) src.val;
  }
  template <typename D, int N, typename S>
  static Vec<N,D> cast(const Vec<N,S>& src)
  {
#  if  !defined(SKNX_NO_SIMD) && defined(__clang__)
    return to_vec(__builtin_convertvector(to_vext(src), VExt<N,D>));
#  else 
    return join(cast<D>(src.lo), cast<D>(src.hi));
#  endif
  }
  template <int... Ix, int N, typename T>
  static Vec<sizeof...(Ix),T> shuffle(const Vec<N,T>& x)
  {
#  if  !defined(SKNX_NO_SIMD) && defined(__clang__)
    return to_vec<sizeof...(Ix),T>(__builtin_shufflevector(to_vext(x), to_vext(x), Ix...));
#  else 
    return {x[Ix]};
#  endif
  }
  template <int N>
  static Vec<N,uint8_t> div255(const Vec<N,uint16_t>& x)
  {
    return cast<uint8_t>((x + 127) / 255);
  }
  template <int N>
  static Vec<N,uint8_t> approx_scale(const Vec<N,uint8_t>& x, const Vec<N,uint8_t>& y)
  {
    auto X = cast<uint16_t>(x);
    auto Y = cast<uint16_t>(y);
    return cast<uint8_t>((X * Y + X) / 256);
  }
#  if  !defined(SKNX_NO_SIMD) && defined(__ARM_NEON)
  static Vec<8,uint16_t> mull(const Vec<8,uint8_t>& x, const Vec<8,uint8_t>& y)
  {
    return to_vec<8,uint16_t>(vmull_u8(to_vext(x), to_vext(y)));
  }
  template <int N>
  static typename std::enable_if<(N < 8), Vec<N,uint16_t>>::type mull(const Vec<N,uint8_t>& x, const Vec<N,uint8_t>& y)
  {
    return mull(join(x, x), join(y, y)).lo;
  }
  template <int N>
  static typename std::enable_if<(N > 8), Vec<N,uint16_t>>::type mull(const Vec<N,uint8_t>& x, const Vec<N,uint8_t>& y)
  {
    return join(mull(x.lo, y.lo), mull(x.hi, y.hi));
  }
#  else 
  template <int N>
  static Vec<N,uint16_t> mull(const Vec<N,uint8_t>& x, const Vec<N,uint8_t>& y)
  {
    return cast<uint16_t>(x) * cast<uint16_t>(y);
  }
#  endif
#  if  !defined(SKNX_NO_SIMD)
#    if  defined(__SSE__)
  static Vec<4,float> sqrt(const Vec<4,float>& x)
  {
    return bit_pun<Vec<4,float>>(_mm_sqrt_ps(bit_pun<__m128>(x)));
  }
  static Vec<4,float> rsqrt(const Vec<4,float>& x)
  {
    return bit_pun<Vec<4,float>>(_mm_rsqrt_ps(bit_pun<__m128>(x)));
  }
  static Vec<4,float> rcp(const Vec<4,float>& x)
  {
    return bit_pun<Vec<4,float>>(_mm_rcp_ps(bit_pun<__m128>(x)));
  }
  static Vec<2,float> sqrt(const Vec<2,float>& x)
  {
    return shuffle<0,1>(sqrt(shuffle<0,1,0,1>(x)));
  }
  static Vec<2,float> rsqrt(const Vec<2,float>& x)
  {
    return shuffle<0,1>(rsqrt(shuffle<0,1,0,1>(x)));
  }
  static Vec<2,float> rcp(const Vec<2,float>& x)
  {
    return shuffle<0,1>(rcp(shuffle<0,1,0,1>(x)));
  }
#    endif
#    if  defined(__SSE4_1__)
  static Vec<4,float> if_then_else(const Vec<4,int >& c, const Vec<4,float>& t, const Vec<4,float>& e)
  {
    return bit_pun<Vec<4,float>>(_mm_blendv_ps(bit_pun<__m128>(e), bit_pun<__m128>(t), bit_pun<__m128>(c)));
  }
#    elif  defined(__SSE__)
  static Vec<4,float> if_then_else(const Vec<4,int >& c, const Vec<4,float>& t, const Vec<4,float>& e)
  {
    return bit_pun<Vec<4,float>>(_mm_or_ps(_mm_and_ps(bit_pun<__m128>(c), bit_pun<__m128>(t)), _mm_andnot_ps(bit_pun<__m128>(c), bit_pun<__m128>(e))));
  }
#    elif  defined(__ARM_NEON)
  static Vec<4,float> if_then_else(const Vec<4,int >& c, const Vec<4,float>& t, const Vec<4,float>& e)
  {
    return bit_pun<Vec<4,float>>(vbslq_f32(bit_pun<uint32x4_t>(c), bit_pun<float32x4_t>(t), bit_pun<float32x4_t>(e)));
  }
#    endif
#  endif
}
#  undef SINTU
#  undef SINT
#  undef SIT
#  undef SKVX_ALIGNMENT
#endif
