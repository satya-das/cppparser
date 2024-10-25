// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C18A3DB4_37B0_4AC7_BAB2_C9D9735913DC
#define C18A3DB4_37B0_4AC7_BAB2_C9D9735913DC

#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression.h"
#include "cppast/cpp_var.h"

namespace cppast {

/// Some blocks have common structure like if, while, and do-while.
/// They all contain a body and an expression of condition.
template <CppEntityType _EntityType>
class CppControlBlockBase : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return _EntityType;
  }

public:
  const CppEntity* condition() const
  {
    return cond_.get();
  }
  const CppEntity* body() const
  {
    return body_.get();
  }

protected:
  CppControlBlockBase(std::unique_ptr<CppEntity> cond, std::unique_ptr<CppEntity> body)
    : CppEntity(EntityType())
    , cond_(std::move(cond))
    , body_(std::move(body))
  {
  }

private:
  const std::unique_ptr<CppEntity> cond_;
  const std::unique_ptr<CppEntity> body_;
};

class CppIfBlock : public CppControlBlockBase<CppEntityType::IF_BLOCK>
{
public:
  CppIfBlock(std::unique_ptr<CppEntity> cond,
             std::unique_ptr<CppEntity> body,
             std::unique_ptr<CppEntity> _else = nullptr)
    : CppControlBlockBase(std::move(cond), std::move(body))
    , else_(std::move(_else))
  {
  }

public:
  const CppEntity* elsePart() const
  {
    return else_.get();
  }

private:
  const std::unique_ptr<CppEntity> else_;
};

class CppWhileBlock : public CppControlBlockBase<CppEntityType::WHILE_BLOCK>
{
public:
  CppWhileBlock(std::unique_ptr<CppEntity> cond, std::unique_ptr<CppEntity> body)
    : CppControlBlockBase(std::move(cond), std::move(body))
  {
  }
};

class CppDoWhileBlock : public CppControlBlockBase<CppEntityType::DO_WHILE_BLOCK>
{
public:
  CppDoWhileBlock(std::unique_ptr<CppEntity> cond, std::unique_ptr<CppEntity> body)
    : CppControlBlockBase(std::move(cond), std::move(body))
  {
  }
};

using CppExpressions = std::vector<std::unique_ptr<const CppExpression>>;

class CppForBlock : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::FOR_BLOCK;
  }

public:
  CppForBlock(std::unique_ptr<CppEntity>           start,
              std::unique_ptr<const CppExpression> stop,
              std::unique_ptr<const CppExpression> step,
              std::unique_ptr<CppEntity>           body)
    : CppEntity(EntityType())
    , start_(std::move(start))
    , stop_(std::move(stop))
    , step_(std::move(step))
    , body_(std::move(body))
  {
  }

  const CppEntity* start() const
  {
    return start_.get();
  }

  const CppExpression* stop() const
  {
    return stop_.get();
  }

  const CppExpression* step() const
  {
    return step_.get();
  }

  const CppEntity* body() const
  {
    return body_.get();
  }

private:
  const std::unique_ptr<CppEntity>           start_;
  const std::unique_ptr<const CppExpression> stop_;
  const std::unique_ptr<const CppExpression> step_;
  const std::unique_ptr<CppEntity>           body_;
};

class CppRangeForBlock : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::RANGE_FOR_BLOCK;
  }

public:
  CppRangeForBlock(std::unique_ptr<CppVar> var, std::unique_ptr<CppExpression> expr, std::unique_ptr<CppEntity> body)
    : CppEntity(EntityType())
    , var_(std::move(var))
    , expr_(std::move(expr))
    , body_(std::move(body))
  {
  }

public:
  const CppVar* var() const
  {
    return var_.get();
  }

  const CppExpression* expr() const
  {
    return expr_.get();
  }

  const CppEntity* body() const
  {
    return body_.get();
  }

private:
  const std::unique_ptr<CppVar>        var_;
  const std::unique_ptr<CppExpression> expr_;
  const std::unique_ptr<CppEntity>     body_;
};

class CppCase
{
public:
  CppCase(std::unique_ptr<CppExpression> caseExpr, std::unique_ptr<CppCompound> body)
    : case_(std::move(caseExpr))
    , body_(std::move(body))
  {
  }

public:
  const CppExpression* caseExpr() const
  {
    return case_.get();
  }

  const CppCompound* body() const
  {
    return body_.get();
  }

private:
  std::unique_ptr<CppExpression> case_;
  std::unique_ptr<CppCompound>   body_;
};

class CppSwitchBlock : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::SWITCH_BLOCK;
  }

public:
  CppSwitchBlock(std::unique_ptr<CppExpression> cond, std::vector<CppCase> body)
    : CppEntity(EntityType())
    , cond_(std::move(cond))
    , body_(std::move(body))
  {
  }

public:
  const CppExpression* condition() const
  {
    return cond_.get();
  }

  const std::vector<CppCase>& body() const
  {
    return body_;
  }

private:
  const std::unique_ptr<CppExpression> cond_;
  const std::vector<CppCase>           body_;
};

} // namespace cppast

#endif /* C18A3DB4_37B0_4AC7_BAB2_C9D9735913DC */
