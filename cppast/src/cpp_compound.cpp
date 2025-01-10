// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_compound.h"
#include "cppast/cpp_compound_info_accessor.h"
#include "cppast/cpp_function.h"

namespace cppast {

CppCompound::CppCompound(std::string name, CppCompoundType type)
  : CppEntity(EntityType())
  , name_(std::move(name))
  , compoundType_(type)
{
}

CppCompound::CppCompound(CppCompoundType type)
  : CppCompound(std::string(), type)
{
}

bool CppCompound::visitAll(const Visitor<const CppEntity&>& callback) const
{
  for (auto& entity : entities_)
  {
    if (!callback(*entity))
    {
      return false;
    }
  }

  return true;
}

bool CppCompound::visitAll(const Visitor<CppEntity&>& callback)
{
  for (auto& entity : entities_)
  {
    if (!callback(*entity))
    {
      return false;
    }
  }

  return true;
}

} // namespace cppast
