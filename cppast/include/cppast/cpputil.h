// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C1DD4A12_AE7D_412D_BB5C_D180EAABE992
#define C1DD4A12_AE7D_412D_BB5C_D180EAABE992

// TODO: Do we need this file?

#include "cppast/cppast.h"
#include "cppast/cppconst.h"

namespace CppAst {

inline CppAccessType defaultAccessType(CppCompoundType type)
{
  return (type == CppCompoundType::CLASS) ? CppAccessType::PRIVATE : CppAccessType::PUBLIC;
}

inline CppAccessType effectiveAccessType(CppAccessType objAccessType, CppCompoundType ownerType)
{
  return (objAccessType != CppAccessType::UNSPECIFIED) ? objAccessType : defaultAccessType(ownerType);
}

inline CppAccessType resolveInheritanceType(CppAccessType inheritanceType, CppCompoundType type)
{
  return (inheritanceType != CppAccessType::UNSPECIFIED) ? inheritanceType : defaultAccessType(type);
}

} // namespace CppAst

#endif /* C1DD4A12_AE7D_412D_BB5C_D180EAABE992 */
