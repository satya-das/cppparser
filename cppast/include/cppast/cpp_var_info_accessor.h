// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef CDAA666A_2ABB_4001_A29C_52422A76A808
#define CDAA666A_2ABB_4001_A29C_52422A76A808

#include "cppast/cppast.h"
#include "cppast/cppconst.h"

#include <cstring>

namespace cppast {

inline std::uint8_t PtrLevel(const CppVarType& varType)
{
  return varType.typeModifier().ptrLevel_;
}

inline std::uint8_t PtrLevel(const std::unique_ptr<CppVarType>& varType)
{
  return PtrLevel(*varType);
}

inline CppRefType RefType(const CppVarType& varType)
{
  return varType.typeModifier().refType_;
}

inline CppRefType RefType(const std::unique_ptr<CppVarType>& varType)
{
  return RefType(*varType);
}

inline std::uint8_t EffectivePtrLevel(const CppVarType& varType)
{
  return PtrLevel(varType) + [&varType]() {
    switch (RefType(varType))
    {
      case CppRefType::BY_REF:
      case CppRefType::RVAL_REF:
        return 1;
      case CppRefType::NO_REF:
        break;
    }
    return 0;
  }();
}

inline const std::string& BaseType(const CppVarType& varType)
{
  return varType.baseType();
}

inline const std::string& BaseType(const std::unique_ptr<CppVarType>& varType)
{
  return BaseType(*varType);
}

inline bool UsesTemplateType(const std::string& varTypeName)
{
  return varTypeName.find('<') != varTypeName.npos;
}

inline bool IsVoid(const CppVarType& varType)
{
  if (varType.typeModifier().ptrLevel_ != 0 || varType.typeModifier().refType_ != CppRefType::NO_REF)
    return false;
  // return (varType.BaseType().compare("void") == 0);
  // Above simple check fails to detect cases like usage of GrGLvoid
  if (varType.baseType().length() < 4)
    return false;
  return (std::strncmp(varType.baseType().c_str() + varType.baseType().length() - 4, "void", 4) == 0);
}

inline bool IsVoid(const std::unique_ptr<CppVarType>& varType)
{
  return IsVoid(*varType);
}

inline bool IsByRef(const CppVarType& varType)
{
  return varType.typeModifier().refType_ == CppRefType::BY_REF;
}

inline bool IsByRef(const std::unique_ptr<CppVarType>& varType)
{
  return IsByRef(*varType);
}

inline bool IsByRValueRef(const CppVarType& varType)
{
  return varType.typeModifier().refType_ == CppRefType::RVAL_REF;
}

inline bool IsByRValueRef(const std::unique_ptr<CppVarType>& varType)
{
  return IsByRValueRef(*varType);
}

inline bool IsConst(const CppVarType& varType)
{
  return ((varType.typeAttr() & CONST) == CONST) || (varType.typeModifier().constBits_ & 1);
}

inline bool IsConst(const std::unique_ptr<CppVarType>& varType)
{
  return IsConst(*varType);
}

inline bool IsByValue(const CppVarType& varType)
{
  return !IsVoid(varType) && (varType.typeModifier().refType_ == CppRefType::NO_REF)
         && (varType.typeModifier().ptrLevel_ == 0);
}

inline bool IsByValue(const std::unique_ptr<CppVarType>& varType)
{
  return IsByValue(*varType);
}

inline const std::string& BaseType(const CppVar& var)
{
  return BaseType(var.varType());
}

inline const std::string& BaseType(const std::unique_ptr<CppVar>& var)
{
  return BaseType(*var);
}

inline std::uint8_t PtrLevel(const CppVar& var)
{
  return PtrLevel(var.varType());
}

inline std::uint8_t PtrLevel(const std::unique_ptr<CppVar>& var)
{
  return PtrLevel(*var);
}

inline CppRefType RefType(const CppVar& var)
{
  return RefType(var.varType());
}

inline CppRefType RefType(const std::unique_ptr<CppVar>& var)
{
  return RefType(*var);
}

inline const std::string& Name(const CppVar& var)
{
  return var.varDecl().name();
}

inline const std::string& Name(const std::unique_ptr<CppVar>& var)
{
  return Name(*var);
}

inline bool IsByRef(const CppVar& var)
{
  return IsByRef(var.varType());
}

inline bool IsByRef(const std::unique_ptr<CppVar>& var)
{
  return IsByRef(*var);
}

inline bool IsByRValueRef(const CppVar& var)
{
  return IsByRValueRef(var.varType());
}

inline bool IsByRValueRef(const std::unique_ptr<CppVar>& var)
{
  return IsByRValueRef(*var);
}

inline bool IsConst(const CppVar& var)
{
  return IsConst(var.varType());
}

inline bool IsConst(const std::unique_ptr<CppVar>& var)
{
  return IsConst(*var);
}

inline bool IsByValue(const CppVar& var)
{
  return IsByValue(var.varType());
}

inline bool IsByValue(const std::unique_ptr<CppVar>& var)
{
  return IsByValue(*var);
}

} // namespace cppast

#endif /* CDAA666A_2ABB_4001_A29C_52422A76A808 */
