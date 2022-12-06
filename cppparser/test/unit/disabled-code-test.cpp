#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

#include "embedded-snippet-test-base.h"

#include <string>

class DisabledCodeTest : public EmbeddedSnippetTestBase
{
protected:
  DisabledCodeTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

TEST_CASE_METHOD(DisabledCodeTest, "Code disabled using #if")
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

  cppparser::CppParser parser;
  parser.addDefinedName("CPPPARSER_DISABLED_PARAM_TEST", 0);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto params = GetAllParams(*func);
  CHECK(params.size() == 1);
}

TEST_CASE_METHOD(DisabledCodeTest, "Code disabled using #if !")
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

  cppparser::CppParser parser;
  parser.addDefinedName("CPPPARSER_DISABLED_PARAM_TEST", 0);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto params = GetAllParams(*func);
  CHECK(params.size() == 2);
}

TEST_CASE_METHOD(DisabledCodeTest, "Code enabled in #else part of #if")
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

  cppparser::CppParser parser;
  parser.addDefinedName("CPPPARSER_DISABLED_PARAM_TEST", 0);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto params = GetAllParams(*func);
  CHECK(params.size() == 2);
}

TEST_CASE_METHOD(DisabledCodeTest, "Code enabled using #if {ID} >= {NUM}")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  if CPPPARSER_ENABLED_PARAM_TEST >= 1
                                  ,
                                  int disabledParam
#  endif // CPPPARSER_ENABLED_PARAM_TEST
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  parser.addDefinedName("CPPPARSER_ENABLED_PARAM_TEST", 2);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto params = GetAllParams(*func);
  CHECK(params.size() == 2);
}

TEST_CASE_METHOD(DisabledCodeTest, "Code disabled using #ifdef")
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

  cppparser::CppParser parser;
  parser.addUndefinedNames({"CPPPARSER_DISABLED_USING_IFDEF_PARAM_TEST"});
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto params = GetAllParams(*func);
  CHECK(params.size() == 1);
}

TEST_CASE_METHOD(DisabledCodeTest, "Code enabled in #else part of #ifdef")
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

  cppparser::CppParser parser;
  parser.addUndefinedNames({"CPPPARSER_DISABLED_USING_IFDEF_PARAM_TEST"});
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto params = GetAllParams(*func);
  CHECK(params.size() == 2);
}

TEST_CASE_METHOD(DisabledCodeTest, "Code disabled using #ifndef")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  ifndef CPPPARSER_TEST_DEFINED_MACRO
                                  ,
                                  int disabledParam
#  else
#  endif // CPPPARSER_TEST_DEFINED_MACRO
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  parser.addDefinedName("CPPPARSER_TEST_DEFINED_MACRO", 1);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto params = GetAllParams(*func);
  CHECK(params.size() == 1);
}

TEST_CASE_METHOD(DisabledCodeTest, "Code enabled in #else part of #ifndef")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  void FunctionWithDisabledParams(int normalParam
#  ifndef CPPPARSER_TEST_DEFINED_MACRO
                                    Anything in this part should not fail the parser
#  else
                                  ,
                                  int disabledParam
#  endif // CPPPARSER_TEST_DEFINED_MACRO
  );
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  parser.addDefinedName("CPPPARSER_TEST_DEFINED_MACRO", 1);
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  cppast::CppConstFunctionEPtr func = members[0];
  REQUIRE(func);

  const auto params = GetAllParams(*func);
  CHECK(params.size() == 2);
}

TEST_CASE_METHOD(DisabledCodeTest, "Enabled code section has disabled subsection")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
#  if CPPPARSER_TEST_DEFINED_MACRO
  int x;
#    ifdef CPPPARSER_DISABLED_USING_IFDEF
  int y;   // We don't expect this part to get parsed in the AST
#    endif // CPPPARSER_DISABLED_USING_IFDEF
#  endif   // CPPPARSER_TEST_DEFINED_MACRO
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  cppparser::CppParser parser;
  parser.addDefinedName("CPPPARSER_TEST_DEFINED_MACRO", 1);
  parser.addUndefinedName("CPPPARSER_DISABLED_USING_IFDEF");
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 1);

  const cppast::CppConstVarEPtr var = members[0];
  REQUIRE(var);
}
