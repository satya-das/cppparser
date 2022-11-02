// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E9679E26_EB4E_4C8F_952F_FEDCCFB07380
#define E9679E26_EB4E_4C8F_952F_FEDCCFB07380

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppVarDeclInList : public CppTypeModifier, public CppVarDecl
{
public:
  CppVarDeclInList(CppTypeModifier modifier, CppVarDecl varDecl)
    : CppTypeModifier(modifier)
    , CppVarDecl(std::move(varDecl))
  {
  }
};

using CppVarDeclList = std::vector<CppVarDeclInList>;

/**
 * @brief List of variables declared in a line without repeating its type, e.g. int i, j; is a var-list.
 */
class CppVarList : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::VAR_LIST;
  }

public:
  const std::unique_ptr<CppVar> firstVar_;

  CppVarList(CppVar* firstVar, CppVarDeclInList varDecl)
    : CppEntity(EntityType())
    , firstVar_(firstVar)
  {
    addVarDecl(std::move(varDecl));
  }
  void addVarDecl(CppVarDeclInList varDecl)
  {
    varDeclList_.push_back(std::move(varDecl));
  }
  const std::unique_ptr<CppVar>& firstVar() const
  {
    return firstVar_;
  }
  const CppVarDeclList& varDeclList() const
  {
    return varDeclList_;
  }

private:
  CppVarDeclList varDeclList_;
};

} // namespace CppAst

#endif /* E9679E26_EB4E_4C8F_952F_FEDCCFB07380 */
