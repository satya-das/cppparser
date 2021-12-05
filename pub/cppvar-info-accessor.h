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

inline std::uint8_t ptrLevel(const CppVarType* varType)
{
  return varType->typeModifier().ptrLevel_;
}

inline std::uint8_t ptrLevel(const std::unique_ptr<CppVarType>& varType)
{
  return varType->typeModifier().ptrLevel_;
}

inline std::uint8_t ptrLevel(CppVarTypeEPtr varType)
{
  return varType->typeModifier().ptrLevel_;
}

inline std::uint8_t ptrLevel(CppConstVarTypeEPtr varType)
{
  return varType->typeModifier().ptrLevel_;
}

inline CppRefType refType(const CppVarType* varType)
{
  return varType->typeModifier().refType_;
}

inline CppRefType refType(const std::unique_ptr<CppVarType>& varType)
{
  return varType->typeModifier().refType_;
}

inline CppRefType refType(CppVarTypeEPtr varType)
{
  return varType->typeModifier().refType_;
}

inline CppRefType refType(CppConstVarTypeEPtr varType)
{
  return varType->typeModifier().refType_;
}

inline std::uint8_t effectivePtrLevel(const CppConstVarTypeEPtr& varType)
{
  return ptrLevel(varType) + [&varType]() {
    switch (refType(varType))
    {
      case CppRefType::kByRef:
      case CppRefType::kRValRef:
        return 1;
      case CppRefType::kNoRef:
        break;
    }
    return 0;
  }();
}

inline const std::string& baseType(const CppVarType* varType)
{
  return varType->baseType();
}

inline const std::string& baseType(const std::unique_ptr<CppVarType>& varType)
{
  return varType->baseType();
}

inline const std::string& baseType(CppVarTypeEPtr varType)
{
  return varType->baseType();
}

inline const std::string& baseType(CppConstVarTypeEPtr varType)
{
  return varType->baseType();
}

inline bool usesTemplateType(const std::string& varTypeName)
{
  return varTypeName.find('<') != varTypeName.npos;
}

inline bool usesTemplateType(CppConstVarTypeEPtr varType)
{
  return usesTemplateType(baseType(varType));
}

inline bool isVoid(const CppVarType* varType)
{
  if (varType->typeModifier().ptrLevel_ != 0 || varType->typeModifier().refType_ != CppRefType::kNoRef)
    return false;
  // return (varType->baseType().compare("void") == 0);
  // Above simple check fails to detect cases like usage of GrGLvoid
  if (varType->baseType().length() < 4)
    return false;
  return (strncmp(varType->baseType().c_str() + varType->baseType().length() - 4, "void", 4) == 0);
}

inline bool isVoid(const std::unique_ptr<CppVarType>& varType)
{
  return isVoid(varType.get());
}

inline bool isByRef(const CppVarType* varType)
{
  return varType->typeModifier().refType_ == CppRefType::kByRef;
}

inline bool isByRef(const std::unique_ptr<CppVarType>& varType)
{
  return isByRef(varType.get());
}

inline bool isByRef(CppVarTypeEPtr varType)
{
  return varType->typeModifier().refType_ == CppRefType::kByRef;
}

inline bool isByRef(CppConstVarTypeEPtr varType)
{
  return varType->typeModifier().refType_ == CppRefType::kByRef;
}

inline bool isByRValueRef(const CppVarType* varType)
{
  return varType->typeModifier().refType_ == CppRefType::kRValRef;
}

inline bool isByRValueRef(const std::unique_ptr<CppVarType>& varType)
{
  return isByRValueRef(varType.get());
}

inline bool isByRValueRef(CppVarTypeEPtr varType)
{
  return varType->typeModifier().refType_ == CppRefType::kRValRef;
}

inline bool isByRValueRef(CppConstVarTypeEPtr varType)
{
  return varType->typeModifier().refType_ == CppRefType::kRValRef;
}

inline bool isConst(const CppVarType* varType)
{
  return ((varType->typeAttr() & kConst) == kConst) || (varType->typeModifier().constBits_ & 1);
}

inline bool isConst(const std::unique_ptr<CppVarType>& varType)
{
  return isConst(varType.get());
}

inline bool isConst(CppVarTypeEPtr varType)
{
  return ((varType->typeAttr() & kConst) == kConst) || (varType->typeModifier().constBits_ & 1);
}

inline bool isConst(CppConstVarTypeEPtr varType)
{
  return ((varType->typeAttr() & kConst) == kConst) || (varType->typeModifier().constBits_ & 1);
}

inline bool isByValue(const CppVarType* varType)
{
  return !isVoid(varType) && (varType->typeModifier().refType_ == CppRefType::kNoRef)
         && (varType->typeModifier().ptrLevel_ == 0);
}

inline bool isByValue(const std::unique_ptr<CppVarType>& varType)
{
  return isByValue(varType.get());
}

inline bool isByValue(CppVarTypeEPtr varType)
{
  return !isVoid(varType) && (varType->typeModifier().refType_ == CppRefType::kNoRef)
         && (varType->typeModifier().ptrLevel_ == 0);
}

inline bool isByValue(CppConstVarTypeEPtr varType)
{
  return !isVoid(varType) && (varType->typeModifier().refType_ == CppRefType::kNoRef)
         && (varType->typeModifier().ptrLevel_ == 0);
}

inline const std::string& baseType(const CppVar* var)
{
  return baseType(var->varType());
}

inline const std::string& baseType(const std::unique_ptr<CppVar>& var)
{
  return baseType(var->varType());
}

inline const std::string& baseType(CppVarEPtr var)
{
  return baseType(var->varType());
}

inline const std::string& baseType(CppConstVarEPtr var)
{
  return baseType(var->varType());
}

inline std::uint8_t ptrLevel(const CppVar* var)
{
  return ptrLevel(var->varType());
}

inline std::uint8_t ptrLevel(const std::unique_ptr<CppVar>& var)
{
  return ptrLevel(var->varType());
}

inline std::uint8_t ptrLevel(CppVarEPtr var)
{
  return ptrLevel(var->varType());
}

inline std::uint8_t ptrLevel(CppConstVarEPtr var)
{
  return ptrLevel(var->varType());
}

inline CppRefType refType(const CppVar* var)
{
  return refType(var->varType());
}

inline CppRefType refType(const std::unique_ptr<CppVar>& var)
{
  return refType(var->varType());
}

inline CppRefType refType(CppVarEPtr var)
{
  return refType(var->varType());
}

inline CppRefType refType(CppConstVarEPtr var)
{
  return refType(var->varType());
}

inline const std::string& name(const CppVar* var)
{
  return var->varDecl().name();
}

inline const std::string& name(const std::unique_ptr<CppVar>& var)
{
  return name(var.get());
}

inline const std::string& name(CppVarEPtr var)
{
  return var->varDecl().name();
}

inline const std::string& name(CppConstVarEPtr var)
{
  return var->varDecl().name();
}

inline bool isByRef(const CppVar* var)
{
  return isByRef(var->varType());
}

inline bool isByRef(const std::unique_ptr<CppVar>& var)
{
  return isByRef(var->varType());
}

inline bool isByRef(CppVarEPtr var)
{
  return isByRef(var->varType());
}

inline bool isByRef(CppConstVarEPtr var)
{
  return isByRef(var->varType());
}

inline bool isByRValueRef(const CppVar* var)
{
  return isByRValueRef(var->varType());
}

inline bool isByRValueRef(const std::unique_ptr<CppVar>& var)
{
  return isByRValueRef(var->varType());
}

inline bool isByRValueRef(CppVarEPtr var)
{
  return isByRValueRef(var->varType());
}

inline bool isByRValueRef(CppConstVarEPtr var)
{
  return isByRValueRef(var->varType());
}

inline bool isConst(const CppVar* var)
{
  return isConst(var->varType());
}

inline bool isConst(const std::unique_ptr<CppVar>& var)
{
  return isConst(var->varType());
}

inline bool isConst(CppVarEPtr var)
{
  return isConst(var->varType());
}

inline bool isConst(CppConstVarEPtr var)
{
  return isConst(var->varType());
}

inline bool isByValue(const CppVar* var)
{
  return isByValue(var->varType());
}

inline bool isByValue(const std::unique_ptr<CppVar>& var)
{
  return isByValue(var->varType());
}

inline bool isByValue(CppVarEPtr var)
{
  return isByValue(var->varType());
}

inline bool isByValue(CppConstVarEPtr var)
{
  return isByValue(var->varType());
}
