// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A6947342_A917_4B84_B327_5878ACC690B3
#define A6947342_A917_4B84_B327_5878ACC690B3

#include "cppast/defs.h"

#include <memory>
#include <optional>
#include <string>
#include <variant>

namespace cppast {

class CppEntity;
class CppVarType;
class CppFunctionPointer;
class CppExpression;

/**
 * Parameter types that are used to define a templated C++ entity.
 */
class CppTemplateParam
{
public:
  using ParamType = std::variant<std::unique_ptr<const CppVarType>, std::unique_ptr<const CppFunctionPointer>>;
  using ArgType   = std::variant<std::unique_ptr<const CppVarType>, std::unique_ptr<const CppExpression>>;

public:
  CppTemplateParam(std::string paramName, ArgType defArg = ArgType());
  CppTemplateParam(ParamType paramType, std::string paramName, ArgType defArg = ArgType());

  CppTemplateParam(CppTemplateParam&& rval) = default;

  ~CppTemplateParam();

public:
  const std::optional<ParamType>& paramType() const
  {
    return paramType_;
  }

  const std::string& paramName() const
  {
    return paramName_;
  }

  const ArgType& defaultArg() const
  {
    return defaultArg_;
  }

private:
  // If initialized then template param is not of type typename/class
  std::optional<ParamType> paramType_;
  std::string              paramName_;
  ArgType                  defaultArg_;
};

} // namespace cppast

#include "cppast/cpp_expression.h"
#include "cppast/cpp_function.h"
#include "cppast/cpp_var_type.h"

#endif /* A6947342_A917_4B84_B327_5878ACC690B3 */
