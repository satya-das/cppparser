// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B1A7BAF0_1D5C_4F41_9DF8_07895208C0BC
#define B1A7BAF0_1D5C_4F41_9DF8_07895208C0BC

#include <memory>

template <typename T>
auto Ptr(T* p)
{
  return std::unique_ptr<T>(p);
}

template <typename T, typename = void>
class ToObjHelper
{
  T* p_;

public:
  ToObjHelper(T* p)
    : p_(p)
  {
  }

  T ToObj()
  {
    if (p_ == nullptr)
      throw std::runtime_error("nullptr cannot be converted to an object");

    return std::move(*std::unique_ptr<T>(p_));
  }
};

template <typename T>
class ToObjHelper<T, std::enable_if_t<std::is_default_constructible_v<T>>>
{
  T* p_;

public:
  ToObjHelper(T* p)
    : p_(p)
  {
  }

  T ToObj()
  {
    if (p_ == nullptr)
      return T();
    return std::move(*std::unique_ptr<T>(p_));
  }
};

template <typename T>
auto Obj(T* p)
{
  return ToObjHelper(p).ToObj();
}

#endif /* B1A7BAF0_1D5C_4F41_9DF8_07895208C0BC */
