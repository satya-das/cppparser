// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef EB6246DE_3216_42BA_AF41_B260CA71C4EE
#define EB6246DE_3216_42BA_AF41_B260CA71C4EE

// TODO: This file needs to be at least conformed to new coding style
//       - Setup clang-tidy to achieve it.

#include "cppast/cpp_compound.h"

namespace cppast {

inline bool isNamespace(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::NAMESPACE;
}
inline bool isClass(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::CLASS;
}
inline bool isStruct(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::STRUCT;
}
inline bool isUnion(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::UNION;
}
inline bool isCppFile(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::FILE;
}
inline bool isBlock(const CppCompound& compound)
{
  return compound.compoundType() == CppCompoundType::BLOCK;
}

} // namespace cppast

#endif /* EB6246DE_3216_42BA_AF41_B260CA71C4EE */
