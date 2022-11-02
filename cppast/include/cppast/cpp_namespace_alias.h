// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef EF5889FE_0030_44BB_9ED0_BA3CAC9467FB
#define EF5889FE_0030_44BB_9ED0_BA3CAC9467FB

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppNamespaceAlias : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::NAMESPACE_ALIAS;
  }

public:
  const std::string name_;
  const std::string alias_;

  CppNamespaceAlias(std::string name, std::string alias)
    : CppEntity(EntityType())
    , name_(std::move(name))
    , alias_(std::move(alias))
  {
  }
};

} // namespace CppAst

#endif /* EF5889FE_0030_44BB_9ED0_BA3CAC9467FB */
