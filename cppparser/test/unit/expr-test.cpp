// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

#include "embedded-snippet-test-base.h"

#include <string>

class ExpressionTest : public EmbeddedSnippetTestBase
{
protected:
  ExpressionTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

TEST_CASE_METHOD(ExpressionTest, "new char* []")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  auto p = new char*[5];
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstVarEPtr var = members[0];
  REQUIRE(var);

  CHECK(var->assignValue() != nullptr);
}

TEST_CASE_METHOD(ExpressionTest, "goto cleanup")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  const auto Cleanup = [&]() {
    // Do cleanup;
  };

  goto cleanup;

cleanup:
  Cleanup();
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 4);

  cppast::CppConstGotoStatementEPtr gotoStmt = members[1];
  REQUIRE(gotoStmt);
  const auto&                  label     = gotoStmt->label();
  cppast::CppConstNameExprEPtr labelExpr = &label;
  REQUIRE(labelExpr);
  CHECK(*labelExpr == cppast::CppNameExpr("cleanup"));

  cppast::CppConstLabelEPtr labelStmt = members[2];
  REQUIRE(labelStmt);
  CHECK(labelStmt->label() == "cleanup");
}

TEST_CASE_METHOD(ExpressionTest, "a == b ? c : d")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int a, b, c, d;
  a == b ? c : d;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 2);

  cppast::CppConstExpressionEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  cppast::CppConstTrinomialExprEPtr trinomial = topLevelOp;
  REQUIRE(trinomial);
  CHECK(trinomial->oper() == cppast::CppTernaryOperator::CONDITIONAL);
  cppast::CppConstBinomialExprEPtr term1 = &(trinomial->term1());
  REQUIRE(term1);
  CHECK(term1->oper() == cppast::CppBinaryOperator::EQUAL);
  cppast::CppConstAtomicExpressionEPtr term2 = &(trinomial->term2());
  REQUIRE(term2);
  cppast::CppConstAtomicExpressionEPtr term3 = &(trinomial->term3());
  REQUIRE(term3);
}

TEST_CASE_METHOD(ExpressionTest, "a * b < c")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int a, b, c;
  a*  b < c;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 2);

  cppast::CppConstBinomialExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper() == cppast::CppBinaryOperator::LESS);

  cppast::CppConstBinomialExprEPtr left = &(topLevelOp->term1());
  REQUIRE(left);
  CHECK(left->oper() == cppast::CppBinaryOperator::MUL);
}

TEST_CASE_METHOD(ExpressionTest, "a * b > c")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int a, b, c;
  a*  b > c;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 2);

  cppast::CppConstBinomialExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper() == cppast::CppBinaryOperator::GREATER);

  cppast::CppConstBinomialExprEPtr left = &(topLevelOp->term1());
  REQUIRE(left);
  CHECK(left->oper() == cppast::CppBinaryOperator::MUL);
}

TEST_CASE_METHOD(ExpressionTest, "a * b + c")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int a = 1, b = 5, c = 0;
  a*  b + c;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 2);

  cppast::CppConstBinomialExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper() == cppast::CppBinaryOperator::PLUS);

  cppast::CppConstBinomialExprEPtr left = &(topLevelOp->term1());
  REQUIRE(left);
  CHECK(left->oper() == cppast::CppBinaryOperator::MUL);
}

TEST_CASE_METHOD(ExpressionTest, "a + b * c")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int    a = 1, b = 5, c = 0;
  a + b* c;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 2);

  cppast::CppConstBinomialExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper() == cppast::CppBinaryOperator::PLUS);

  cppast::CppConstBinomialExprEPtr right = &(topLevelOp->term2());
  REQUIRE(right);
  CHECK(right->oper() == cppast::CppBinaryOperator::MUL);
}

#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
b = x > y;
#  endif
#endif
TEST_CASE_METHOD(ExpressionTest, "b = x > y")
{
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 4);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 3);
  cppast::CppConstBinomialExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper() == cppast::CppBinaryOperator::ASSIGN);

  cppast::CppConstBinomialExprEPtr right = &(topLevelOp->term2());
  REQUIRE(right);
  CHECK(right->oper() == cppast::CppBinaryOperator::GREATER);
}
