// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C71015A9_4DC2_457C_9322_CB5C71E71649
#define C71015A9_4DC2_457C_9322_CB5C71E71649

#include "cppast/cpp_entity.h"

namespace cppast {

class CppUsingNamespaceDecl : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::USING_NAMESPACE;
  }

public:
  CppUsingNamespaceDecl(std::string name)
    : CppEntity(EntityType())
    , name_(std::move(name))
  {
  }

public:
  const std::string& name() const
  {
    return name_;
  }

private:
  std::string name_;
};

} // namespace cppast

#endif /* C71015A9_4DC2_457C_9322_CB5C71E71649 */
