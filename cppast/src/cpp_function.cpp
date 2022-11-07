// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_function.h"

namespace cppast {

CppConstructor::CppConstructor(std::string                             name,
                               std::vector<std::unique_ptr<CppEntity>> params,
                               CppMemberInits                          memInitList,
                               std::uint32_t                           attr)
  : CppFuncCtorBase(EntityType(), name, std::move(params), attr)
  , memInits_(std::move(memInitList))
{
}

CppConstructor::~CppConstructor() = default;

} // namespace cppast
