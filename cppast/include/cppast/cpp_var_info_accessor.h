// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef CDAA666A_2ABB_4001_A29C_52422A76A808
#define CDAA666A_2ABB_4001_A29C_52422A76A808

#include "cppast/cppast.h"
#include "cppast/cppconst.h"

#include <cstring>

namespace cppast {

inline std::uint8_t ptrLevel(const CppVarType& varType)
{
  return varType.typeModifier().ptrLevel_;
}

inline std::uint8_t ptrLevel(const std::unique_ptr<CppVarType>& varType)
{
  return ptrLevel(*varType);
}

inline CppRefType refType(const CppVarType& varType)
{
  return varType.typeModifier().refType_;
}

inline CppRefType refType(const std::unique_ptr<CppVarType>& varType)
{
  return refType(*varType);
}

inline std::uint8_t effectivePtrLevel(const CppVarType& varType)
{
  return ptrLevel(varType) + [&varType]() {
    switch (refType(varType))
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

inline const std::string& baseType(const CppVarType& varType)
{
  return varType.baseType();
}

inline const std::string& baseType(const std::unique_ptr<CppVarType>& varType)
{
  return baseType(*varType);
}

inline bool usesTemplateType(const std::string& varTypeName)
{
  return varTypeName.find('<') != varTypeName.npos;
}

inline bool isVoid(const CppVarType& varType)
{
  if (varType.typeModifier().ptrLevel_ != 0 || varType.typeModifier().refType_ != CppRefType::NO_REF)
    return false;
  // return (varType.baseType().compare("void") == 0);
  // Above simple check fails to detect cases like usage of GrGLvoid
  if (varType.baseType().length() < 4)
    return false;
  return (std::strncmp(varType.baseType().c_str() + varType.baseType().length() - 4, "void", 4) == 0);
}

inline bool isVoid(const std::unique_ptr<CppVarType>& varType)
{
  return isVoid(*varType);
}

inline bool isByRef(const CppVarType& varType)
{
  return varType.typeModifier().refType_ == CppRefType::BY_REF;
}

inline bool isByRef(const std::unique_ptr<CppVarType>& varType)
{
  return isByRef(*varType);
}

inline bool isByRValueRef(const CppVarType& varType)
{
  return varType.typeModifier().refType_ == CppRefType::RVAL_REF;
}

inline bool isByRValueRef(const std::unique_ptr<CppVarType>& varType)
{
  return isByRValueRef(*varType);
}

inline bool isConst(const CppVarType& varType)
{
  return ((varType.typeAttr() & CONST) == CONST) || (varType.typeModifier().constBits_ & 1);
}

inline bool isConst(const std::unique_ptr<CppVarType>& varType)
{
  return isConst(*varType);
}

inline bool isByValue(const CppVarType& varType)
{
  return !isVoid(varType) && (varType.typeModifier().refType_ == CppRefType::NO_REF)
         && (varType.typeModifier().ptrLevel_ == 0);
}

inline bool isByValue(const std::unique_ptr<CppVarType>& varType)
{
  return isByValue(*varType);
}

inline const std::string& baseType(const CppVar& var)
{
  return baseType(var.varType());
}

inline const std::string& baseType(const std::unique_ptr<CppVar>& var)
{
  return baseType(*var);
}

inline std::uint8_t ptrLevel(const CppVar& var)
{
  return ptrLevel(var.varType());
}

inline std::uint8_t ptrLevel(const std::unique_ptr<CppVar>& var)
{
  return ptrLevel(*var);
}

inline CppRefType refType(const CppVar& var)
{
  return refType(var.varType());
}

inline CppRefType refType(const std::unique_ptr<CppVar>& var)
{
  return refType(*var);
}

inline const std::string& name(const CppVar& var)
{
  return var.varDecl().name();
}

inline const std::string& name(const std::unique_ptr<CppVar>& var)
{
  return name(*var);
}

inline bool isByRef(const CppVar& var)
{
  return isByRef(var.varType());
}

inline bool isByRef(const std::unique_ptr<CppVar>& var)
{
  return isByRef(*var);
}

inline bool isByRValueRef(const CppVar& var)
{
  return isByRValueRef(var.varType());
}

inline bool isByRValueRef(const std::unique_ptr<CppVar>& var)
{
  return isByRValueRef(*var);
}

inline bool isConst(const CppVar& var)
{
  return isConst(var.varType());
}

inline bool isConst(const std::unique_ptr<CppVar>& var)
{
  return isConst(*var);
}

inline bool isByValue(const CppVar& var)
{
  return isByValue(var.varType());
}

inline bool isByValue(const std::unique_ptr<CppVar>& var)
{
  return isByValue(*var);
}

} // namespace cppast

#endif /* CDAA666A_2ABB_4001_A29C_52422A76A808 */
