// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef FD128B15_4F2F_4742_A4B5_D3C91033195C
#define FD128B15_4F2F_4742_A4B5_D3C91033195C

#include "cppast/cpp_entity.h"

#include <cassert>
#include <variant>
#include <vector>

namespace cppast {

enum class CppVarInitializeType
{
  USING_EQUAL,
  DIRECT_CONSTRUCTOR_CALL
};

class CppExpression;

using CppCallArgs   = std::vector<std::unique_ptr<const CppExpression>>;
using CppArraySizes = CppCallArgs;

enum class CppConstructorCallStyle : bool
{
  USING_PARENTHESES,
  USING_BRACES
};

struct CppConstructorCallInfo
{
  CppCallArgs             args;
  CppConstructorCallStyle style;
};

using CppVarInitInfo = std::variant<    // Variable can be initialized using different ways.
  std::unique_ptr<const CppExpression>, // Variable is initialized using '='.
  CppConstructorCallInfo                // Variable is initialized using direct constructor call.
  >;

class CppVarDecl
{
public:
  CppVarDecl(std::string name)
    : name_(std::move(name))
  {
  }

  CppVarDecl(std::string name, CppVarInitInfo initInfo)
    : name_(std::move(name))
    , initInfo_(std::move(initInfo))
  {
  }

  CppVarDecl(std::string name, std::unique_ptr<const CppExpression> assignExpr)
    : CppVarDecl(std::move(name), CppVarInitInfo(std::move(assignExpr)))
  {
  }

  CppVarDecl(std::string name, CppCallArgs constructorParams, CppConstructorCallStyle style)
    : CppVarDecl(std::move(name), CppConstructorCallInfo {std::move(constructorParams), style})
  {
  }

  void initialize(CppVarInitInfo initInfo)
  {
    initInfo_ = std::move(initInfo);
  }

  const std::string& name() const
  {
    return name_;
  }

  bool isInitialized() const
  {
    return initInfo_.has_value();
  }

  std::optional<CppVarInitializeType> initializeType() const
  {
    if (!isInitialized())
      return std::nullopt;
    if (initInfo_.value().index() == 0)
      return CppVarInitializeType::USING_EQUAL;
    return CppVarInitializeType::DIRECT_CONSTRUCTOR_CALL;
  }

  /**
   * @brief Gets the value assigned to variable.
   *
   * @return value assigned to variable.
   * @note The returned value can be nullptr.
   */
  const CppExpression* assignValue() const
  {
    if (initializeType() != CppVarInitializeType::USING_EQUAL)
      return nullptr;
    return std::get<std::unique_ptr<const CppExpression>>(initInfo_.value()).get();
  }

  CppConstructorCallStyle directConstructorCallStyle() const
  {
    return std::get<CppConstructorCallInfo>(initInfo_.value()).style;
  }

  const CppCallArgs& constructorCallArgs() const
  {
    return std::get<CppConstructorCallInfo>(initInfo_.value()).args;
  }

  const CppExpression* bitField() const
  {
    return bitField_.get();
  }
  void bitField(std::unique_ptr<const CppExpression> bitFieldArg)
  {
    bitField_ = std::move(bitFieldArg);
  }

  const CppArraySizes& arraySizes() const
  {
    return arraySizes_;
  }
  void addArraySize(CppExpression* arraySize)
  {
    arraySizes_.emplace_back(arraySize);
  }

private:
  std::string                   name_;
  std::optional<CppVarInitInfo> initInfo_;

  std::unique_ptr<const CppExpression> bitField_;
  CppArraySizes                        arraySizes_;
};

} // namespace cppast

#endif /* FD128B15_4F2F_4742_A4B5_D3C91033195C */
