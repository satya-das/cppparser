// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

/***************************************************************************************/

#ifndef B62AFC2E_FA06_4E70_8FA6_A27299D11596
#define B62AFC2E_FA06_4E70_8FA6_A27299D11596

#include "cppast/cppast.h"
#include "cppconst.h"

#include "cppobj-info-accessor.h"

inline bool isConst(const CppFunctionBase& func)
{
  return (func.attr() & kConst) == kConst;
}
inline bool isVirtual(const CppFunctionBase& func)
{
  return (func.attr() & (kVirtual | kOverride)) == kVirtual;
}
inline bool isPureVirtual(const CppFunctionBase& func)
{
  return (func.attr() & kPureVirtual) == kPureVirtual;
}
inline bool isStatic(const CppFunctionBase& func)
{
  return (func.attr() & kStatic) == kStatic;
}
inline bool isInline(const CppFunctionBase& func)
{
  return (func.attr() & kInline) == kInline;
}
inline bool isOverride(const CppFunctionBase& func)
{
  return (func.attr() & kOverride) == kOverride;
}
inline bool isDeleted(const CppFunctionBase& func)
{
  return (func.attr() & kDelete) == kDelete;
}
inline bool isFinal(const CppFunctionBase& func)
{
  return (func.attr() & kFinal) == kFinal;
}

inline bool isMethod(CppConstFunctionEPtr func)
{
  return func.owner() && isClassLike(func.owner());
}

#endif /* B62AFC2E_FA06_4E70_8FA6_A27299D11596 */
