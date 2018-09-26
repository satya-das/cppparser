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

#include "cppconst.h"

/**
 * Can be used to find default inheritance type of a compound object.
 * @param type Type of compound object.
 * @return Default inheritance type of class/struct/union if not explicitly specified.
 */
inline CppObjProtLevel defaultInheritanceType(CppCompoundType type)
{
  return type == kClass ? kPrivate : kPublic;
}

inline CppObjProtLevel resolveInheritanceType(CppObjProtLevel inheritanceType, CppCompoundType type)
{
  if (inheritanceType != kUnknownProt)
    return inheritanceType;
  return defaultInheritanceType(type);
}

/**
 * Can be used to find default protection level of a compound object.
 * @param type Type of compound object.
 * @return Default protection level of member of a class/struct/union if not explicitly specified.
 */
inline CppObjProtLevel defaultMemberProtLevel(CppCompoundType type)
{
  return type == kClass ? kPrivate : kPublic;
}
