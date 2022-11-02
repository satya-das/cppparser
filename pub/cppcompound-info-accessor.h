// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef FDA8B2C2_913F_4B9A_8AC1_FE10F833D979
#define FDA8B2C2_913F_4B9A_8AC1_FE10F833D979

#include "cppast/cppast.h"
#include "cppconst.h"
#include "cpputil.h"

#include "cppobj-info-accessor.h"

#include <functional>

inline bool forEachMember(CppConstCompoundEPtr compound, std::function<bool(const CppEntity*)> visitor)
{
  for (const auto& mem : compound->members())
  {
    if (visitor(mem.get()))
      return true;
  }

  return false;
}

inline bool forEachMember(CppConstCompoundEPtr                  compound,
                          CppAccessType                         memAccessType,
                          std::function<bool(const CppEntity*)> visitor)
{
  for (const auto& mem : compound->members())
  {
    if ((accessType(mem.get()) == memAccessType) && visitor(mem.get()))
      return true;
  }

  return false;
}

inline bool isNamespace(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::kNamespace;
}
inline bool isClass(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::CLASS;
}
inline bool isStruct(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::STRUCT;
}
inline bool isUnion(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::UNION;
}
inline bool isCppFile(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::FILE;
}
inline bool isBlock(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::BLOCK;
}

/// @return full name of compound type.
inline std::string fullName(CppConstCompoundEPtr compound)
{
  if (!isNamespaceLike(compound))
    return "";
  if (compound->owner() && isNamespaceLike(compound->owner()))
    return fullName(compound->owner()) + "::" + compound->name();
  else
    return compound->name();
}

inline bool traverse(CppConstCompoundEPtr compound, std::function<bool(const CppEntity*)> visitor)
{
  forEachMember(compound, [&](const CppEntity* mem) {
    if (isNamespaceLike(mem) && traverse(mem, visitor))
      return true;
    if (visitor(mem))
      return true;

    return false;
  });

  return false;
}

inline bool traversePreorder(CppConstCompoundEPtr compound, std::function<bool(const CppEntity*)> visitor)
{
  forEachMember(compound, [&](const CppEntity* mem) {
    if (visitor(mem))
      return true;
    if (isNamespaceLike(mem) && traverse(mem, visitor))
      return true;

    return false;
  });

  return false;
}

#endif /* FDA8B2C2_913F_4B9A_8AC1_FE10F833D979 */
