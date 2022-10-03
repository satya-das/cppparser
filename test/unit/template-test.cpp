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

class TemplateParsingTest : public EmbeddedSnippetTestBase
{
protected:
  TemplateParsingTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
template <int kGrowPercent = 75>
class SkTDynamicHash
{
};
#endif
TEST_CASE_METHOD(TemplateParsingTest, "template <int kGrowPercent = 75>", "[template-parsing]")
{
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 4);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);
  CppCompoundEPtr compound = members[0];
  REQUIRE(compound);
}

/*
 The code
    C<v != 0> x;
 can be interpreted as 'C' being a templated type taking a boolean parameter and 'x' is a variable of such type.
 Another interpretation can be that it is an expression that is equivalent to:
    (C<v) != (0>x);

 The following test ascertains that such code must be interpreted as variable declaration.
*/
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
C<v != 0> x;
#  endif
#endif
TEST_CASE_METHOD(TemplateParsingTest, "vardecl-or-expr-ambiguity", "[template-parsing][ambiguous-input]")
{
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 4);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 3);
  CppVarEPtr var = members[1];
  REQUIRE(var);
}

#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
C<Class, v != 0> x;
#  endif
#endif
TEST_CASE_METHOD(TemplateParsingTest, "C<Class, v != 0> x;", "[template-parsing][operator-precedence-fallout]")
{
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 4);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 3);
  CppVarEPtr var = members[1];
  REQUIRE(var);
}
