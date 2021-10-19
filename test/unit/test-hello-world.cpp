#include <catch/catch.hpp>

#include "cppparser.h"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

TEST_CASE(" Parsing hello world program")
{
  CppParser parser;
  parser.parseFunctionBodyAsBlob(false);
  auto testFilePath = fs::path(__FILE__).parent_path() / "test-files/hello-world.cpp";
  auto ast          = parser.parseFile(testFilePath.string());
  REQUIRE(ast != nullptr);

  const auto& members = ast->members();
  REQUIRE(members.size() == 2);

  CppIncludeEPtr hashInclude = members[0];
  REQUIRE(hashInclude);
  CHECK(hashInclude->name_ == "<iostream>");

  CppFunctionEPtr func = members[1];
  REQUIRE(func);
  CHECK(func->name_ == "main");

  REQUIRE(func->defn());
  const auto& mainBodyMembers = func->defn()->members();
  REQUIRE(mainBodyMembers.size() == 2);

  CppExprEPtr coutHelloWorld = mainBodyMembers[0];
  REQUIRE(coutHelloWorld);
  CHECK(coutHelloWorld->oper_ == CppOperator::kInsertion);
}
