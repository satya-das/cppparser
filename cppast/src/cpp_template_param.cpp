// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_template_param.h"
#include "cppast/cpp_function.h"
#include "cppast/cpp_var_type.h"

namespace cppast {

CppTemplateParam::CppTemplateParam(std::string paramName, ArgType defArg)
  : paramName_(std::move(paramName))
  , defaultArg_(std::move(defArg))
{
}

CppTemplateParam::CppTemplateParam(ParamType paramType, std::string paramName, ArgType defArg)
  : paramType_(std::move(paramType))
  , paramName_(std::move(paramName))
  , defaultArg_(std::move(defArg))
{
}

CppTemplateParam::~CppTemplateParam() = default;

} // namespace cppast
