#ifndef B1262C86_DF1F_4A47_8920_3675EB33EF3A
#define B1262C86_DF1F_4A47_8920_3675EB33EF3A

#include "cppast/cpp_expression.h"

void CodeGenMonomialExpr(std::ostream& stm, const cppast::CppMonomialExpr& monomialExpr)
{
  // clang-format off
  switch(monomialExpr.oper()){
  case cppast::CppUnaryOperator::UNARY_PLUS           : stm << '+'  << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::UNARY_MINUS          : stm << '-'  << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::PREFIX_INCREMENT     : stm << '++' << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::PREFIX_DECREMENT     : stm << '--' << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::BIT_TOGGLE           : stm << '~'  << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::LOGICAL_NOT          : stm << '!'  << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::DEREFER              : stm << '*'  << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::REFER                : stm << '&'  << monomialExpr.term(); break;

  case cppast::CppUnaryOperator::POSTFIX_INCREMENT    : stm << monomialExpr.term() << '++'; break;
  case cppast::CppUnaryOperator::POSTFIX_DECREMENT    : stm << monomialExpr.term() << '--'; break;

  case cppast::CppUnaryOperator::VARIADIC             : stm << monomialExpr.term() << "..."; break;

  case cppast::CppUnaryOperator::NEW                  : stm << "new "       << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::DELETE               : stm << "delete "    << monomialExpr.term(); break;
  case cppast::CppUnaryOperator::DELETE_AARAY         : stm << "delete[] "  << monomialExpr.term(); break;

  case cppast::CppUnaryOperator::PARENTHESIZE         : stm << '('          << monomialExpr.term() << ')'; break;
  case cppast::CppUnaryOperator::SIZE_OF              : stm << "siezeof("   << monomialExpr.term() << ')'; break;
  case cppast::CppUnaryOperator::VARIADIC_SIZE_OF     : stm << "sizeof...(" << monomialExpr.term() << ')'; break;
  }
  // clang-format on
}

void CodeGenStringLiteralExpr(std::ostream& stm, const cppast::CppStringLiteralExpr& expr)
{
  stm << expr.value();
};

void CodeGenCharLiteralExpr(std::ostream& stm, const cppast::CppCharLiteralExpr& expr)
{
  stm << expr.value();
};

void CodeGenNumberLiteralExpr(std::ostream& stm, const cppast::CppNumberLiteralExpr& expr)
{
  stm << expr.value();
};

void CodeGenNameExpr(std::ostream& stm, const cppast::CppNameExpr& expr)
{
  stm << expr.value();
};

void CodeGenVartypeExpression(std::ostream& stm, const cppast::CppVartypeExpression& expr)
{
  stm << expr.value();
};

void CodeGenLambdaExpr(std::ostream& stm, const cppast::CppLambdaExpr& expr)
{
  stm << expr.value();
}
#endif /* B1262C86_DF1F_4A47_8920_3675EB33EF3A */
