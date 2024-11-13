// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BE6CEA53_1EF6_4B14_AA5B_A7FAA7AE5512
#define BE6CEA53_1EF6_4B14_AA5B_A7FAA7AE5512

#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression_operators.h"
#include "cppast/cpp_expression_type.h"
#include "cppast/cpp_typecast_type.h"
#include "cppast/cpp_var_type.h"

#include <string>

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

protected:
  CppExpression(CppExpressionType expressionType)
    : CppEntity(EntityType())
    , expressionType_(expressionType)
  {
  }

private:
  const CppExpressionType expressionType_;
};

enum class CppAtomicExprType
{
  STRING_LITERAL,
  CHAR_LITERAL,
  NUMBER_LITEREL,
  NAME,
  VARTYPE,
  LAMBDA,
};

/**
 * @brief Atomic expression is an expression that involves no operator.
 *
 * Expressions like string literal or number literals are atomic expressions.
 * @see CppAtomicExprType.
 */
class CppAtomicExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::ATOMIC;
  }

  auto atomicExpressionType() const
  {
    return atomicExprType_;
  }

protected:
  CppAtomicExpr(CppAtomicExprType atomicExprType)
    : CppExpression(ExpressionType())
    , atomicExprType_(atomicExprType)
  {
  }

private:
  const CppAtomicExprType atomicExprType_;
};

template <CppAtomicExprType _AtomicExprType>
class CppAtomicExprImplBase
{
public:
  static constexpr auto AtomicExprType()
  {
    return _AtomicExprType;
  }

protected:
  CppAtomicExprImplBase() {}
};

template <CppAtomicExprType _AtomicExprType>
class CppCommonAtomicExprImplBase : public CppAtomicExprImplBase<_AtomicExprType>
{
public:
  const std::string& value() const
  {
    return atom_;
  }

protected:
  CppCommonAtomicExprImplBase(std::string atom)
    : atom_(std::move(atom))
  {
  }

private:
  std::string atom_;
};

class CppStringLiteralExpr : public CppAtomicExpr, public CppCommonAtomicExprImplBase<CppAtomicExprType::STRING_LITERAL>
{
public:
  CppStringLiteralExpr(std::string atom)
    : CppAtomicExpr(AtomicExprType())
    , CppCommonAtomicExprImplBase(std::move(atom))
  {
  }

  friend bool operator==(const CppStringLiteralExpr& lhs, const CppStringLiteralExpr& rhs)
  {
    return lhs.value() == rhs.value();
  }
};

class CppCharLiteralExpr : public CppAtomicExpr, public CppCommonAtomicExprImplBase<CppAtomicExprType::CHAR_LITERAL>
{
public:
  CppCharLiteralExpr(std::string atom)
    : CppAtomicExpr(AtomicExprType())
    , CppCommonAtomicExprImplBase(std::move(atom))
  {
  }
};

class CppNumberLiteralExpr : public CppAtomicExpr, public CppCommonAtomicExprImplBase<CppAtomicExprType::NUMBER_LITEREL>
{
public:
  CppNumberLiteralExpr(std::string atom)
    : CppAtomicExpr(AtomicExprType())
    , CppCommonAtomicExprImplBase(std::move(atom))
  {
  }
};

class CppNameExpr : public CppAtomicExpr, public CppCommonAtomicExprImplBase<CppAtomicExprType::NAME>
{
public:
  CppNameExpr(std::string atom)
    : CppAtomicExpr(AtomicExprType())
    , CppCommonAtomicExprImplBase(std::move(atom))
  {
  }

  friend bool operator==(const CppNameExpr& lhs, const CppNameExpr& rhs)
  {
    return lhs.value() == rhs.value();
  }
};

class CppVartypeExpr : public CppAtomicExpr, public CppAtomicExprImplBase<CppAtomicExprType::VARTYPE>
{
public:
  CppVartypeExpr(std::unique_ptr<const CppVarType> atom)
    : CppAtomicExpr(AtomicExprType())
    , atom_(std::move(atom))
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
class CppLambdaExpr : public CppAtomicExpr, public CppAtomicExprImplBase<CppAtomicExprType::LAMBDA>
{
public:
  CppLambdaExpr(std::unique_ptr<const CppLambda> lambda)
    : CppAtomicExpr(AtomicExprType())
    , lambda_(std::move(lambda))
  {
  }

public:
  const CppLambda& lamda() const
  {
    return *lambda_;
  }

private:
  const std::unique_ptr<const CppLambda> lambda_;
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
  CppBinomialExpr(CppBinaryOperator                    oper,
                  std::unique_ptr<const CppExpression> term1,
                  std::unique_ptr<const CppExpression> term2)
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
  const CppBinaryOperator                    oper_;
  const std::unique_ptr<const CppExpression> term1_;
  const std::unique_ptr<const CppExpression> term2_;
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
  CppFunctionCallExpr(std::unique_ptr<const CppExpression> func, std::vector<std::unique_ptr<const CppExpression>> args)
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
  const std::unique_ptr<const CppExpression>              function_;
  const std::vector<std::unique_ptr<const CppExpression>> arguments_;
};

class CppUniformInitializerExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::UNIFORM_INITIALIZER;
  }

public:
  CppUniformInitializerExpr(std::string name, std::vector<std::unique_ptr<const CppExpression>> args)
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
  const std::string                                       name_;
  const std::vector<std::unique_ptr<const CppExpression>> arguments_;
};

class CppInitializerListExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::INITIALIZER_LIST;
  }

public:
  CppInitializerListExpr(std::vector<std::unique_ptr<const CppExpression>> exprList)
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
  const std::vector<std::unique_ptr<const CppExpression>> exprList_;
};

class CppTypecastExpr : public CppExpression
{
public:
  static constexpr auto ExpressionType()
  {
    return CppExpressionType::TYPECAST;
  }

public:
  auto castType() const
  {
    return castType_;
  }

public:
  const CppVarType& targetType() const
  {
    return *targetType_;
  }

  const CppExpression& inputExpresion() const
  {
    return *expr_;
  }

protected:
  CppTypecastExpr(CppTypecastType                      typecastType,
                  std::unique_ptr<const CppVarType>    targetType,
                  std::unique_ptr<const CppExpression> expr)
    : CppExpression(ExpressionType())
    , castType_(typecastType)
    , targetType_(std::move(targetType))
    , expr_(std::move(expr))
  {
  }

private:
  const CppTypecastType                      castType_;
  const std::unique_ptr<const CppVarType>    targetType_;
  const std::unique_ptr<const CppExpression> expr_;
};

template <CppTypecastType _TypecastType>
class CppTypecastExprImplBase
{
public:
  static constexpr auto TypecastType()
  {
    return _TypecastType;
  }

public:
};

class CppCStyleTypecastExpr : public CppTypecastExpr, public CppTypecastExprImplBase<CppTypecastType::C_STYLE>
{
public:
  CppCStyleTypecastExpr(std::unique_ptr<const CppVarType> targetType, std::unique_ptr<const CppExpression> expr)
    : CppTypecastExpr(TypecastType(), std::move(targetType), std::move(expr))
  {
  }
};

class CppFunctionStyleTypecastExpr : public CppTypecastExpr,
                                     public CppTypecastExprImplBase<CppTypecastType::FUNCTION_STYLE>
{
public:
  CppFunctionStyleTypecastExpr(std::unique_ptr<const CppVarType> targetType, std::unique_ptr<const CppExpression> expr)
    : CppTypecastExpr(TypecastType(), std::move(targetType), std::move(expr))
  {
  }
};

class CppStaticCastExpr : public CppTypecastExpr, public CppTypecastExprImplBase<CppTypecastType::STATIC>
{
public:
  CppStaticCastExpr(std::unique_ptr<const CppVarType> targetType, std::unique_ptr<const CppExpression> expr)
    : CppTypecastExpr(TypecastType(), std::move(targetType), std::move(expr))
  {
  }
};

class CppConstCastExpr : public CppTypecastExpr, public CppTypecastExprImplBase<CppTypecastType::CONST>
{
public:
  CppConstCastExpr(std::unique_ptr<const CppVarType> targetType, std::unique_ptr<const CppExpression> expr)
    : CppTypecastExpr(TypecastType(), std::move(targetType), std::move(expr))
  {
  }
};

class CppDynamiCastExpr : public CppTypecastExpr, public CppTypecastExprImplBase<CppTypecastType::DYNAMIC>
{
public:
  CppDynamiCastExpr(std::unique_ptr<const CppVarType> targetType, std::unique_ptr<const CppExpression> expr)
    : CppTypecastExpr(TypecastType(), std::move(targetType), std::move(expr))
  {
  }
};

class CppReinterpretCastExpr : public CppTypecastExpr, public CppTypecastExprImplBase<CppTypecastType::REINTERPRET>
{
public:
  CppReinterpretCastExpr(std::unique_ptr<const CppVarType> targetType, std::unique_ptr<const CppExpression> expr)
    : CppTypecastExpr(TypecastType(), std::move(targetType), std::move(expr))
  {
  }
};

} // namespace cppast

#endif /* BE6CEA53_1EF6_4B14_AA5B_A7FAA7AE5512 */
