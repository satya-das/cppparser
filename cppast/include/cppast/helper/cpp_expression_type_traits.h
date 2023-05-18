// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B3EF45C9_9225_4AC0_9EF4_FC91034918D7
#define B3EF45C9_9225_4AC0_9EF4_FC91034918D7

#include "cppast/cpp_expression.h"
#include "cppast/helper/cpp_entity_type_traits.h"

#include <type_traits>

namespace cppast::helper {

template <typename T, typename = void>
struct IsCppExpression : std::false_type
{
};

template <typename T>
struct IsCppExpression<T, std::enable_if_t<IsCppEntity_v<T> && (T::EntityType() == CppExpression::EntityType())>>
  : std::true_type
{
};

template <typename T>
constexpr bool IsCppExpression_v = IsCppExpression<T>::value;

} // namespace cppast::helper

#endif /* B3EF45C9_9225_4AC0_9EF4_FC91034918D7 */
