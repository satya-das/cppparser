// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

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

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);
  cppast::CppConstCompoundEPtr compound = members[0];
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

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 3);
  cppast::CppConstVarEPtr var = members[1];
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

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 3);
  cppast::CppConstVarEPtr var = members[1];
  REQUIRE(var);
}
