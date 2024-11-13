// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DEE52E89_9A5C_4A01_B51A_D0D4786BC7EF
#define DEE52E89_9A5C_4A01_B51A_D0D4786BC7EF

#include "cppast/cpp_enum.h"
#include "cppast/cpp_function.h"
#include "cppast/cpp_type_modifier.h"
#include "cppast/cpp_var_type.h"
#include "cppast/cppconst.h"

#include <string>

namespace cppast {

class CppFunctionPointer;
class CppEnum;

/**
 * @brief Models variable type in C++.
 *
 * It can be used to define a variable or function parameter.
 * @see CppVar.
 */
class CppVarType : public CppAttributeSpecifierSequenceContainer
{
public:
  CppVarType(std::string baseType, CppTypeModifier modifier);
  CppVarType(CppCompound* compound, CppTypeModifier modifier);
  CppVarType(CppFunctionPointer* fptr, CppTypeModifier modifier);
  CppVarType(CppEnum* enumObj, CppTypeModifier modifier);
  CppVarType(const CppVarType& varType);

  const std::string& baseType() const
  {
    return baseType_;
  }
  void baseType(std::string baseTypeArg)
  {
    baseType_ = std::move(baseTypeArg);
  }
  const CppEntity* compound() const
  {
    return compound_.get();
  }
  std::uint32_t typeAttr() const
  {
    return typeAttr_;
  }
  void typeAttr(std::uint32_t attr)
  {
    typeAttr_ = attr;
  }
  void addAttr(std::uint32_t attr)
  {
    if ((attr & CppIdentifierAttrib::CONST) == 0)
      typeAttr_ |= attr;
    else
      typeModifier_.constBits_ |= 1;
  }

  const CppTypeModifier& typeModifier() const
  {
    return typeModifier_;
  }

  CppTypeModifier& typeModifier()
  {
    return typeModifier_;
  }

  void parameterPack(bool paramPack)
  {
    paramPack_ = paramPack;
  }

  bool parameterPack() const
  {
    return paramPack_;
  }

private:
  CppVarType(std::string baseType, std::uint32_t typeAttr, CppTypeModifier modifier);

private:
  std::string baseType_; // This is the basic data type of var e.g. for 'const int*& pi' base-type is int.
  std::unique_ptr<CppEntity> compound_;
  CppTypeModifier            typeModifier_;
  std::uint32_t              typeAttr_ {0};
  bool                       paramPack_ {false};
};

} // namespace cppast

#endif /* DEE52E89_9A5C_4A01_B51A_D0D4786BC7EF */
