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

#pragma once

#include "utils.h"

#include <string>

/**
 * @brief Parent class of all unit tests that uses embedded test snippet in the test body itself.
 */
class EmbeddedSnippetTestBase
{
  const std::string testProgramFileContent;
  const std::string reverseContent;

protected:
  EmbeddedSnippetTestBase(const std::string& testProgramFile)
    : testProgramFileContent(readFile(testProgramFile))
    , reverseContent(testProgramFileContent.rbegin(), testProgramFileContent.rend())
  {
  }

  /**
   * Returns the iterator that points to the element in file content that is at the start of the given `lineNum`.
   */
  static auto getBeforeLine(const std::string& fileContent, int lineNum)
  {
    auto itr = fileContent.begin();
    for (; lineNum && itr != fileContent.end(); ++itr)
    {
      if (*itr == '\n')
        --lineNum;
    }
    return itr;
  }

  /**
   * Returns the test snippet embedded in this file.
   */
  std::string getTestSnippet(int lastSnippetBeforeLineNum) const
  {
    const auto testSnippetStartsAfter  = std::string("#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE\n");
    const auto reverseSearchStartPoint = std::string(testSnippetStartsAfter.rbegin(), testSnippetStartsAfter.rend());

    const auto snippetEnd    = getBeforeLine(testProgramFileContent, lastSnippetBeforeLineNum);
    const auto snippetEndPos = snippetEnd - testProgramFileContent.begin();
    const auto snippetBeginPos =
      testProgramFileContent.size()
      - reverseContent.find(reverseSearchStartPoint, testProgramFileContent.size() - snippetEndPos);

    return testProgramFileContent.substr(snippetBeginPos, snippetEndPos - snippetBeginPos);
  }

  /**
   * Returns string suitable to feed to the parser.
   */
  std::string getTestSnippetParseStream(int lastSnippetBeforeLineNum) const
  {
    return getTestSnippet(lastSnippetBeforeLineNum).append(3, '\0');
  }
};
