// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppobjfactory.h"

// TODO: Get rid of this file

using namespace CppAst;

CppCompound* CppObjFactory::CreateCompound(std::string name, CppCompoundType type) const
{
  return new CppCompound(std::move(name), type);
}

CppCompound* CppObjFactory::CreateCompound(CppCompoundType type) const
{
  return new CppCompound(type);
}

CppConstructor* CppObjFactory::CreateConstructor(std::string                              name,
                                                 std::vector<std::unique_ptr<CppEntity>>* params,
                                                 CppMemInits                              memInits,
                                                 unsigned int                             attr) const
{
  return new CppConstructor(std::move(name), params, memInits, attr);
}

CppDestructor* CppObjFactory::CreateDestructor(std::string name, std::uint32_t attr) const
{
  return new CppDestructor(name, attr);
}

CppFunction* CppObjFactory::CreateFunction(std::string                              name,
                                           CppVarType*                              retType,
                                           std::vector<std::unique_ptr<CppEntity>>* params,
                                           unsigned int                             attr) const
{
  return new CppFunction(std::move(name), retType, params, attr);
}

CppTypeConverter* CppObjFactory::CreateTypeConverter(CppVarType* type, std::string name) const
{
  return new CppTypeConverter(type, std::move(name));
}
