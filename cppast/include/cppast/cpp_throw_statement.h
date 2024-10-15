// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef F15509A7_09DA_415D_ACD7_9E0129DA3999
#define F15509A7_09DA_415D_ACD7_9E0129DA3999

#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression.h"

#include <memory>

namespace cppast {

class CppThrowStatement : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::THROW_STATEMENT;
  }

public:
  CppThrowStatement(std::unique_ptr<CppExpression> expr)
    : CppEntity(EntityType())
    , expr_(std::move(expr))
  {
  }
  CppThrowStatement()
    : CppThrowStatement(std::unique_ptr<CppExpression>())
  {
  }

public:
  bool hasException() const
  {
    return expr_.get() != nullptr;
  }

  const CppExpression& exception() const
  {
    return *expr_;
  }

private:
  const std::unique_ptr<CppExpression> expr_;
};

} // namespace cppast

#endif /* F15509A7_09DA_415D_ACD7_9E0129DA3999 */
