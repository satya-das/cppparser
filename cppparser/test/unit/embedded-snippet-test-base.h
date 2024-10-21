// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BDBCC362_A51C_4ECA_BEFF_299AE5927F2F
#define BDBCC362_A51C_4ECA_BEFF_299AE5927F2F

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
    return getTestSnippet(lastSnippetBeforeLineNum).append(2, '\0');
  }
};

#endif /* BDBCC362_A51C_4ECA_BEFF_299AE5927F2F */
