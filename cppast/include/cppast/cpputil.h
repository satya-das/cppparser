// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C1DD4A12_AE7D_412D_BB5C_D180EAABE992
#define C1DD4A12_AE7D_412D_BB5C_D180EAABE992

// TODO: Do we need this file?

#include "cppast/cppconst.h"

#include <optional>

namespace cppast {

inline CppAccessType DefaultAccessType(CppCompoundType type)
{
  return (type == CppCompoundType::CLASS) ? CppAccessType::PRIVATE : CppAccessType::PUBLIC;
}

inline CppAccessType ResolveInheritanceType(const std::optional<CppAccessType>& inheritanceType, CppCompoundType type)
{
  return (inheritanceType.has_value()) ? inheritanceType.value() : DefaultAccessType(type);
}

} // namespace cppast

#endif /* C1DD4A12_AE7D_412D_BB5C_D180EAABE992 */
