// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_template_param.h"
#include "cppast/cpp_function.h"
#include "cppast/cpp_var_type.h"

namespace CppAst {

CppTemplateParam::CppTemplateParam(std::string paramName)
  : paramName_(std::move(paramName))
{
}

CppTemplateParam::CppTemplateParam(std::unique_ptr<const CppVarType> paramType,
                                   std::string                       paramName,
                                   std::unique_ptr<const CppEntity>  defArg)
  : paramType_(std::move(paramType))
  , paramName_(std::move(paramName))
  , defaultArg_(std::move(defArg))
{
}

CppTemplateParam::CppTemplateParam(std::unique_ptr<const CppFunctionPointer> paramType,
                                   std::string                               paramName,
                                   std::unique_ptr<const CppEntity>          defArg)
  : paramType_(std::move(paramType))
  , paramName_(std::move(paramName))
  , defaultArg_(std::move(defArg))
{
}

CppTemplateParam::~CppTemplateParam() = default;

} // namespace CppAst
