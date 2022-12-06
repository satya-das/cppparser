// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef F36C585F_CB39_4CAE_99AD_2901A74B4AE6
#define F36C585F_CB39_4CAE_99AD_2901A74B4AE6

#include "cppast/cpp_entity_type.h"

#include <type_traits>

namespace cppast::helper {

template <typename T, typename = void>
struct IsCppEntity : std::false_type
{
};

template <typename T>
struct IsCppEntity<T, std::enable_if_t<std::is_same_v<decltype(T::EntityType()), ::cppast::CppEntityType>>>
  : std::true_type
{
};

template <typename T>
constexpr bool IsCppEntity_v = IsCppEntity<T>::value;

} // namespace cppast::helper

#endif /* F36C585F_CB39_4CAE_99AD_2901A74B4AE6 */
