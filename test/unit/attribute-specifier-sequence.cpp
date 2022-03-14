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
  const auto& classAttribSeq = classDefn->attribSpecifierSequence();
  REQUIRE(classAttribSeq);
  REQUIRE(classAttribSeq->size() == 2);

  CppExprEPtr classAttrib0 = classAttribSeq->at(0);
  REQUIRE(classAttrib0);
  CHECK((*classAttrib0) == CppExpr("xnet::HttpController"));

  CppExprEPtr classAttrib1 = classAttribSeq->at(1);
  REQUIRE(classAttrib1);
  REQUIRE(classAttrib1->expr1_.atom);
  CHECK(*(classAttrib1->expr1_.atom) == "xnet::Route");
  CHECK(classAttrib1->oper_ == CppOperator::kFunctionCall);
  const auto funcArgs = classAttrib1->expr2_.expr;
  REQUIRE(funcArgs);
  CHECK(funcArgs->expr1_.type == CppExprAtom::kAtom);
  REQUIRE(funcArgs->expr1_.atom);
  CHECK(*(funcArgs->expr1_.atom) == "\"/plakmp\"");

  const auto& classMembers = classDefn->members();
  REQUIRE(classMembers.size() == 3);

  const CppFunctionEPtr methodGetPlakMpPlayers = classMembers[0];
  REQUIRE(methodGetPlakMpPlayers);
  const auto& returnTypeGetPlakMpPlayers = methodGetPlakMpPlayers->retType_;
  REQUIRE(returnTypeGetPlakMpPlayers);

  const auto& attribSeqGetPlakMpPlayers = returnTypeGetPlakMpPlayers->attribSpecifierSequence();
  REQUIRE(attribSeqGetPlakMpPlayers);
  REQUIRE(attribSeqGetPlakMpPlayers->size() == 2);

  CppExprEPtr methodAttrib0 = attribSeqGetPlakMpPlayers->at(0);
  REQUIRE(methodAttrib0);
  CHECK((*methodAttrib0) == CppExpr("xnet::HttpGet"));

  CppExprEPtr methodAttrib1 = attribSeqGetPlakMpPlayers->at(1);
  REQUIRE(methodAttrib1);
  REQUIRE(methodAttrib1->expr1_.atom);
  CHECK(*(methodAttrib1->expr1_.atom) == "xnet::Route");
  CHECK(methodAttrib1->oper_ == CppOperator::kFunctionCall);
  const auto funcArgs2 = methodAttrib1->expr2_.expr;
  REQUIRE(funcArgs2);
  CHECK(funcArgs2->expr1_.type == CppExprAtom::kAtom);
  REQUIRE(funcArgs2->expr1_.atom);
  CHECK(*(funcArgs2->expr1_.atom) == "\"/players\"");
}
