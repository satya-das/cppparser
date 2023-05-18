#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

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

  cppparser::CppParser parser;
  const auto           ast = parser.parseStream(testSnippet.data(), testSnippet.size());
  REQUIRE(ast != nullptr);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 2);

  cppast::CppConstCompoundEPtr structDefn = members[0];
  REQUIRE(structDefn);
  const auto structAttribSeq = GetAllAttributeSpecifiers(*structDefn);
  REQUIRE(structAttribSeq.size() == 1);

  cppast::CppConstStringLiteralExprEPtr structAttrib = structAttribSeq.at(0);
  REQUIRE(structAttrib);
  CHECK((*structAttrib) == cppast::CppStringLiteralExpr("xnet::ValidateData"));

  const auto structMembers = GetAllOwnedEntities(*structDefn);
  REQUIRE(structMembers.size() == 1);

  cppast::CppConstCompoundEPtr classDefn = members[1];
  REQUIRE(classDefn);
  const auto classAttribSeq = GetAllAttributeSpecifiers(*classDefn);
  REQUIRE(classAttribSeq.size() == 2);

  cppast::CppConstStringLiteralExprEPtr classAttrib0 = classAttribSeq.at(0);
  REQUIRE(classAttrib0);
  CHECK((*classAttrib0) == cppast::CppStringLiteralExpr("xnet::HttpController"));

  cppast::CppConstFunctionCallExprEPtr classAttrib1 = classAttribSeq.at(1);
  /* TODO: Enable this
  REQUIRE(classAttrib1);
  REQUIRE(classAttrib1->expr1_.atom);
  CHECK(*(classAttrib1->expr1_.atom) == "xnet::Route");
  CHECK(classAttrib1->oper_ == cppast::CppOperator::kFunctionCall);
  const auto funcArgs = classAttrib1->expr2_.expr;
  REQUIRE(funcArgs);
  CHECK(funcArgs->expr1_.type == cppast::CppExprAtom::kAtom);
  REQUIRE(funcArgs->expr1_.atom);
  CHECK(*(funcArgs->expr1_.atom) == "\"/plakmp\"");

  const auto classMembers = GetAllOwnedEntities(*classDefn);
  REQUIRE(classMembers.size() == 4);

  const cppast::CppConstFunctionEPtr methodGetPlakMpPlayers = classMembers[1];
  REQUIRE(methodGetPlakMpPlayers);
  const auto* returnTypeGetPlakMpPlayers = methodGetPlakMpPlayers->returnType();
  REQUIRE(returnTypeGetPlakMpPlayers);

  const auto attribSeqGetPlakMpPlayers = GetAllAttributeSpecifiers(*returnTypeGetPlakMpPlayers);
  REQUIRE(attribSeqGetPlakMpPlayers.size() == 2);

  cppast::CppConstExpressionEPtr methodAttrib0 = attribSeqGetPlakMpPlayers.at(0);
  REQUIRE(methodAttrib0);
  CHECK((*methodAttrib0) == cppast::CppExpression("xnet::HttpGet"));

  cppast::CppConstExpressionEPtr methodAttrib1 = attribSeqGetPlakMpPlayers.at(1);
  REQUIRE(methodAttrib1);
  REQUIRE(methodAttrib1->expr1_.atom);
  CHECK(*(methodAttrib1->expr1_.atom) == "xnet::Route");
  CHECK(methodAttrib1->oper_ == cppast::CppOperator::kFunctionCall);
  const auto funcArgs2 = methodAttrib1->expr2_.expr;
  REQUIRE(funcArgs2);
  CHECK(funcArgs2->expr1_.type == cppast::CppExprAtom::kAtom);
  REQUIRE(funcArgs2->expr1_.atom);
  CHECK(*(funcArgs2->expr1_.atom) == "\"/players\"");
  */
}
