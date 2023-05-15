#ifndef E7E01B9C_F9F8_41CC_947E_80D6A1262373
#define E7E01B9C_F9F8_41CC_947E_80D6A1262373

#include "memory_util.h"

#include "cppast/cppast.h"
#include "cpptoken.h"

////////////////////////////////////////////////////////////////////////////////////////////////

struct CppExpression;

/* Non-terminal for member initializer */
struct CppMemberInitData
{
  CppToken               mem;
  cppast::CppExpression* init;
};

////////////////////////////////////////////////////////////////////////////////////////////////

class CppEntity;

struct CppFunctionData
{
  CppToken                                         funcName;
  std::vector<std::unique_ptr<cppast::CppEntity>>* paramList;
  unsigned int                                     funcAttr;
};

////////////////////////////////////////////////////////////////////////////////////////////////

auto NameExpr(std::string name)
{
  return new CppNameExpr(std::move(name));
}

auto MonomialExpr(cppast::CppUnaryOperator oper, cppast::CppExpression* term)
{
  return new cppast::CppMonomialExpr(oper, Ptr(term));
}

auto BinomialExpr(cppast::CppBinaryOperator oper, cppast::CppExpression* term1, cppast::CppExpression* term2)
{
  return new cppast::CppBinomialExpr(oper, Ptr(term1), Ptr(term2));
}

auto BinomialExpr(cppast::CppBinaryOperator oper, cppast::CppExpression* term1, std::string term2)
{
  return BinomialExpr(oper, term1, NameExpr(std::move(term2)));
}

auto TrinomialExpr(cppast::CppTernaryOperator oper,
                   cppast::CppExpression*     term1,
                   cppast::CppExpression*     term2,
                   cppast::CppExpression*     term3)
{
  return new cppast::CppTrinomialExpr(oper, Ptr(term1), Ptr(term2), Ptr(term3));
}

auto FuncCallExpr(cppast::CppExpression* func)
{
  return new cppast::CppFunctionCallExpr(Ptr(func), {});
}

auto FuncCallExpr(cppast::CppExpression* func, std::vector<std::unique_ptr<cppast::CppExpression>>* args)
{
  return new cppast::CppFunctionCallExpr(Ptr(func), Obj(args));
}

auto UniformInitExpr(std::string name, std::vector<std::unique_ptr<cppast::CppExpression>>* args)
{
  return new cppast::CppUniformInitializerExpr(std::move(name), Obj(args));
}

auto InitializerListExpr(std::vector<std::unique_ptr<cppast::CppExpression>>* exprList)
{
  return new CppInitializerListExpr(Obj(exprList));
}

auto CStyleCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppCStyleTypecastExpr(Ptr(targetType), Ptr(expr));
}

auto StaticCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppStaticCastExpr(Ptr(targetType), Ptr(expr));
}

auto ConstCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppConstCastExpr(Ptr(targetType), Ptr(expr));
}

auto DynamiCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppDynamiCastExpr(Ptr(targetType), Ptr(expr));
}

auto ReinterpretCastExpr(const cppast::CppVarType* targetType, const cppast::CppExpression* expr)
{
  return new cppast::CppReinterpretCastExpr(Ptr(targetType), Ptr(expr));
}

auto VartpeExpr(const cppast::CppVarType* vartype)
{
  return new cppast::CppVartypeExpression(Ptr(vartype));
}

auto NewExpr(const cppast::CppVarType* vartype)
{
  return new cppast::CppVartypeExpression(Ptr(vartype));
}

#endif /* E7E01B9C_F9F8_41CC_947E_80D6A1262373 */
