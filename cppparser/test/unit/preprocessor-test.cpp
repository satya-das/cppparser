// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

#include "embedded-snippet-test-base.h"

#include <string>

class ProprocessorTest : public EmbeddedSnippetTestBase
{
protected:
  ProprocessorTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

TEST_CASE_METHOD(ProprocessorTest, "include<iostream>", "[preprocessor]")
{
  // clang-format off
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
#    include<iostream>
#  endif
#endif
  // clang-format on
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 3);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members     = GetAllOwnedEntities(*ast);
  const auto hashInclude = cppast::CppConstPreprocessorIncludeEPtr(members[1]);
  REQUIRE(hashInclude);
  CHECK(hashInclude->name() == "<iostream>");
}
