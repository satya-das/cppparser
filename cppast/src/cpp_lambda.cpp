// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_function.h"

namespace cppast {

CppLambda::CppLambda(std::unique_ptr<const CppExpression>          captures,
                     std::vector<std::unique_ptr<const CppEntity>> params,
                     std::unique_ptr<const CppCompound>            defn,
                     std::unique_ptr<const CppVarType>             retType)
  : CppEntity(EntityType())
  , captures_(std::move(captures))
  , params_(std::move(params))
  , retType_(std::move(retType))
  , defn_(std::move(defn))
{
}

} // namespace cppast
