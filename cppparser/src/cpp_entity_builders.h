// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E7E01B9C_F9F8_41CC_947E_80D6A1262373
#define E7E01B9C_F9F8_41CC_947E_80D6A1262373

#include "memory_util.h"

#include "cppast/cppast.h"
#include "cpptoken.h"

////////////////////////////////////////////////////////////////////////////////////////////////

struct CppExpression;

////////////////////////////////////////////////////////////////////////////////////////////////

class CppEntity;

struct CppFunctionData
{
  CppToken                                         funcName;
  std::vector<std::unique_ptr<cppast::CppEntity>>* paramList;
  unsigned int                                     funcAttr;
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

inline auto FuncCallExpr(cppast::CppExpression* func, const cppast::CppExpression* arg)
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

inline auto UniformInitExpr(std::string name, cppast::CppCallArgs* args)
{
  return new cppast::CppUniformInitializerExpr(std::move(name), Obj(args));
}

inline auto InitializerListExpr(cppast::CppCallArgs* exprList)
{
  return new cppast::CppInitializerListExpr(Obj(exprList));
}

inline auto CStyleCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppCStyleTypecastExpr(Ptr(targetType), Ptr(expr));
}

inline auto StaticCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppStaticCastExpr(Ptr(targetType), Ptr(expr));
}

inline auto ConstCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppConstCastExpr(Ptr(targetType), Ptr(expr));
}

inline auto DynamiCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppDynamiCastExpr(Ptr(targetType), Ptr(expr));
}

inline auto ReinterpretCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppReinterpretCastExpr(Ptr(targetType), Ptr(expr));
}

inline auto VarTypeExpr(const cppast::CppVarType* vartype)
{
  return new cppast::CppVartypeExpression(Ptr(vartype));
}

inline auto VarTypeExpr(std::string baseType, cppast::CppTypeModifier modifier)
{
  return VarTypeExpr(new cppast::CppVarType(std::move(baseType), modifier));
}

inline auto NewExpr(const cppast::CppVarType* vartype)
{
  return new cppast::CppVartypeExpression(Ptr(vartype));
}

inline auto LambdaExpression(const cppast::CppLambda* lambda)
{
  return new cppast::CppLambdaExpr(Ptr(lambda));
}

inline auto VarDecl(std::string name, cppast::CppVarInitInfo* initInfo)
{
  return initInfo ? cppast::CppVarDecl(name, Obj(initInfo)) : cppast::CppVarDecl(name);
}

inline auto VarInitInfo(const cppast::CppExpression* expr)
{
  return new cppast::CppVarInitInfo(Ptr(expr));
}

inline auto VarInitInfo(cppast::CppCallArgs* args, cppast::CppConstructorCallStyle style)
{
  return new cppast::CppVarInitInfo(cppast::CppConstructorCallInfo {args ? Obj(args) : cppast::CppCallArgs(), style});
}

inline auto MemberInit(std::string memberName, const cppast::CppExpression* arg, cppast::CppConstructorCallStyle style)
{
  cppast::CppCallArgs args;
  if (arg)
    args.emplace_back(arg);
  return new cppast::CppMemberInit {std::move(memberName), cppast::CppConstructorCallInfo {std::move(args), style}};
}

inline auto MemberInit(std::string memberName, cppast::CppCallArgs* args, cppast::CppConstructorCallStyle style)
{
  return new cppast::CppMemberInit {std::move(memberName),
                                    cppast::CppConstructorCallInfo {args ? Obj(args) : cppast::CppCallArgs(), style}};
}

#endif /* E7E01B9C_F9F8_41CC_947E_80D6A1262373 */
