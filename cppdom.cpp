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

#include "cppdom.h"

bool CppConstructor::isCopyConstructor() const
{
  if (isCopyConstructor_)
    return *isCopyConstructor_;

  isCopyConstructor_ = false;
  if (!params_ || (params_->size() != 1))
    return false;
  const auto param = params_->front().varObj;
  if (param->varType_->typeModifier_.ptrLevel_ != 0)
    return false;
  if (!param->varType_->isConst() || !param->varType_->isByRef())
    return false;
  if (param->varType_->baseType_ != name_)
    return false;
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
  const auto param = params_->front().varObj;
  if (param->varType_->typeModifier_.ptrLevel_ != 0)
    return false;
  if (param->varType_->isConst() || !param->varType_->isByRValueRef())
    return false;
  if (param->varType_->baseType_ != name_)
    return false;
  isMoveConstructor_ = true;
  return *isMoveConstructor_;
}

bool CppCompound::hasVirtualMethod() const
{
  if (!isClassLike())
    return false;
  if (hasVirtual_)
    return *hasVirtual_;
  hasVirtual_ = false;
  for (auto mem : members_)
  {
    if (mem->objType_ == kFunction)
    {
      auto func = (CppFunction*) mem;
      if (func->attr_ & (kVirtual | kOverride))
      {
        hasVirtual_ = true;
        break;
      }
    }
  }
  return *hasVirtual_;
}

bool CppCompound::hasPureVirtual() const
{
  if (!isClassLike())
    return false;
  if (hasPureVirtual_)
    return *hasPureVirtual_;
  hasPureVirtual_ = false;
  for (auto mem : members_)
  {
    if (mem->objType_ == kFunction)
    {
      auto func = static_cast<const CppFunction*>(mem);
      if (func->isPureVirtual())
      {
        hasPureVirtual_ = true;
        break;
      }
    }
    else if (mem->objType_ == kDestructor)
    {
      auto dtor = static_cast<const CppDestructor*>(mem);
      if (dtor->isPureVirtual())
      {
        hasPureVirtual_ = true;
        break;
      }
    }
  }
  return *hasPureVirtual_;
}
