/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkEnumOperators_DEFINED
#  define SkEnumOperators_DEFINED
#  include <type_traits>
namespace skstd
{
  template <typename T>
  struct is_bitmask_enum :  std::false_type
  {
  };
  template <typename E>
  typename std::enable_if<skstd::is_bitmask_enum<E>::value, bool>::type Any(E e)
  {
    return static_cast<typename std::underlying_type<E>::type>(e) != 0;
  }
}
template <typename E>
typename std::enable_if<skstd::is_bitmask_enum<E>::value, E>::type operator|(E l, E r)
{
  using U = typename std::underlying_type<E>::type;
  return static_cast<E>(static_cast<U>(l) | static_cast<U>(r));
}
template <typename E>
typename std::enable_if<skstd::is_bitmask_enum<E>::value, E&>::type operator|=(E& l, E r)
{
  return l = l | r;
}
template <typename E>
typename std::enable_if<skstd::is_bitmask_enum<E>::value, E>::type operator&(E l, E r)
{
  using U = typename std::underlying_type<E>::type;
  return static_cast<E>(static_cast<U>(l) & static_cast<U>(r));
}
template <typename E>
typename std::enable_if<skstd::is_bitmask_enum<E>::value, E&>::type operator&=(E& l, E r)
{
  return l = l & r;
}
template <typename E>
typename std::enable_if<skstd::is_bitmask_enum<E>::value, E>::type operator~(E e)
{
  return static_cast<E>(~static_cast<typename std::underlying_type<E>::type>(e));
}
#endif
