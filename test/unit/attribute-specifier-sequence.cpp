#include <catch/catch.hpp>

#include "cppparser.h"

#include "embedded-snippet-test-base.h"

#include <string>

class CppAtributeTest : public EmbeddedSnippetTestBase
{
protected:
  CppAtributeTest()
    : EmbeddedSnippetTestBase(__FILE__)
  {
  }
};

TEST_CASE_METHOD(CppAtributeTest, "Attribute specifier sequence")
{
#if TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE
  struct [[xnet::ValidateData]] SignUpRequest
  {
    [[xnet::StringNotEmpty]] [[xnet::StringMinLength(2)]] std::string name;
  };

  class [[xnet::HttpController]] [[xnet::Route("/plakmp")]] PlakMpApiController
  {
  public:
    [[xnet::HttpGet]] [[xnet::Route("/players")]] std::string GetPlakMpPlayers(std::string first_name);

    [[xnet::HttpGet]] std::string GetHelloWorld();

    [[xnet::HttpPost]] [[xnet::Route("/register")]] std::string CreateAccount(
      [[xnet::FromBody]] [[xnet::EnsureValid]] SignUpRequest request);
  };
#endif
  auto testSnippet = getTestSnippetParseStream(__LINE__ - 2);

  CppParser  parser;
  const auto ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 2);

  CppCompoundEPtr structDefn = members[0];
  REQUIRE(structDefn);
  const auto& structAttribSeq = structDefn->attribSpecifierSequence();
  REQUIRE(structAttribSeq);
  REQUIRE(structAttribSeq->size() == 1);

  CppExprEPtr structAttrib = structAttribSeq->at(0);
  REQUIRE(structAttrib);
  CHECK((*structAttrib) == CppExpr("xnet::ValidateData"));

  const auto& structMembers = structDefn->members();
  REQUIRE(structMembers.size() == 1);

  CppCompoundEPtr classDefn = members[1];
  REQUIRE(classDefn);
  REQUIRE(classDefn->attribSpecifierSequence());
  const auto& classMembers = classDefn->members();
  REQUIRE(classMembers.size() == 3);
}
