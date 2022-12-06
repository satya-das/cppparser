// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DAF1BDEC_3BAD_4448_87E1_B28609630F6A
#define DAF1BDEC_3BAD_4448_87E1_B28609630F6A

#include "cppast/cpp_entity.h"

#include "cppast/helper/cpp_entity_type_traits.h"

#include <type_traits>

namespace cppast::helper {

template <
  typename T,
  std::enable_if_t<std::is_pointer_v<T> && IsCppEntity_v<std::remove_const_t<std::remove_pointer_t<T>>>>* = nullptr>
inline T cpp_entity_cast(cppast::CppEntity* cppEntity)
{
  if (cppEntity == nullptr)
  {
    return nullptr;
  }

  using _TargetCppEntityClass = std::remove_const_t<std::remove_pointer_t<T>>;
  if (_TargetCppEntityClass::EntityType() != cppEntity->entityType())
  {
    return static_cast<_TargetCppEntityClass*>(nullptr);
  }

  return static_cast<_TargetCppEntityClass*>(cppEntity);
}

template <
  typename T,
  std::enable_if_t<
    std::is_pointer_v<
      T> && std::is_const_v<std::remove_pointer_t<T>> && cppast::helper::IsCppEntity_v<std::remove_const_t<std::remove_pointer_t<T>>>>* =
    nullptr>
auto cpp_entity_cast(const cppast::CppEntity* cppEntity)
{
  return cpp_entity_cast<T>(const_cast<cppast::CppEntity*>(cppEntity));
}

// TODO: Add unit tests to show usage of cpp_entity_cast().

} // namespace cppast::helper

#endif /* DAF1BDEC_3BAD_4448_87E1_B28609630F6A */
