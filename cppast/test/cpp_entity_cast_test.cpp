#include <catch/catch.hpp>

#include "cppast/cppast.h"

TEST_CASE("Casting of CppEntity* to derived class")
{
  cppast::CppCompound     compound("TestClass", cppast::CppCompoundType::CLASS);
  cppast::CppEntity*      entity      = &compound;
  cppast::CppCompoundEPtr compoundPtr = entity;
  CHECK(compoundPtr);
}

TEST_CASE("Casting of const CppEntity* to derived class")
{
  const cppast::CppCompound    compound("TestClass", cppast::CppCompoundType::CLASS);
  const cppast::CppEntity*     entity      = &compound;
  cppast::CppConstCompoundEPtr compoundPtr = entity;
  CHECK(compoundPtr);
}
