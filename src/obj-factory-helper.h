// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E9F3C1D2_FCAD_426F_BDB1_A2BC7058F759
#define E9F3C1D2_FCAD_426F_BDB1_A2BC7058F759

#include "cppast/cppast.h"
#include "cppobjfactory.h"
#include "cpptoken.h"

extern CppObjFactory* gObjFactory;

template <typename... Params>
CppCompound* newCompound(Params... params)
{
  return gObjFactory->CreateCompound(params...);
}

template <typename... Params>
CppConstructor* newConstructor(Params... params)
{
  return gObjFactory->CreateConstructor(params...);
}

template <typename... Params>
CppDestructor* newDestructor(Params... params)
{
  return gObjFactory->CreateDestructor(params...);
}

template <typename... Params>
CppFunction* newFunction(Params... params)
{
  return gObjFactory->CreateFunction(params...);
}

template <typename... Params>
CppTypeConverter* newTypeConverter(Params... params)
{
  return gObjFactory->CreateTypeConverter(params...);
}

#endif /* E9F3C1D2_FCAD_426F_BDB1_A2BC7058F759 */
