#include <catch/catch.hpp>

#include "cppparser/cppparser.h"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

TEST_CASE("Parsing hello world program")
{
  cppparser::CppParser parser;
  const auto           testFilePath = fs::path(__FILE__).parent_path() / "test-files/hello-world.cpp";
  const auto           ast          = parser.parseFile(testFilePath.string());
  REQUIRE(ast);

  const auto members = GetAllOwnedEntities(*ast);
  REQUIRE(members.size() == 2);

  const cppast::CppConstPreprocessorIncludeEPtr hashInclude = members[0];
  REQUIRE(hashInclude);
  CHECK(hashInclude->name() == "<iostream>");

  cppast::CppConstFunctionEPtr func = members[1];
  REQUIRE(func);
  CHECK(func->name() == "main");

  REQUIRE(func->defn());
  const auto mainBodyMembers = GetAllOwnedEntities(*func->defn());
  REQUIRE(mainBodyMembers.size() == 2);

  cppast::CppConstBinomialExprEPtr coutHelloWorld = mainBodyMembers[0];
  REQUIRE(coutHelloWorld);
  CHECK(coutHelloWorld->oper() == cppast::CppBinaryOperator::INSERTION);
}
