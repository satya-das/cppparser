#include <catch/catch.hpp>

#include "cppparser.h"
#include "utils.h"

#include <boost/filesystem.hpp>

#include <string>

namespace fs = boost::filesystem;

namespace {

auto getBeforeLine(const std::string& fileContent, int lineNum)
{
  auto itr = fileContent.begin();
  for (; lineNum && itr != fileContent.end(); ++itr)
  {
    if (*itr == '\n')
      --lineNum;
  }
  return itr;
}

} // namespace

class DisabledCodeTest
{
  std::string thisFileContent;
  std::string reverseContent;

protected:
  DisabledCodeTest()
    : thisFileContent(readFile(__FILE__))
    , reverseContent(thisFileContent.rbegin(), thisFileContent.rend())
  {
  }

  std::string getTestSnippet(int lastSnippetBeforeLineNum) const
  {
    const auto testSnippetStartsAfter  = std::string("#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE\n");
    const auto reverseSearchStartPoint = std::string(testSnippetStartsAfter.rbegin(), testSnippetStartsAfter.rend());

    const auto snippetEnd    = getBeforeLine(thisFileContent, lastSnippetBeforeLineNum);
    const auto snippetEndPos = snippetEnd - thisFileContent.begin();
    const auto snippetBeginPos =
      thisFileContent.size() - reverseContent.find(reverseSearchStartPoint, thisFileContent.size() - snippetEndPos);

    return thisFileContent.substr(snippetBeginPos, snippetEndPos - snippetBeginPos);
  }

  /**
   * Returns string suitable to feed to the parser.
   */
  std::string getTestSnippetParseStream(int lastSnippetBeforeLineNum) const
  {
    return getTestSnippet(lastSnippetBeforeLineNum).append(3, '\0');
  }
};

TEST_CASE_METHOD(DisabledCodeTest, " Code disabled using #if")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  if CPPPARSER_DISABLED_PARAM_TEST
                                  ,
                                  int disabledParam
#  endif // CPPPARSER_DISABLED_PARAM_TEST
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser parser;
  parser.addDefinedName("CPPPARSER_DISABLED_PARAM_TEST", 0);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);

  CppFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto* params = func->params();
  REQUIRE(params != nullptr);
  CHECK(params->size() == 1);
}

TEST_CASE_METHOD(DisabledCodeTest, " Code disabled using #if !")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  if !CPPPARSER_DISABLED_PARAM_TEST
                                  ,
                                  int disabledParam
#  endif // CPPPARSER_DISABLED_PARAM_TEST
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser parser;
  parser.addDefinedName("CPPPARSER_DISABLED_PARAM_TEST", 0);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);

  CppFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto* params = func->params();
  REQUIRE(params != nullptr);
  CHECK(params->size() == 2);
}

TEST_CASE_METHOD(DisabledCodeTest, " Code enabled in #else part of #if")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  if CPPPARSER_DISABLED_PARAM_TEST
                                    Anything in this part should not fail the parser
#  else
                                  ,
                                  int disabledParam
#  endif // CPPPARSER_DISABLED_PARAM_TEST
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser parser;
  parser.addDefinedName("CPPPARSER_DISABLED_PARAM_TEST", 0);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);

  CppFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto* params = func->params();
  REQUIRE(params != nullptr);
  CHECK(params->size() == 2);
}

TEST_CASE_METHOD(DisabledCodeTest, " Code disabled using #ifdef")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  ifdef CPPPARSER_DISABLED_USING_IFDEF_PARAM_TEST
                                  ,
                                  int disabledParam
#  endif // CPPPARSER_DISABLED_USING_IFDEF_PARAM_TEST
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser parser;
  parser.addUndefinedNames({"CPPPARSER_DISABLED_USING_IFDEF_PARAM_TEST"});
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);

  CppFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto* params = func->params();
  REQUIRE(params != nullptr);
  CHECK(params->size() == 1);
}

TEST_CASE_METHOD(DisabledCodeTest, " Code enabled in #else part of #ifdef")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  ifdef CPPPARSER_DISABLED_USING_IFDEF_PARAM_TEST
                                    Anything in this part should not fail the parser
#  else
                                  ,
                                  int disabledParam
#  endif // CPPPARSER_DISABLED_USING_IFDEF_PARAM_TEST
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser parser;
  parser.addUndefinedNames({"CPPPARSER_DISABLED_USING_IFDEF_PARAM_TEST"});
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);

  CppFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto* params = func->params();
  REQUIRE(params != nullptr);
  CHECK(params->size() == 2);
}

TEST_CASE_METHOD(DisabledCodeTest, " Code disabled using #ifndef")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  ifndef CPPPARSER_DISABLED_USING_IFNDEF_PARAM_TEST
                                  ,
                                  int disabledParam
#  else
#  endif // CPPPARSER_DISABLED_USING_IFNDEF_PARAM_TEST
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser parser;
  parser.addDefinedName("CPPPARSER_DISABLED_USING_IFNDEF_PARAM_TEST", 1);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);

  CppFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto* params = func->params();
  REQUIRE(params != nullptr);
  CHECK(params->size() == 1);
}

TEST_CASE_METHOD(DisabledCodeTest, " Code enabled in #else part of #ifndef")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  ifndef CPPPARSER_DISABLED_USING_IFNDEF_PARAM_TEST
                                    Anything in this part should not fail the parser
#  else
                                  ,
                                  int disabledParam
#  endif // CPPPARSER_DISABLED_USING_IFNDEF_PARAM_TEST
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser parser;
  parser.addDefinedName("CPPPARSER_DISABLED_USING_IFNDEF_PARAM_TEST", 1);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 1);

  CppFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto* params = func->params();
  REQUIRE(params != nullptr);
  CHECK(params->size() == 2);
}
