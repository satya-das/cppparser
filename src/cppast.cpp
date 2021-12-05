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

#include "cppcompound-info-accessor.h"
#include "cppfunc-info-accessor.h"
#include "cppobj-info-accessor.h"
#include "cppvar-info-accessor.h"

bool CppConstructor::isCopyConstructor() const
{
  if (isCopyConstructor_ != TriStateBool::Unknown)
    return isCopyConstructor_ == TriStateBool::True;

  isCopyConstructor_ = TriStateBool::False;
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
  isCopyConstructor_ = TriStateBool::True;

  return true;
}

bool CppConstructor::isMoveConstructor() const
{
  if (isMoveConstructor_ != TriStateBool::Unknown)
    return isMoveConstructor_ == TriStateBool::True;

  isMoveConstructor_ = TriStateBool::False;
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
  isMoveConstructor_ = TriStateBool::True;

  return true;
}

bool CppCompound::hasPublicVirtualMethod() const
{
  if (!isClassLike(this))
    return false;
  if (hasVirtual_ != TriStateBool::Unknown)
    return hasVirtual_ == TriStateBool::True;

  hasVirtual_ = TriStateBool::False;
  forEachMember(this, [&](const CppObj* mem) {
    if (isFunction(mem) && isPublic(mem))
    {
      auto func = (CppFunction*) mem;
      if (func->attr() & (kVirtual | kOverride))
      {
        hasVirtual_ = TriStateBool::True;
        return true;
      }
    }
    return false;
  });

  return hasVirtual_ == TriStateBool::True;
}

bool CppCompound::hasPureVirtual() const
{
  if (!isClassLike(this))
    return false;
  if (hasPureVirtual_ != TriStateBool::Unknown)
    return hasPureVirtual_ == TriStateBool::True;

  hasPureVirtual_ = TriStateBool::False;
  forEachMember(this, [&](const CppObj* mem) {
    if (isFunction(mem))
    {
      auto func = static_cast<const CppFunction*>(mem);
      if (isPureVirtual(func))
      {
        hasPureVirtual_ = TriStateBool::True;
        return true;
      }
    }
    else if (isDestructor(mem))
    {
      auto dtor = static_cast<const CppDestructor*>(mem);
      if (isPureVirtual(dtor))
      {
        hasPureVirtual_ = TriStateBool::True;
        return true;
      }
    }

    return false;
  });

  return hasPureVirtual_ == TriStateBool::True;
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
