// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef EB6246DE_3216_42BA_AF41_B260CA71C4EE
#define EB6246DE_3216_42BA_AF41_B260CA71C4EE

#include "cppast/cpp_compound.h"

namespace cppast {

inline bool IsNamespace(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::NAMESPACE;
}
inline bool IsClass(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::CLASS;
}
inline bool IsStruct(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::STRUCT;
}
inline bool IsUnion(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::UNION;
}
inline bool IsCppFile(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::FILE;
}
inline bool IsBlock(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::BLOCK;
}

} // namespace cppast

#endif /* EB6246DE_3216_42BA_AF41_B260CA71C4EE */
