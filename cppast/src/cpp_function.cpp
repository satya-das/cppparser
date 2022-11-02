// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_function.h"

namespace CppAst {

CppConstructor::CppConstructor(std::string                              name,
                               std::vector<std::unique_ptr<CppEntity>>* params,
                               CppMemInits                              memInitList,
                               std::uint32_t                            attr)
  : CppFuncCtorBase(EntityType(), name, params, attr)
  , memInits_(memInitList)
{
}

CppConstructor::~CppConstructor()
{
  if (memInits_.memInitListIsABlob_)
    delete memInits_.blob;
  else
    delete memInits_.memInitList;
}

} // namespace CppAst
