// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef F6CF90DD_DA23_4671_A270_BA9BB35B3EAE
#define F6CF90DD_DA23_4671_A270_BA9BB35B3EAE

#include "cppast/cpp_entity_info_accessor.h"
#include "cppast/cppast.h"
#include "cppast/cppconst.h"

#include <vector>

namespace cppast {

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

inline std::vector<const CppEntity*> GetAllParams(const CppFuncCtorBase& func)
{
  std::vector<const CppEntity*> result;
  func.visitAllParams([&result](const auto& param) { result.push_back(&param); });

  return result;
}

} // namespace cppast

#endif /* F6CF90DD_DA23_4671_A270_BA9BB35B3EAE */
