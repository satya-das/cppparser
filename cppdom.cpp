#include "cppdom.h"

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
