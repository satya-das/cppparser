// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A0CFB388_7CA2_495B_BD3B_414E92AF16F5
#define A0CFB388_7CA2_495B_BD3B_414E92AF16F5

#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression.h"

#include <memory>

namespace cppast {

class CppReturnStatement : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::RETURN_STATEMENT;
  }

public:
  CppReturnStatement(std::unique_ptr<const CppExpression> expr)
    : CppEntity(EntityType())
    , expr_(std::move(expr))
  {
  }
  CppReturnStatement()
    : CppReturnStatement(std::unique_ptr<const CppExpression>())
  {
  }

public:
  bool hasReturnValue() const
  {
    return expr_.get() != nullptr;
  }

  const CppExpression& returnValue() const
  {
    return *expr_;
  }

private:
  const std::unique_ptr<const CppExpression> expr_;
};

} // namespace cppast

#endif /* A0CFB388_7CA2_495B_BD3B_414E92AF16F5 */
