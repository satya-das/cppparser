// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BE6CEA53_1EF6_4B14_AA5B_A7FAA7AE5512
#define BE6CEA53_1EF6_4B14_AA5B_A7FAA7AE5512

#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression_operators.h"
#include "cppast/cpp_expression_type.h"
#include "cppast/cpp_operator.h"
#include "cppast/cpp_typecast_type.h"
#include "cppast/cpp_var_type.h"

namespace cppast {

class CppExpression;
class CppLambda;
class CppVarType;

/**
 * @brief An expression in a C/C++ program.
 *
 * Its a base class for all other specialized expression classes.
 */
class CppExpression : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::EXPRESSION;
  }

public:
  CppExpressionType expressionType() const
  {
    return expressionType_;
  }

public:
  CppExpression(CppExpressionType expressionType)
    : CppEntity(EntityType())
    , expressionType_(expressionType)
  {
  }

private:
  const CppExpressionType expressionType_;
};

enum class CppAtomicExpressionType
{
  STRING_LITERAL,
  CHAR_LITERAL,
  NUMBER_LITEREL,
  NAME,
  VARTYPE,
  LAMBDA,
};

template <CppAtomicExpressionType _AtomicExprType>
class CppAtomicExpression : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::ATOMIC;
  }

  static constexpr auto AtomicExpressionType()
  {
    return _AtomicExprType;
  }

public:
  CppAtomicExpression()
    : CppExpression(ExpressionType())
  {
  }
};

template <CppAtomicExpressionType _AtomicExprType>
class CppCommonAtomicExpressionBase : public CppAtomicExpression<_AtomicExprType>
{
public:
  CppCommonAtomicExpressionBase(std::string atom)
    : atom_(std::move(atom))
  {
  }

  const std::string& value() const
  {
    return atom_;
  }

private:
  std::string atom_;
};

class CppStringLiteralExpr : public CppCommonAtomicExpressionBase<CppAtomicExpressionType::STRING_LITERAL>
{
public:
  using CppCommonAtomicExpressionBase<CppAtomicExpressionType::STRING_LITERAL>::CppCommonAtomicExpressionBase;
};

class CppCharLiteralExpr : public CppCommonAtomicExpressionBase<CppAtomicExpressionType::CHAR_LITERAL>
{
public:
  using CppCommonAtomicExpressionBase<CppAtomicExpressionType::CHAR_LITERAL>::CppCommonAtomicExpressionBase;
};

class CppNumberLiteralExpr : public CppCommonAtomicExpressionBase<CppAtomicExpressionType::NUMBER_LITEREL>
{
public:
  using CppCommonAtomicExpressionBase<CppAtomicExpressionType::NUMBER_LITEREL>::CppCommonAtomicExpressionBase;
};

class CppNameExpr : public CppCommonAtomicExpressionBase<CppAtomicExpressionType::NAME>
{
public:
  using CppCommonAtomicExpressionBase<CppAtomicExpressionType::NAME>::CppCommonAtomicExpressionBase;
};

class CppVartypeExpression : public CppAtomicExpression<CppAtomicExpressionType::VARTYPE>
{
public:
  CppVartypeExpression(std::unique_ptr<const CppVarType> atom)
    : atom_(std::move(atom))
  {
  }

  const CppVarType& value() const
  {
    return *atom_;
  }

private:
  std::unique_ptr<const CppVarType> atom_;
};

// TODO: Eliminate CppLambda by merging to CppLambdaExpr.
class CppLambdaExpr : public CppAtomicExpression<CppAtomicExpressionType::LAMBDA>
{
public:
  CppLambdaExpr(std::unique_ptr<CppLambda> lambda)
    : lambda_(std::move(lambda))
  {
  }

public:
  const CppLambda& lamda() const
  {
    return *lambda_;
  }

private:
  const std::unique_ptr<CppLambda> lambda_;
};

class CppMonomialExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::MONOMIAL;
  }

public:
  CppMonomialExpr(CppUnaryOperator oper, std::unique_ptr<CppExpression> term)
    : CppExpression(ExpressionType())
    , oper_(oper)
    , term_(std::move(term))
  {
  }

public:
  const CppExpression& term() const
  {
    return *term_;
  }

  CppUnaryOperator oper() const
  {
    return oper_;
  }

private:
  const CppUnaryOperator               oper_;
  const std::unique_ptr<CppExpression> term_;
};

class CppBinomialExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::BINOMIAL;
  }

public:
  CppBinomialExpr(CppBinaryOperator oper, std::unique_ptr<CppExpression> term1, std::unique_ptr<CppExpression> term2)
    : CppExpression(ExpressionType())
    , oper_(oper)
    , term1_(std::move(term1))
    , term2_(std::move(term2))
  {
  }

public:
  CppBinaryOperator oper() const
  {
    return oper_;
  }

  const CppExpression& term1() const
  {
    return *term1_;
  }

  const CppExpression& term2() const
  {
    return *term2_;
  }

private:
  const CppBinaryOperator              oper_;
  const std::unique_ptr<CppExpression> term1_;
  const std::unique_ptr<CppExpression> term2_;
};

class CppTrinomialExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::TRINOMIAL;
  }

public:
  CppTrinomialExpr(CppTernaryOperator             oper,
                   std::unique_ptr<CppExpression> term1,
                   std::unique_ptr<CppExpression> term2,
                   std::unique_ptr<CppExpression> term3)
    : CppExpression(ExpressionType())
    , oper_(oper)
    , term1_(std::move(term1))
    , term2_(std::move(term2))
    , term3_(std::move(term3))
  {
  }

public:
  CppTernaryOperator oper() const
  {
    return oper_;
  }

  const CppExpression& term1() const
  {
    return *term1_;
  }

  const CppExpression& term2() const
  {
    return *term2_;
  }

  const CppExpression& term3() const
  {
    return *term3_;
  }

private:
  const CppTernaryOperator             oper_;
  const std::unique_ptr<CppExpression> term1_;
  const std::unique_ptr<CppExpression> term2_;
  const std::unique_ptr<CppExpression> term3_;
};

class CppFunctionCallExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::FUNCTION_CALL;
  }

public:
  CppFunctionCallExpr(std::unique_ptr<CppExpression> func, std::vector<std::unique_ptr<CppExpression>> args)
    : CppExpression(ExpressionType())
    , function_(std::move(func))
    , arguments_(std::move(args))
  {
  }

public:
  const CppExpression& function() const
  {
    return *function_;
  }

  size_t numArgs() const
  {
    return arguments_.size();
  }

  const CppExpression& arg(size_t argIndex) const
  {
    return *(arguments_[argIndex]);
  }

private:
  const std::unique_ptr<CppExpression>              function_;
  const std::vector<std::unique_ptr<CppExpression>> arguments_;
};

class CppUniformInitializerExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::UNIFORM_INITIALIZER;
  }

public:
  CppUniformInitializerExpr(std::string name, std::vector<std::unique_ptr<CppExpression>> args)
    : CppExpression(ExpressionType())
    , name_(std::move(name))
    , arguments_(std::move(args))
  {
  }

public:
  const std::string& name() const
  {
    return name_;
  }

  size_t numArgs() const
  {
    return arguments_.size();
  }

  const CppExpression& arg(size_t argIndex) const
  {
    return *(arguments_[argIndex]);
  }

private:
  const std::string                                 name_;
  const std::vector<std::unique_ptr<CppExpression>> arguments_;
};

class CppInitializerListExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::INITIALIZER_LIST;
  }

public:
  CppInitializerListExpr(std::vector<std::unique_ptr<CppExpression>> exprList)
    : CppExpression(ExpressionType())
    , exprList_(std::move(exprList))
  {
  }

public:
  size_t numArgs() const
  {
    return exprList_.size();
  }

  const CppExpression& arg(size_t argIndex) const
  {
    return *(exprList_[argIndex]);
  }

private:
  const std::vector<std::unique_ptr<CppExpression>> exprList_;
};

template <CppTypecastType _TypecastType>
class CppTypecastExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::TYPECAST;
  }

public:
  static constexpr auto TypecastType()
  {
    return _TypecastType;
  }

public:
  CppTypecastExpr(std::unique_ptr<const CppVarType> targetType, std::unique_ptr<const CppExpression> expr)
    : targetType_(targetType)
    , expr_(expr)
  {
  }

  const CppVarType& targetType() const
  {
    return *targetType_;
  }

  const CppExpression& inputExpresion() const
  {
    return *expr_;
  }

private:
  const std::unique_ptr<const CppVarType>    targetType_;
  const std::unique_ptr<const CppExpression> expr_;
};

class CppCStyleTypecastExpr : public CppTypecastExpr<CppTypecastType::C_STYLE_CAST>
{
public:
  using CppTypecastExpr<CppTypecastType::C_STYLE_CAST>::CppTypecastExpr;
};

class CppFunctionStyleTypecastExpr : public CppTypecastExpr<CppTypecastType::FUNCTION_STYLE_CAST>
{
public:
  using CppTypecastExpr<CppTypecastType::FUNCTION_STYLE_CAST>::CppTypecastExpr;
};

class CppStaticCastExpr : public CppTypecastExpr<CppTypecastType::STATIC_CAST>
{
public:
  using CppTypecastExpr<CppTypecastType::STATIC_CAST>::CppTypecastExpr;
};

class CppConstCastExpr : public CppTypecastExpr<CppTypecastType::CONST_CAST>
{
public:
  using CppTypecastExpr<CppTypecastType::CONST_CAST>::CppTypecastExpr;
};

class CppDynamiCastExpr : public CppTypecastExpr<CppTypecastType::DYNAMIC_CAST>
{
public:
  using CppTypecastExpr<CppTypecastType::DYNAMIC_CAST>::CppTypecastExpr;
};

class CppReinterpretCastExpr : public CppTypecastExpr<CppTypecastType::REINTERPRET_CAST>
{
public:
  using CppTypecastExpr<CppTypecastType::REINTERPRET_CAST>::CppTypecastExpr;
};

} // namespace cppast

#endif /* BE6CEA53_1EF6_4B14_AA5B_A7FAA7AE5512 */
