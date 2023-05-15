// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef FD128B15_4F2F_4742_A4B5_D3C91033195C
#define FD128B15_4F2F_4742_A4B5_D3C91033195C

#include "cppast/cpp_entity.h"

#include <cassert>
#include <vector>

namespace cppast {

enum class AssignType
{
  NONE,
  USING_EQUAL,
  USING_PARENTHESES,
  USING_BRACES
};

class CppExpression;

using CppArraySizes = std::vector<std::unique_ptr<CppExpression>>;

class CppVarDecl
{
public:
  CppVarDecl(std::string name)
    : name_(std::move(name))
  {
  }

  CppVarDecl(std::string name, CppExpression* assign, AssignType assignType = AssignType::NONE);

  const std::string& name() const
  {
    return name_;
  }
  void name(std::string _name)
  {
    name_ = std::move(_name);
  }

  const CppExpression* assignValue() const
  {
    return assignValue_.get();
  }
  AssignType assignType() const
  {
    return assignType_;
  }
  void assign(CppExpression* assignVal, AssignType assignType)
  {
    assert(assignType_ == AssignType::NONE);
    assignValue_.reset(assignVal);
    assignType_ = assignType;
  }

  const CppExpression* bitField() const
  {
    return bitField_.get();
  }
  void bitField(CppExpression* _bitField)
  {
    bitField_.reset(_bitField);
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
  std::string              name_;
  std::unique_ptr<CppExpression> assignValue_; // Value assigned at declaration.
  AssignType               assignType_ {AssignType::NONE};

  std::unique_ptr<CppExpression> bitField_;
  CppArraySizes            arraySizes_;
};

inline CppVarDecl::CppVarDecl(std::string name, CppExpression* assign, AssignType assignType)
  : name_(std::move(name))
  , assignValue_(assign)
  , assignType_(assignType)
{
}

} // namespace cppast

#endif /* FD128B15_4F2F_4742_A4B5_D3C91033195C */
