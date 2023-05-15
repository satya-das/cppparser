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

  cppast::CppConstExprEPtr gotoStmt = members[1];
  REQUIRE(gotoStmt);
  CHECK(gotoStmt->flags_ == cppast::CppExpression::kGoto);

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

  cppast::CppConstExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == cppast::CppOperator::kTertiaryOperator);

  const auto cond = topLevelOp->expr1_.expr;
  REQUIRE(cond);
  CHECK(cond->oper_ == cppast::CppOperator::kCmpEqual);
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

  cppast::CppConstExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == cppast::CppOperator::kLess);

  const auto left = topLevelOp->expr1_.expr;
  REQUIRE(left);
  CHECK(left->oper_ == cppast::CppOperator::kMul);
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

  cppast::CppConstExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == cppast::CppOperator::kGreater);

  const auto left = topLevelOp->expr1_.expr;
  REQUIRE(left);
  CHECK(left->oper_ == cppast::CppOperator::kMul);
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

  cppast::CppConstExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == cppast::CppOperator::kPlus);

  const auto left = topLevelOp->expr1_.expr;
  REQUIRE(left);
  CHECK(left->oper_ == cppast::CppOperator::kMul);
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

  cppast::CppConstExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == cppast::CppOperator::kPlus);

  const auto right = topLevelOp->expr2_.expr;
  REQUIRE(right);
  CHECK(right->oper_ == cppast::CppOperator::kMul);
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
  cppast::CppConstExprEPtr expr = members[1];
  REQUIRE(expr);
}
