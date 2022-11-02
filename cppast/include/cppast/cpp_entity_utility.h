// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DAF1BDEC_3BAD_4448_87E1_B28609630F6A
#define DAF1BDEC_3BAD_4448_87E1_B28609630F6A

#include "cppast/cpp_entity.h"

#include <type_traits>

template <typename T>
inline T cpp_entity_cast(CppAst::CppEntity* cppEntity)
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

template <typename T>
auto cpp_entity_cast(const CppAst::CppEntity* cppEntity)
{
  return cpp_entity_cast<T>(const_cast<CppAst::CppEntity*>(cppEntity));
}

#endif /* DAF1BDEC_3BAD_4448_87E1_B28609630F6A */
