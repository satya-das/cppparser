/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <catch/catch.hpp>

#include "cppparser.h"

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

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);

  CppVarEPtr var = members[0];
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

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 4);

  CppExprEPtr gotoStmt = members[1];
  REQUIRE(gotoStmt);
  CHECK(gotoStmt->flags_ == CppExpr::kGoto);

  CppLabelEPtr labelStmt = members[2];
  REQUIRE(labelStmt);
  CHECK(labelStmt->label_ == "cleanup");
}

TEST_CASE_METHOD(ExpressionTest, "a == b ? c : d")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int a, b, c, d;
  a == b ? c : d;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 2);

  CppExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == kTertiaryOperator);

  const auto cond = topLevelOp->expr1_.expr;
  REQUIRE(cond);
  CHECK(cond->oper_ == kCmpEqual);
}

TEST_CASE_METHOD(ExpressionTest, "a * b < c")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int a, b, c;
  a*  b < c;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 2);

  CppExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == kLess);

  const auto left = topLevelOp->expr1_.expr;
  REQUIRE(left);
  CHECK(left->oper_ == kMul);
}

TEST_CASE_METHOD(ExpressionTest, "a * b > c")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int a, b, c;
  a*  b > c;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 2);

  CppExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == kGreater);

  const auto left = topLevelOp->expr1_.expr;
  REQUIRE(left);
  CHECK(left->oper_ == kMul);
}

TEST_CASE_METHOD(ExpressionTest, "a * b + c")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int a = 1, b = 5, c = 0;
  a*  b + c;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 2);

  CppExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == kPlus);

  const auto left = topLevelOp->expr1_.expr;
  REQUIRE(left);
  CHECK(left->oper_ == kMul);
}

TEST_CASE_METHOD(ExpressionTest, "a + b * c")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int    a = 1, b = 5, c = 0;
  a + b* c;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 2);

  CppExprEPtr topLevelOp = members[1];
  REQUIRE(topLevelOp);
  CHECK(topLevelOp->oper_ == kPlus);

  const auto right = topLevelOp->expr2_.expr;
  REQUIRE(right);
  CHECK(right->oper_ == kMul);
}

#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
b = x > y;
#  endif
#endif
TEST_CASE_METHOD(ExpressionTest, "b = x > y")
{
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 4);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 3);
  CppExprEPtr expr = members[1];
  REQUIRE(expr);
}
