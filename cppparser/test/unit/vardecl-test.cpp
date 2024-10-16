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
  const auto& firstVar = varlist->firstVar();
  REQUIRE(varlist);
  REQUIRE(firstVar->isInitialized());
  CHECK(firstVar->initializeType() == cppast::CppVarInitializeType::USING_EQUAL);
  const auto& firstVarAssignVal = firstVar->assignValue();
  REQUIRE(firstVarAssignVal != nullptr);
  REQUIRE(varlist->varDeclList().size() == 1);
  const auto& secondVar = varlist->varDeclList()[0];
  REQUIRE(secondVar.isInitialized());
  CHECK(secondVar.initializeType() == cppast::CppVarInitializeType::USING_EQUAL);
  REQUIRE(secondVar.assignValue() != nullptr);
}

TEST_CASE_METHOD(VarDeclTest, "int variable, array_one[100], array_two[500];", "[vardecllist]")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  int variable, array_one[100], array_two[500];
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);
  cppast::CppConstVarListEPtr varlist = members[0];
  REQUIRE(varlist);
  const auto& firstVar = varlist->firstVar();
  REQUIRE(firstVar);
  CHECK(firstVar->arraySizes().size() == 0);

  REQUIRE(varlist->varDeclList().size() == 2);
  const auto& secondVar = varlist->varDeclList()[0];
  CHECK(secondVar.arraySizes().size() == 1);
  const auto& thirdVar = varlist->varDeclList()[1];
  CHECK(thirdVar.arraySizes().size() == 1);
}
