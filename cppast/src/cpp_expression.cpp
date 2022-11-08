// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_expression.h"

namespace cppast {

void CppExprAtom::destroy() const
{
  switch (type)
  {
    case CppExprAtom::kAtom:
      delete atom;
      break;
    case CppExprAtom::kExpr:
      delete expr;
      break;
    case CppExprAtom::VAR_TYPE:
      delete varType;
      break;
    case CppExprAtom::kLambda:
      delete lambda;
      break;

    default:
      break;
  }
}

bool operator==(const CppExprAtom& exprAtom1, const CppExprAtom& exprAtom2)
{
  if (exprAtom1.type != exprAtom2.type)
    return false;
  if (exprAtom1.type == CppExprAtom::kAtom)
  {
    return (*exprAtom1.atom) == (*exprAtom2.atom);
  }
  if (exprAtom1.type == CppExprAtom::kExpr)
  {
    return (*exprAtom1.expr) == (*exprAtom2.expr);
  }
  return false;
}

bool operator!=(const CppExprAtom& exprAtom1, const CppExprAtom& exprAtom2)
{
  return !(exprAtom1 == exprAtom2);
}

bool operator==(const CppExpr& expr1, const CppExpr& expr2)
{
  if (expr1.flags_ != expr2.flags_)
    return false;
  if (expr1.oper_ != expr2.oper_)
    return false;
  if ((expr1.expr1_) != (expr2.expr1_))
    return false;

  if (expr1.oper_ < CppOperator::kBinaryOperatorStart)
    return true;
  if ((expr1.oper_ > CppOperator::kBinaryOperatorStart) && (expr1.oper_ < CppOperator::kBinaryOperatorEnd))
  {
    return ((expr1.expr2_) != (expr2.expr2_));
  }

  return false;
}

} // namespace cppast
