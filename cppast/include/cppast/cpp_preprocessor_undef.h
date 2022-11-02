// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E208389D_3833_42AC_97DA_384BF200EE7F
#define E208389D_3833_42AC_97DA_384BF200EE7F

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppPreprocessorUndef : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_UNDEF;
  }

  CppPreprocessorUndef(std::string name)
    : CppEntity(EntityType())
    , name_(std::move(name))
  {
  }

  const std::string& name() const
  {
    return name_;
  }

private:
  const std::string name_;
};

} // namespace CppAst

#endif /* E208389D_3833_42AC_97DA_384BF200EE7F */
