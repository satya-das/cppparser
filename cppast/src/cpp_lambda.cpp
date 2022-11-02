// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_function.h"

namespace CppAst {

CppLambda::CppLambda(std::unique_ptr<CppExpr>                captures,
                     std::vector<std::unique_ptr<CppEntity>> params,
                     std::unique_ptr<CppCompound>            defn,
                     std::unique_ptr<CppVarType>             retType)
  : CppFuncLikeBase(EntityType())
  , captures_(std::move(captures))
  , params_(std::move(params))
  , retType_(std::move(retType))
  , defn_(std::move(defn))
{
}

} // namespace CppAst
