// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef EB6246DE_3216_42BA_AF41_B260CA71C4EE
#define EB6246DE_3216_42BA_AF41_B260CA71C4EE

// TODO: This file needs to be at least conformed to new coding style
// TODO: Clean up.
// TODO: Merge with cpp_compound_utility.h

#include "cppast/cpp_compound.h"
#include "cppast/cpp_entity_info_accessor.h"
#include "cppast/cppconst.h"

#include <functional>

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

/// @return full name of compound type.
inline std::string fullName(const CppCompound& compound)
{
  if (!isNamespaceLike(compound))
    return "";
  if (compound.owner() && isNamespaceLike(*compound.owner()))
    return fullName(*compound.owner()) + "::" + compound.name();
  else
    return compound.name();
}

// inline bool traverse(const CppCompound& compound, std::function<bool(const CppEntity&)> visitor)
// {
//   forEachMember(compound, [&](const CppEntity& mem) {
//     if (isNamespaceLike(mem) && traverse(mem, visitor))
//       return true;
//     if (visitor(mem))
//       return true;

//     return false;
//   });

//   return false;
// }

// inline bool traversePreorder(const CppCompound& compound, std::function<bool(const CppEntity*)> visitor)
// {
//   forEachMember(compound, [&](const CppEntity* mem) {
//     if (visitor(mem))
//       return true;
//     if (isNamespaceLike(mem) && traverse(mem, visitor))
//       return true;

//     return false;
//   });

//   return false;
// }

} // namespace cppast

#endif /* EB6246DE_3216_42BA_AF41_B260CA71C4EE */
