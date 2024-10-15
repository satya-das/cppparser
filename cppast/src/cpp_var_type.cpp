// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_var_type.h"
#include "cppast/cpp_compound.h"

namespace cppast {

CppVarType::CppVarType(std::string baseType, CppTypeModifier modifier)
  : CppVarType(std::move(baseType), 0, modifier)
{
}

CppVarType::CppVarType(CppCompound* compound, CppTypeModifier modifier)
  : CppEntity(EntityType())
  , compound_(compound)
  , typeModifier_(modifier)
{
}

CppVarType::CppVarType(CppFunctionPointer* compound, CppTypeModifier modifier)
  : CppEntity(EntityType())
  , compound_(compound)
  , typeModifier_(modifier)
{
}

CppVarType::CppVarType(CppEnum* enumObj, CppTypeModifier modifier)
  : CppEntity(EntityType())
  , compound_(enumObj)
  , typeModifier_(modifier)
{
}

CppVarType::CppVarType(const CppVarType& varType)
  : CppVarType(varType.baseType(), varType.typeModifier())
{
  // TODO: clone compound_.
}

CppVarType::CppVarType(std::string baseType, std::uint32_t typeAttr, CppTypeModifier modifier)
  : CppEntity(EntityType())
  , baseType_(std::move(baseType))
  , typeModifier_(modifier)
  , typeAttr_(typeAttr)
{
}

} // namespace cppast
