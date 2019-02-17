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

/***************************************************************************************/

#pragma once

#include "cppast.h"
#include "cppconst.h"

#include "cppobj-accessor.h"

inline bool isConst(const CppFunctionBase* func)
{
  return (func->attr() & kConst) == kConst;
}
inline bool isVirtual(const CppFunctionBase* func)
{
  return (func->attr() & kVirtual) == kVirtual;
}
inline bool isPureVirtual(const CppFunctionBase* func)
{
  return (func->attr() & kPureVirtual) == kPureVirtual;
}
inline bool isStatic(const CppFunctionBase* func)
{
  return (func->attr() & kStatic) == kStatic;
}
inline bool isInline(const CppFunctionBase* func)
{
  return (func->attr() & kInline) == kInline;
}
inline bool isOverride(const CppFunctionBase* func)
{
  return (func->attr() & kOverride) == kOverride;
}
inline bool isDeleted(const CppFunctionBase* func)
{
  return (func->attr() & kDelete) == kDelete;
}
inline bool isFinal(const CppFunctionBase* func)
{
  return (func->attr() & kFinal) == kFinal;
}

inline bool isMethod(CppConstFunctionEPtr func)
{
  return func->owner() && isClassLike(func->owner());
}
