// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_entity_info_accessor.h"

namespace cppast {

bool isClassLike(const CppEntity& cppEntity)
{
  if (!isCompound(cppEntity))
    return false;
  const auto& compound = static_cast<const CppCompound&>(cppEntity);
  return (compound.compoundType() >= CppCompoundType::CLASS) && (compound.compoundType() <= CppCompoundType::UNION);
}

} // namespace cppast
