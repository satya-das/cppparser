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

#include "cppast.h"
#include "cpputil.h"

#include "cppcompound-accessor.h"
#include "cppfunc-accessor.h"
#include "cppobj-accessor.h"
#include "cppvar-accessor.h"

bool CppConstructor::isCopyConstructor() const
{
  if (isCopyConstructor_)
    return *isCopyConstructor_;

  isCopyConstructor_ = false;
  if (!params_ || (params_->size() != 1))
    return false;
  const auto& param = params_->front();
  if (!isVar(param.get()))
    return false;
  const auto* var = static_cast<const CppVar*>(param.get());
  if (ptrLevel(var->varType()) != 0)
    return false;
  if (!isConst(var->varType()) || !isByRef(var->varType()))
    return false;
  auto templStartPos = var->varType()->baseType().find('<');
  if (templStartPos != std::string::npos)
  {
    while (isspace(var->varType()->baseType()[--templStartPos]))
      ;
    ++templStartPos;
    if (var->varType()->baseType().substr(0, templStartPos) != name_)
      return false;
  }
  else if (var->varType()->baseType() != name_)
  {
    return false;
  }
  isCopyConstructor_ = true;
  return *isCopyConstructor_;
}

bool CppConstructor::isMoveConstructor() const
{
  if (isMoveConstructor_)
    return *isMoveConstructor_;

  isMoveConstructor_ = false;
  if (!params_ || (params_->size() != 1))
    return false;
  const auto& param = params_->front();
  if (!isVar(param.get()))
    return false;
  const auto* var = static_cast<const CppVar*>(param.get());
  if (ptrLevel(var->varType()) != 0)
    return false;
  if (ptrLevel(var->varType()) != 0)
    return false;
  if (isConst(var->varType()) || !isByRValueRef(var->varType()))
    return false;
  auto templStartPos = var->varType()->baseType().find('<');
  if (templStartPos != std::string::npos)
  {
    while (isspace(var->varType()->baseType()[--templStartPos]))
      ;
    ++templStartPos;
    if (var->varType()->baseType().substr(0, templStartPos) != name_)
      return false;
  }
  else if (var->varType()->baseType() != name_)
  {
    return false;
  }
  isMoveConstructor_ = true;
  return *isMoveConstructor_;
}

bool CppCompound::hasPublicVirtualMethod() const
{
  if (!isClassLike(this))
    return false;
  if (hasVirtual_)
    return *hasVirtual_;
  hasVirtual_ = false;
  forEachMember(this, [&](const CppObj* mem) {
    if (isFunction(mem) && isPublic(mem))
    {
      auto func = (CppFunction*) mem;
      if (func->attr() & (kVirtual | kOverride))
      {
        hasVirtual_ = true;
        return true;
      }
    }
    return false;
  });
  return *hasVirtual_;
}

bool CppCompound::hasPureVirtual() const
{
  if (!isClassLike(this))
    return false;
  if (hasPureVirtual_)
    return *hasPureVirtual_;
  hasPureVirtual_ = false;
  forEachMember(this, [&](const CppObj* mem) {
    if (isFunction(mem))
    {
      auto func = static_cast<const CppFunction*>(mem);
      if (isPureVirtual(func))
      {
        hasPureVirtual_ = true;
        return true;
      }
    }
    else if (isDestructor(mem))
    {
      auto dtor = static_cast<const CppDestructor*>(mem);
      if (isPureVirtual(dtor))
      {
        hasPureVirtual_ = true;
        return true;
      }
    }

    return false;
  });
  return *hasPureVirtual_;
}

bool CppCompound::triviallyConstructable() const
{
  if (ctors_.empty())
    return true;
  for (auto* ctor : ctors_)
  {
    if (!ctor->hasParams())
      return true;
  }
  return false;
}

void CppCompound::assignSpecialMember(const CppObj* mem)
{
  if (mem->objType_ == CppObjType::kConstructor)
  {
    auto* ctor = static_cast<const CppConstructor*>(mem);
    ctors_.push_back(ctor);
    if (ctor->isCopyConstructor())
      copyCtor_ = ctor;
    else if (ctor->isMoveConstructor())
      moveCtor_ = ctor;
  }
  else if (mem->objType_ == CppObjType::kDestructor)
  {
    dtor_ = static_cast<const CppDestructor*>(mem);
  }
}

CppObjType objType(const CppObj* cppObj)
{
  return cppObj ? cppObj->objType_ : CppObjType::kUnknown;
}

bool operator==(const CppExpr& expr1, const CppExpr& expr2)
{
  if (expr1.flags_ != expr2.flags_)
    return false;
  if (expr1.oper_ != expr2.oper_)
    return false;
  if ((expr1.expr1_) != (expr2.expr1_))
    return false;

  if (expr1.oper_ < CppOperator::kBinaryOperatorStart)
    return true;
  if ((expr1.oper_ > CppOperator::kBinaryOperatorStart) && (expr1.oper_ < CppOperator::kBinaryOperatorEnd))
  {
    return ((expr1.expr2_) != (expr2.expr2_));
  }

  return false;
}
