/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "cppast.h"
#include "cppconst.h"
#include "cpputil.h"

#include "cppobj-accessor.h"

#include <functional>

inline bool forEachMember(CppConstCompoundEPtr compound, std::function<bool(const CppObj*)> visitor)
{
  for (const auto& mem : compound->members())
  {
    if (visitor(mem.get()))
      return true;
  }

  return false;
}

inline bool forEachMember(CppConstCompoundEPtr               compound,
                          CppAccessType                      memAccessType,
                          std::function<bool(const CppObj*)> visitor)
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
  return compound->compoundType() == CppCompoundType::kClass;
}
inline bool isStruct(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::kStruct;
}
inline bool isUnion(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::kUnion;
}
inline bool isCppFile(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::kCppFile;
}
inline bool isBlock(CppConstCompoundEPtr compound)
{
  return compound->compoundType() == CppCompoundType::kBlock;
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

inline bool traverse(CppConstCompoundEPtr compound, std::function<bool(const CppObj*)> visitor)
{
  forEachMember(compound, [&](const CppObj* mem) {
    if (isNamespaceLike(mem) && traverse(mem, visitor))
      return true;
    if (visitor(mem))
      return true;

    return false;
  });

  return false;
}

inline bool traversePreorder(CppConstCompoundEPtr compound, std::function<bool(const CppObj*)> visitor)
{
  forEachMember(compound, [&](const CppObj* mem) {
    if (visitor(mem))
      return true;
    if (isNamespaceLike(mem) && traverse(mem, visitor))
      return true;

    return false;
  });

  return false;
}
