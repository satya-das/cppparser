// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef EA1A13FF_EE93_47C9_9DB6_4CC010F45EC0
#define EA1A13FF_EE93_47C9_9DB6_4CC010F45EC0

#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression.h"

#include <memory>

namespace cppast {

class CppGotoStatement : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::GOTO_STATEMENT;
  }

public:
  CppGotoStatement(std::unique_ptr<const CppExpression> expr)
    : CppEntity(EntityType())
    , expr_(std::move(expr))
  {
  }

public:
  const CppExpression& label() const
  {
    return *expr_;
  }

private:
  const std::unique_ptr<const CppExpression> expr_;
};

} // namespace cppast

#endif /* EA1A13FF_EE93_47C9_9DB6_4CC010F45EC0 */
