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

#include "angle-bracket-match-finder.h"

#include "embedded-snippet-test-base.h"

#include <string>

class AngleBracketMatchFinderTest : public EmbeddedSnippetTestBase
{
protected:
  AngleBracketMatchFinderTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }

  class EnsureInputBufferUnchanged
  {
    const std::string& originalSnippet;
    const std::string  copiedSnippet;

  public:
    EnsureInputBufferUnchanged(const std::string& snippet)
      : originalSnippet(snippet)
      , copiedSnippet(snippet)
    {
    }
    ~EnsureInputBufferUnchanged()
    {
      CHECK(originalSnippet == copiedSnippet);
    }
  };
};

#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
template <typename T>
struct Test1
{
};
#endif
TEST_CASE_METHOD(AngleBracketMatchFinderTest, "template <typename T>", "[template-parse-helper]")
{
  auto       testSnippet       = getTestSnippetParseStream(__LINE__ - 4);
  const auto startAngleBracket = testSnippet.data() + 9;
  REQUIRE(*startAngleBracket == '<');
  EnsureInputBufferUnchanged ensureInputBufferUnchanged(testSnippet);
  const auto                 matchedClosedBracket =
    findMatchedClosingAngleBracket(startAngleBracket, testSnippet.data() + testSnippet.size());
  CHECK(*matchedClosedBracket == '>');
}

#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
TT<Ta1, TT2<Ta2> > var;
#  endif
#endif
TEST_CASE_METHOD(AngleBracketMatchFinderTest, "TT<Ta1, TT2<Ta2> >", "[template-parse-helper]")
{
  auto       testSnippet        = getTestSnippetParseStream(__LINE__ - 4);
  const auto startAngleBracket1 = testSnippet.data() + 23;
  REQUIRE(*startAngleBracket1 == '<');
  EnsureInputBufferUnchanged ensureInputBufferUnchanged(testSnippet);
  const auto                 matchedClosedBracket1 =
    findMatchedClosingAngleBracket(startAngleBracket1, testSnippet.data() + testSnippet.size());
  CHECK(*matchedClosedBracket1 == '>');

  const auto startAngleBracket2 = startAngleBracket1 + 9;
  REQUIRE(*startAngleBracket2 == '<');
  const auto matchedClosedBracket2 =
    findMatchedClosingAngleBracket(startAngleBracket2, testSnippet.data() + testSnippet.size());
  CHECK(*matchedClosedBracket2 == '>');
  CHECK(matchedClosedBracket1 > matchedClosedBracket2);
}

#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if EVADE_COMPILER
inline bool operator<(char c) const
{
  return c > 0;
}
#  endif
#endif
TEST_CASE_METHOD(AngleBracketMatchFinderTest, "operator<(){}", "[template-parse-helper]")
{
  auto       testSnippet       = getTestSnippetParseStream(__LINE__ - 4);
  const auto startAngleBracket = testSnippet.data() + 41;
  REQUIRE(*startAngleBracket == '<');
  EnsureInputBufferUnchanged ensureInputBufferUnchanged(testSnippet);
  const auto                 matchedClosedBracket =
    findMatchedClosingAngleBracket(startAngleBracket, testSnippet.data() + testSnippet.size());
  CHECK(matchedClosedBracket == nullptr);
}
