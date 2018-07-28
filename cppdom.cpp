#include "cppdom.h"


bool CppConstructor::isCopyConstructor() const
{
  if (isCopyConstructor_)
    return *isCopyConstructor_;

  isCopyConstructor_ = false;
  if (!params_ || (params_->size() != 1))
    return false;
  const auto paramType = params_->front().varObj;
  if (paramType->ptrLevel_ != 0)
    return false;
  if (!paramType->isConst() || !paramType->isByRef())
    return false;
  if (paramType->baseType_ != name_)
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
  const auto paramType = params_->front().varObj;
  if (paramType->ptrLevel_ != 0)
    return false;
  if (paramType->isConst() || !paramType->isByRValueRef())
    return false;
  if (paramType->baseType_ != name_)
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
      auto func = (CppFunction*)mem;
      if (func->attr_ & (kVirtual | kOverride))
      {
        hasVirtual_ = true;
        break;
      }
    }
  }
  return *hasVirtual_;
}

bool CppCompound::isAbstract() const
{
  if (!isClassLike())
    return false;
  if (isAbstract_)
    return *isAbstract_;
  isAbstract_ = false;
  for (auto mem : members_)
  {
    if (mem->objType_ == kFunction)
    {
      auto func = (CppFunction*)mem;
      if (func->isPureVirtual())
      {
        isAbstract_ = true;
        break;
      }
    }
  }
  return *isAbstract_;
}
