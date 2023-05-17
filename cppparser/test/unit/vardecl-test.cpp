// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

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

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);
  cppast::CppConstVarListEPtr varlist = members[0];
  REQUIRE(varlist);
  REQUIRE(varlist->firstVar()->assignValue() != nullptr);
  CHECK(varlist->firstVar()->assignType() == cppast::CppVarInitializeType::USING_EQUAL);
  REQUIRE(varlist->varDeclList().size() == 1);
  REQUIRE(varlist->varDeclList()[0].assignValue() != nullptr);
  CHECK(varlist->varDeclList()[0].assignType() == cppast::CppVarInitializeType::USING_EQUAL);
}
