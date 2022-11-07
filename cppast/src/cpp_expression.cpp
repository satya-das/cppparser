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

} // namespace cppast
