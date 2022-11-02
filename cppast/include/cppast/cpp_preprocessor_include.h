// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BC97BFFF_ABE6_4D65_BB85_0BFE81A98146
#define BC97BFFF_ABE6_4D65_BB85_0BFE81A98146

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppPreprocessorInclude : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_INCLUDE;
  }

public:
  CppPreprocessorInclude(std::string name)
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
  const std::string name_;
};

} // namespace CppAst

#endif /* BC97BFFF_ABE6_4D65_BB85_0BFE81A98146 */
