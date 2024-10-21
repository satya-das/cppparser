// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

#include "embedded-snippet-test-base.h"

#include <string>

class InitializerListTest : public EmbeddedSnippetTestBase
{
protected:
  InitializerListTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

TEST_CASE_METHOD(InitializerListTest, "docstr in middle", "[initializerlist]")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  bool boolArray[] = {false,
                      // IGNORABLE COMMENTS HERE
                      false};
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);
  cppast::CppConstVarEPtr var = members[0];
  REQUIRE(var);
}
