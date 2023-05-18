// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef EDF5323C_98B4_4C03_BDCB_5A61C7364DE3
#define EDF5323C_98B4_4C03_BDCB_5A61C7364DE3

#include "cppast/cpp_entity.h"

#include "cppast/helper/cpp_expression_type_traits.h"

#include <type_traits>

namespace cppast::helper {

template <
  typename T,
  std::enable_if_t<std::is_pointer_v<T> && IsCppExpression_v<std::remove_const_t<std::remove_pointer_t<T>>>>* = nullptr>
inline T cpp_expression_cast(cppast::CppExpression* cppExpression)
{
  if (cppExpression == nullptr)
  {
    return nullptr;
  }

  using _TargetCppExpressionClass = std::remove_const_t<std::remove_pointer_t<T>>;
  if (_TargetCppExpressionClass::ExpressionType() != cppExpression->expressionType())
  {
    return static_cast<_TargetCppExpressionClass*>(nullptr);
  }

  return static_cast<_TargetCppExpressionClass*>(cppExpression);
}

template <
  typename T,
  std::enable_if_t<
    std::is_pointer_v<
      T> && std::is_const_v<std::remove_pointer_t<T>> && cppast::helper::IsCppEntity_v<std::remove_const_t<std::remove_pointer_t<T>>>>* =
    nullptr>
auto cpp_expression_cast(const cppast::CppExpression* cppExpression)
{
  return cpp_expression_cast<T>(const_cast<cppast::CppExpression*>(cppExpression));
}

// TODO: Add unit tests to show usage of cpp_expression_cast().

} // namespace cppast::helper

#endif /* EDF5323C_98B4_4C03_BDCB_5A61C7364DE3 */
