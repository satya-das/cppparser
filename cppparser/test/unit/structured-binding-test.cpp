// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

#include "embedded-snippet-test-base.h"

#include <string>

class StructuredBindingTest : public EmbeddedSnippetTestBase
{
protected:
  StructuredBindingTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

/*
TEST_CASE_METHOD(StructuredBindingTest, "auto [x, y] = std::pair<int, int>(5, 10);", "[structuredbinding]")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  auto [x1, y1] = std::pair<int, int>(5, 10);
  auto [x2, y2] { std::pair<int, int>(5, 10) };
  auto [x3, y3] ( std::pair<int, int>(5, 10) );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);
}
*/
