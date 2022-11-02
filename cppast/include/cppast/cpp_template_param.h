// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A6947342_A917_4B84_B327_5878ACC690B3
#define A6947342_A917_4B84_B327_5878ACC690B3

#include "cppast/defs.h"

#include <memory>
#include <string>

namespace CppAst {

class CppEntity;
class CppVarType;
class CppFunctionPointer;

/**
 * Parameter types that are used to define a templated C++ entity.
 */
class CppTemplateParam
{
public:
  CppTemplateParam(std::string paramName);
  CppTemplateParam(std::unique_ptr<const CppVarType> paramType,
                   std::string                       paramName,
                   std::unique_ptr<const CppEntity>  defArg = nullptr);
  CppTemplateParam(std::unique_ptr<const CppFunctionPointer> paramType,
                   std::string                               paramName,
                   std::unique_ptr<const CppEntity>          defArg = nullptr);

  ~CppTemplateParam();

public:
  const CppEntity* paramType() const
  {
    return paramType_.get();
  }

  const std::string& paramName() const
  {
    return paramName_;
  }

  const CppEntity* defaultArg() const
  {
    return defaultArg_.get();
  }

private:
  // If not nullptr then template param is not of type typename/class
  const std::unique_ptr<const CppEntity> paramType_;
  const std::string                      paramName_;
  const std::unique_ptr<const CppEntity> defaultArg_; //< Can be CppVarType or CppExpr
};

} // namespace CppAst

#endif /* A6947342_A917_4B84_B327_5878ACC690B3 */
