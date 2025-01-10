// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E7E01B9C_F9F8_41CC_947E_80D6A1262373
#define E7E01B9C_F9F8_41CC_947E_80D6A1262373

#include "memory_util.h"

#include "cppast/cppast.h"
#include "cpptoken.h"

////////////////////////////////////////////////////////////////////////////////////////////////

class CppEntity;

struct CppFunctionData
{
  CppToken                                               funcName;
  std::vector<std::unique_ptr<cppast::CppEntity>>* paramList;
  unsigned int                                           funcAttr;
};

////////////////////////////////////////////////////////////////////////////////////////////////

inline auto NameExpr(std::string name)
{
  return new cppast::CppNameExpr(std::move(name));
}

inline auto NumberLiteralExpr(std::string number)
{
  return new cppast::CppNameExpr(std::move(number));
}

inline auto MonomialExpr(cppast::CppUnaryOperator oper, cppast::CppExpression* term)
{
  return new cppast::CppMonomialExpr(oper, Ptr(term));
}

inline auto BinomialExpr(cppast::CppBinaryOperator oper, cppast::CppExpression* term1, cppast::CppExpression* term2)
{
  return new cppast::CppBinomialExpr(oper, Ptr(term1), Ptr(term2));
}

inline auto BinomialExpr(cppast::CppBinaryOperator oper, cppast::CppExpression* term1, std::string term2)
{
  return BinomialExpr(oper, term1, NameExpr(std::move(term2)));
}

inline auto TrinomialExpr(cppast::CppTernaryOperator oper,
                          cppast::CppExpression*     term1,
                          cppast::CppExpression*     term2,
                          cppast::CppExpression*     term3)
{
  return new cppast::CppTrinomialExpr(oper, Ptr(term1), Ptr(term2), Ptr(term3));
}

inline auto FuncCallExpr(cppast::CppExpression* func)
{
  return new cppast::CppFunctionCallExpr(Ptr(func), {});
}

inline auto FuncCallExpr(cppast::CppExpression* func, cppast::CppExpression* arg)
{
  cppast::CppCallArgs args;
  if (arg)
    args.emplace_back(arg);
  return new cppast::CppFunctionCallExpr(Ptr(func), std::move(args));
}

inline auto FuncCallExpr(cppast::CppExpression* func, cppast::CppCallArgs args)
{
  return new cppast::CppFunctionCallExpr(Ptr(func), std::move(args));
}

inline auto FuncCallExpr(cppast::CppExpression* func, cppast::CppCallArgs* args)
{
  return new cppast::CppFunctionCallExpr(Ptr(func), args ? Obj(args) : cppast::CppCallArgs());
}

inline auto UniformInitExpr(std::string name, cppast::CppCallArgs args)
{
  return new cppast::CppUniformInitializerExpr(std::move(name), std::move(args));
}

inline auto UniformInitExpr(std::string name, cppast::CppCallArgs* args)
{
  return UniformInitExpr(std::move(name), args ? Obj(args) : cppast::CppCallArgs());
}

inline auto UniformInitExpr(std::string name, cppast::CppExpression* arg)
{
  cppast::CppCallArgs args;
  if (arg)
    args.emplace_back(arg);
  return UniformInitExpr(std::move(name), std::move(args));
}

inline auto InitializerListExpr(cppast::CppCallArgs exprList)
{
  return new cppast::CppInitializerListExpr(std::move(exprList));
}

inline auto InitializerListExpr(cppast::CppCallArgs* exprList)
{
  return InitializerListExpr(exprList ? Obj(exprList) : cppast::CppCallArgs());
}

inline auto InitializerListExpr(cppast::CppExpression* expr)
{
  cppast::CppCallArgs args;
  if (expr)
    args.emplace_back(expr);
  return new cppast::CppInitializerListExpr(std::move(args));
}

inline auto CStyleCastExpr(cppast::CppVarType* targetType, cppast::CppExpression* expr)
{
  return new cppast::CppCStyleTypecastExpr(Ptr(targetType), Ptr(expr));
}

inline auto StaticCastExpr(cppast::CppVarType* targetType, cppast::CppExpression* expr)
{
  return new cppast::CppStaticCastExpr(Ptr(targetType), Ptr(expr));
}

inline auto ConstCastExpr(cppast::CppVarType* targetType, cppast::CppExpression* expr)
{
  return new cppast::CppConstCastExpr(Ptr(targetType), Ptr(expr));
}

inline auto DynamiCastExpr(cppast::CppVarType* targetType, cppast::CppExpression* expr)
{
  return new cppast::CppDynamiCastExpr(Ptr(targetType), Ptr(expr));
}

inline auto ReinterpretCastExpr(cppast::CppVarType* targetType, cppast::CppExpression* expr)
{
  return new cppast::CppReinterpretCastExpr(Ptr(targetType), Ptr(expr));
}

inline auto VarTypeExpr(cppast::CppVarType* vartype)
{
  return new cppast::CppVartypeExpr(Ptr(vartype));
}

inline auto VarTypeExpr(std::string baseType, cppast::CppTypeModifier modifier)
{
  return VarTypeExpr(new cppast::CppVarType(std::move(baseType), modifier));
}

inline auto NewExpr(cppast::CppVarType* vartype)
{
  return new cppast::CppVartypeExpr(Ptr(vartype));
}

inline auto LambdaExpression(cppast::CppLambda* lambda)
{
  return new cppast::CppLambdaExpr(Ptr(lambda));
}

/**
 * An Expression-list expression is an expression that uses ',' as operator.
 * e.g.:
 *  1) int x = 2, 3;
 *  2) gcd((3, 4, 6), 4);
 *  3) return 9, 10;
 * In these examples we see expression-lists are expressions.
 */
template <typename ExprItr>
inline cppast::CppExpression* ExpressionListExpr(ExprItr first, ExprItr end)
{
  static_assert(
    std::is_same_v<std::unique_ptr<cppast::CppExpression>, std::remove_reference_t<decltype(*first)>>);
  assert(first != end);
  auto second = first + 1;
  if (second == end)
    return const_cast<cppast::CppExpression*>(first->release());
  auto result = new cppast::CppBinomialExpr(cppast::CppBinaryOperator::COMMA, std::move(*first), std::move(*second));
  auto next   = second + 1;
  if (next == end)
    return result;
  return new cppast::CppBinomialExpr(cppast::CppBinaryOperator::COMMA, Ptr(result), Ptr(ExpressionListExpr(next, end)));
}

inline auto ExpressionListExpr(std::vector<std::unique_ptr<cppast::CppExpression>> exprList)
{
  return ExpressionListExpr(exprList.begin(), exprList.end());
}

inline auto VarDecl(std::string name, cppast::CppVarInitInfo* initInfo)
{
  return initInfo ? cppast::CppVarDecl(name, Obj(initInfo)) : cppast::CppVarDecl(name);
}

inline auto VarInitInfo(cppast::CppExpression* expr)
{
  return new cppast::CppVarInitInfo(Ptr(expr));
}

inline auto VarInitInfo(cppast::CppCallArgs* args, cppast::CppConstructorCallStyle style)
{
  return new cppast::CppVarInitInfo(cppast::CppConstructorCallInfo {args ? Obj(args) : cppast::CppCallArgs(), style});
}

inline auto MemberInit(std::string                                  memberName,
                       std::unique_ptr<cppast::CppExpression> arg,
                       cppast::CppConstructorCallStyle              style)
{
  cppast::CppCallArgs args;
  if (arg)
    args.emplace_back(arg.release());
  return new cppast::CppMemberInit {std::move(memberName), cppast::CppConstructorCallInfo {std::move(args), style}};
}

inline auto MemberInit(std::string memberName, cppast::CppCallArgs args, cppast::CppConstructorCallStyle style)
{
  return new cppast::CppMemberInit {std::move(memberName), cppast::CppConstructorCallInfo {std::move(args), style}};
}

inline auto MemberInit(std::string memberName, cppast::CppConstructorCallStyle style)
{
  return new cppast::CppMemberInit {std::move(memberName),
                                    cppast::CppConstructorCallInfo {cppast::CppCallArgs(), style}};
}

#endif /* E7E01B9C_F9F8_41CC_947E_80D6A1262373 */
