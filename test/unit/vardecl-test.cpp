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

class VarDeclTest : public EmbeddedSnippetTestBase
{
protected:
  VarDeclTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

TEST_CASE_METHOD(VarDeclTest, "int x = 5, y = 10;", "[vardecllist]")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int x = 5, y = 10;
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);
  CppVarListEPtr varlist = members[0];
  REQUIRE(varlist);
  REQUIRE(varlist->firstVar()->assignValue() != nullptr);
  CHECK(varlist->firstVar()->assignType() == AssignType::kUsingEqual);
  REQUIRE(varlist->varDeclList().size() == 1);
  REQUIRE(varlist->varDeclList()[0].assignValue() != nullptr);
  CHECK(varlist->varDeclList()[0].assignType() == AssignType::kUsingEqual);
}
