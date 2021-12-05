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

inline CppAccessType accessType(const CppObj* cppObj)
{
  if (cppObj->accessType_ != CppAccessType::kUnknown)
    return cppObj->accessType_;
  return (cppObj->owner() == nullptr) ? CppAccessType::kPublic : defaultAccessType(cppObj->owner()->compoundType());
}

inline CppAccessType accessType(const CppObjPtr& cppObj)
{
  return accessType(cppObj.get());
}

inline bool isFunction(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kFunction;
}

inline bool isFunction(const CppObjPtr& cppObj)
{
  return isFunction(cppObj.get());
}

inline bool isFunctionPtr(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kFunctionPtr;
}

inline bool isFunctionPtr(const CppObjPtr& cppObj)
{
  return isFunctionPtr(cppObj.get());
}

inline bool isFunctionLike(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kFunction || cppObj->objType_ == CppObjType::kConstructor
         || cppObj->objType_ == CppObjType::kDestructor || cppObj->objType_ == CppObjType::kTypeConverter;
}

inline bool isFunctionLike(const CppObjPtr& cppObj)
{
  return isFunctionLike(cppObj.get());
}

inline bool isDestructor(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kDestructor;
}

inline bool isDestructor(const CppObjPtr& cppObj)
{
  return isDestructor(cppObj.get());
}

inline bool isEnum(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kEnum;
}

inline bool isEnum(const CppObjPtr cppObj)
{
  return isEnum(cppObj.get());
}

inline bool isTypedefName(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kTypedefName;
}

inline bool isTypedefName(const CppObjPtr& cppObj)
{
  return isTypedefName(cppObj.get());
}

inline bool isUsingDecl(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kUsingDecl;
}

inline bool isUsingDecl(const CppObjPtr& cppObj)
{
  return isUsingDecl(cppObj.get());
}

inline bool isCompound(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kCompound;
}

inline bool isCompound(const CppObjPtr& cppObj)
{
  return isCompound(cppObj.get());
}

inline bool isFwdClsDecl(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kFwdClsDecl;
}

inline bool isFwdClsDecl(const CppObjPtr& cppObj)
{
  return isFwdClsDecl(cppObj.get());
}

inline bool isNamespaceLike(const CppObj* cppObj)
{
  if (!isCompound(cppObj))
    return false;
  auto* compound = static_cast<const CppCompound*>(cppObj);
  return compound->compoundType() & CppCompoundType::kNamespace;
}

inline bool isNamespaceLike(const CppObjPtr& cppObj)
{
  return isNamespaceLike(cppObj.get());
}

inline bool isClassLike(const CppObj* cppObj)
{
  if (!isCompound(cppObj))
    return false;
  auto* compound = static_cast<const CppCompound*>(cppObj);
  return (compound->compoundType() & CppCompoundType::kClass) == CppCompoundType::kClass;
}

inline bool isClassLike(const CppObjPtr& cppObj)
{
  return isClassLike(cppObj.get());
}

inline bool isTypedefLike(const CppObj* cppObj)
{
  return (cppObj->objType_ == CppObjType::kTypedefName) || (cppObj->objType_ == CppObjType::kUsingDecl);
}

inline bool isTypedefLike(const CppObjPtr& cppObj)
{
  return isTypedefLike(cppObj.get());
}

inline bool isPreProcessorType(const CppObj* cppObj)
{
  return cppObj->objType_ > CppObjType::kCPreProcessorTypeStarts
         && cppObj->objType_ < CppObjType::kCPreProcessorTypeEnds;
}

inline bool isPreProcessorType(const CppObjPtr& cppObj)
{
  return isPreProcessorType(cppObj.get());
}

inline bool isVar(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kVar;
}

inline bool isVar(const CppObjPtr& cppObj)
{
  return isVar(cppObj.get());
}

inline bool isVarList(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kVarList;
}

inline bool isVarList(const CppObjPtr& cppObj)
{
  return isVarList(cppObj.get());
}

inline bool isExpr(const CppObj* cppObj)
{
  return cppObj->objType_ == CppObjType::kExpression;
}

inline bool isExpr(const CppObjPtr& cppObj)
{
  return isExpr(cppObj.get());
}

inline bool isPublic(const CppObj* cppObj)
{
  return accessType(cppObj) == CppAccessType::kPublic;
}

inline bool isPublic(const CppObjPtr& cppObj)
{
  return isPublic(cppObj.get());
}

inline bool isProtected(const CppObj* cppObj)
{
  return accessType(cppObj) == CppAccessType::kProtected;
}

inline bool isProtected(const CppObjPtr& cppObj)
{
  return accessType(cppObj) == CppAccessType::kProtected;
}

inline bool isPrivate(const CppObj* cppObj)
{
  return accessType(cppObj) == CppAccessType::kPrivate;
}

inline bool isPrivate(const CppObjPtr& cppObj)
{
  return isPrivate(cppObj.get());
}

inline CppCompound* root(const CppObj* cppObj)
{
  if (cppObj->owner() == nullptr)
    return isCompound(cppObj) ? const_cast<CppCompound*>(static_cast<const CppCompound*>(cppObj)) : nullptr;
  if (cppObj->owner()->owner() == nullptr)
    return cppObj->owner();
  return root(cppObj->owner());
}

inline CppCompound* root(const CppObjPtr& cppObj)
{
  return root(cppObj.get());
}
