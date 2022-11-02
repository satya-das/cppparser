// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C71015A9_4DC2_457C_9322_CB5C71E71649
#define C71015A9_4DC2_457C_9322_CB5C71E71649

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppUsingNamespaceDecl : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::USING_NAMESPACE;
  }

public:
  const std::string name_;

  CppUsingNamespaceDecl(std::string name)
    : CppEntity(EntityType())
    , name_(std::move(name))
  {
  }
};

} // namespace CppAst

#endif /* C71015A9_4DC2_457C_9322_CB5C71E71649 */
