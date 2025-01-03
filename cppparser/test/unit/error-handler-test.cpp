// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

#include "embedded-snippet-test-base.h"

#include <string>

class ErrorHandlerTest : public EmbeddedSnippetTestBase
{
protected:
  ErrorHandlerTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

TEST_CASE_METHOD(ErrorHandlerTest, "Error line and column")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
  callFunc(x, y, ); // Error should be reported for the position of ')'
#  endif
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  bool                               errHandlerCalled = false;
  cppparser::CppParser::ErrorHandler errHandler =
    [&errHandlerCalled](const char* errLineText, size_t lineNum, size_t errorStartPos, int lexerContext) {
      errHandlerCalled = true;
      CHECK(errLineText != nullptr);
      CHECK(lineNum == 2);
      CHECK(errorStartPos == 17);
    };
  cppparser::CppParser parser;
  parser.setErrorHandler(errHandler);
  const bool exceptionThrown = [&]() {
    try
    {
      parser.parseStream(testSnippet.data(), testSnippet.size());
      // FAIL();
    }
    catch (const std::exception& e)
    {
      return true;
    }

    return false;
  }();

  CHECK(errHandlerCalled);
  parser.resetErrorHandler();
  // CHECK(exceptionThrown);
  (void) exceptionThrown;
}
